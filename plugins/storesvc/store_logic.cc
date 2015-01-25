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


	//构造发送数据
	scoped_ptr<netcomm_send::AppSummary> appsummary(new netcomm_send::AppSummary());

	//读取APP
	base_logic::AppInfos  appinfo;
	r = storesvc_logic::DBComm::GetAppSummary(summary->appid(),summary->tclass(),appinfo);
	if(r)
		appsummary->set_intro(appinfo.Release());
	//读取相似
	std::list<base_logic::AppInfos> list;
	storesvc_logic::DBComm::SearchTypeApp(appinfo.type(),summary->tclass(),list);
	while(list.size()>0){
		base_logic::AppInfos app = list.front();
		list.pop_front();
		appsummary->set_like(app.Release());
	}
	//是否点赞

	send_message(socket,(netcomm_send::HeadPacket*)appsummary.get());
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

	//构造发送数据
	scoped_ptr<netcomm_send::WantAppUrl> want_url(new netcomm_send::WantAppUrl());

	std::string url;
	r = storesvc_logic::DBComm::GetWantUrl(want->appid(),want->tclass(),want->machine(),url);
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

	//点赞
	r = storesvc_logic::DBComm::WantAppLike(like->uid(),like->appid(),like->tclass());

	scoped_ptr<netcomm_send::HeadPacket> head(new netcomm_send::HeadPacket());
	head->set_status(1);
	send_message(socket,(netcomm_send::HeadPacket*)head.get());

	return true;
}

}

