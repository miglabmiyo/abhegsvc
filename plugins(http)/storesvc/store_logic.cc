#include "store_logic.h"
#include "db_comm.h"
#include "logic/logic_infos.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "net/store_comm_head.h"
#include "common.h"

namespace storesvc_logic{

Storelogic*
Storelogic::instance_=NULL;

Storelogic::Storelogic(){
   if(!Init())
      assert(0);
}

Storelogic::~Storelogic(){
	storesvc_logic::DBComm::Dest();
}

bool Storelogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);

	storesvc_logic::DBComm::Init(config->mysql_db_list_);
    return true;
}

Storelogic*
Storelogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Storelogic();

    return instance_;
}



void Storelogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Storelogic::OnStoreConnect(struct server *srv,const int socket){

    return true;
}



bool Storelogic::OnStoreMessage(struct server *srv, const int socket, const void *msg,const int len){
	const char* packet_stream = (char*)(msg);
		std::string http_str(packet_stream,len);
		std::string error_str;
		int error_code = 0;

		LOG_MSG2("%s",packet_stream);

		scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP,&http_str));


		netcomm_recv::NetBase*  value = (netcomm_recv::NetBase*)(serializer.get()->Deserialize(&error_code,&error_str));
		if(value==NULL){
			error_code = STRUCT_ERROR;
			//发送错误数据
			send_error(error_code,socket);
			return false;
		}
		scoped_ptr<netcomm_recv::HeadPacket> packet(new netcomm_recv::HeadPacket(value));
		int32 type = packet->GetType();
		switch(type){
		   case SUMMARY_INFOS:
			   OnAppSummary(srv,socket,value);
			   break;
		   case APP_WANT_URL:
			   OnWantURL(srv,socket,value);
			   break;
		   case APP_WANT_LIKE:
			   OnLikePraise(srv,socket,value);
			   break;
		   case APP_TOPICS:
			   OnAppTopics(srv,socket,value);
			   break;
		   case APP_SEARCH_KEY:
			   OnSearchByKey(srv,socket,value);
			   break;
		   case APP_SEARCH_TYPE:
			   OnSearchByType(srv,socket,value);
			   break;
		   case GAME_STRATEGY_CATALOG:
			   OnGameStrategyCatalog(srv,socket,value);
			   break;
		   case GAME_STRATEGY_DETAILS:
			   OnGameStrategyDetails(srv,socket,value);
			   break;
		   case APP_SHAK:
			   OnSharkStore(srv,socket,value);
			   break;
		}

		return true;
    return true;
}

bool Storelogic::OnStoreClose(struct server *srv,const int socket){

    return true;
}



bool Storelogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Storelogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Storelogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Storelogic::OnIniTimer(struct server *srv){

    return true;
}



bool Storelogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Storelogic::OnSearchByType(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
				const void* msg,const int len){
	scoped_ptr<netcomm_recv::AppSearchType> search_type(new netcomm_recv::AppSearchType(netbase));
	bool r = false;
	int error_code = search_type->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	int64 tid = search_type->tid();
	int32 tclass = tid/TYPE_BASIC_PARENT;
	std::list<base_logic::AppInfos> list;
	storesvc_logic::DBComm::SearchTypeApp(tid,tclass,list,search_type->from(),search_type->count());

	scoped_ptr<netcomm_send::AppSearchResult> result(new netcomm_send::AppSearchResult());
	while(list.size()>0){
		base_logic::AppInfos appinfo = list.front();
		list.pop_front();
		result->set_list(appinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)result.get());
	return true;
}



bool Storelogic::OnSearchByKey(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
			const void* msg,const int len){
	scoped_ptr<netcomm_recv::AppSearchKey> search_key(new netcomm_recv::AppSearchKey(netbase));
	bool r = false;
	int error_code = search_key->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	std::string key = search_key->key();
	std::list<base_logic::AppInfos> list;
	storesvc_logic::DBComm::SearchKeyApp(key,list,search_key->from(),search_key->count());
	scoped_ptr<netcomm_send::AppSearchResult> result(new netcomm_send::AppSearchResult());
	while(list.size()>0){
		base_logic::AppInfos appinfo = list.front();
		list.pop_front();
		result->set_list(appinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)result.get());
}

bool Storelogic::OnAppSummary(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
                  		const void* msg,const int len){
	scoped_ptr<netcomm_recv::AppSummary> summary(new netcomm_recv::AppSummary(netbase));
	bool r = false;
	int error_code = summary->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	int32 tclass = summary->appid()/TYPE_BASIC;

	//构造发送数据
	scoped_ptr<netcomm_send::AppSummary> appsummary(new netcomm_send::AppSummary());

	//读取APP
	base_logic::AppInfos  appinfo;
	r = storesvc_logic::DBComm::GetAppSummary(summary->appid(),tclass,appinfo);
	//读取图片集
	storesvc_logic::DBComm::GetAppPicList(summary->appid(),tclass,appinfo);
	if(r)
		appsummary->set_intro(appinfo.Release());
	//图片
	/*std::string pic1 = "http://pic.desgin.miglab.com/abheg/store/app/products/13/summary/s1.jpg";
	std::string pic2 = "http://pic.desgin.miglab.com/abheg/store/app/products/13/summary/s2.jpg";
	std::string pic3 = "http://pic.desgin.miglab.com/abheg/store/app/products/13/summary/s3.jpg";
	std::string pic4 = "http://pic.desgin.miglab.com/abheg/store/app/products/13/summary/s4.jpg";

	appsummary->set_pic(pic1);
	appsummary->set_pic(pic2);
	appsummary->set_pic(pic3);
	appsummary->set_pic(pic4);*/


	//读取相似
	std::list<base_logic::AppInfos> list;
	storesvc_logic::DBComm::SearchTypeApp(appinfo.type(),tclass,list);
	while(list.size()>0){
		base_logic::AppInfos app = list.front();
		list.pop_front();
		appsummary->set_like(app.Release());
	}
	//是否点赞

	send_message(socket,(netcomm_send::HeadPacket*)appsummary.get());
	return true;
}

bool Storelogic::OnAppTopics(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
        					const void* msg,const int len){
	scoped_ptr<netcomm_recv::AppTopics> topics(new netcomm_recv::AppTopics(netbase));
	bool r = false;
	int error_code = topics->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//
	scoped_ptr<netcomm_send::AppTopics> apptopics(new netcomm_send::AppTopics());
	std::list<base_logic::AppInfos> list;
	r = storesvc_logic::DBComm::GetTopics(topics->topics(),list);
	while(list.size()>0){
		base_logic::AppInfos app = list.front();
		list.pop_front();
		apptopics->set_topics(app.Release());
	}
	apptopics->set_like(15);
	send_message(socket,(netcomm_send::HeadPacket*)apptopics.get());
	return true;
}


bool Storelogic::OnWantURL(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
                      		const void* msg,const int len){
	scoped_ptr<netcomm_recv::WantAppUrl> want(new netcomm_recv::WantAppUrl(netbase));
	bool r = false;
	int error_code = want->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	int32 tclass = want->appid()/TYPE_BASIC;
	//构造发送数据
	scoped_ptr<netcomm_send::WantAppUrl> want_url(new netcomm_send::WantAppUrl());

	std::string url;
	r = storesvc_logic::DBComm::GetWantUrl(want->appid(),tclass,want->machine(),url);
	want_url->set_url(url);
	send_message(socket,(netcomm_send::HeadPacket*)want_url.get());

	return true;
}

bool Storelogic::OnLikePraise(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
                      		const void* msg,const int len){
	scoped_ptr<netcomm_recv::LikePraise> like(new netcomm_recv::LikePraise(netbase));
	bool r = false;
	int error_code = like->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	int32 tclass = like->appid()/TYPE_BASIC;

	//点赞
	r = storesvc_logic::DBComm::WantAppLike(like->uid(),like->appid(),tclass);

	scoped_ptr<netcomm_send::HeadPacket> head(new netcomm_send::HeadPacket());
	head->set_status(1);
	send_message(socket,(netcomm_send::HeadPacket*)head.get());

	return true;
}

bool Storelogic::OnGameStrategyCatalog(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
			const void* msg,const int len){
	scoped_ptr<netcomm_recv::GameStrategyCatalog> catalog(new netcomm_recv::GameStrategyCatalog(netbase));
	bool r = false;
	int error_code = catalog->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<storesvc_logic::GameStrategy> list;

	//读取攻略目录
	r = storesvc_logic::DBComm::GetGameStrategyCatalog(catalog->game_id(),catalog->from(),catalog->count(),list);

	scoped_ptr<netcomm_send::GameStrategyCatalog> scatalog(new netcomm_send::GameStrategyCatalog());
	while(list.size()>0){
		storesvc_logic::GameStrategy catalog = list.front();
		list.pop_front();
		scatalog->set_list(catalog.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)scatalog.get());
	return true;
}

bool Storelogic::OnGameStrategyDetails(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
			const void* msg,const int len){
	scoped_ptr<netcomm_recv::GameStrategyDetails> detail(new netcomm_recv::GameStrategyDetails(netbase));
	bool r = false;
	int error_code = detail->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	storesvc_logic::GameStrategy strategy;

	//读取攻略目录
	//r = storesvc_logic::DBComm::GetGameStrategyCatalog(catalog->game_id(),catalog->from(),catalog->count(),list);
	r = storesvc_logic::DBComm::GetGameStrategyDetail(detail->strategy_id(),strategy);
	scoped_ptr<netcomm_send::GameStrategyDetail> scatalog(new netcomm_send::GameStrategyDetail());

	scatalog->set_detail(strategy.details());
	send_message(socket,(netcomm_send::HeadPacket*)scatalog.get());
	return true;
}

bool Storelogic::OnSharkStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::ShakStore> shak(new netcomm_recv::ShakStore(netbase));
	bool r = false;
	int error_code = shak->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<base_logic::AppInfos> list;
	r = storesvc_logic::DBComm::ShakAppInfo(shak->latitude(),shak->longitude(),list);
	scoped_ptr<netcomm_send::AppSearchResult> result(new netcomm_send::AppSearchResult());
	while(list.size()>0){
		base_logic::AppInfos appinfo = list.front();
		list.pop_front();
		result->set_list(appinfo.Release());
	}
	send_message(socket,(netcomm_send::HeadPacket*)result.get());
	return true;
}

}

