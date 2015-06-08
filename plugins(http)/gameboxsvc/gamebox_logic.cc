#include "gamebox_logic.h"
#include "whole_manager.h"
#include "db_comm.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "common.h"

namespace gameboxsvc_logic{

Gameboxlogic*
Gameboxlogic::instance_=NULL;

Gameboxlogic::Gameboxlogic(){
   if(!Init())
      assert(0);
}

Gameboxlogic::~Gameboxlogic(){
	gameboxsvc_logic::DBComm::Dest();
	gameboxsvc_logic::CacheManagerOp::FreeCacheManagerOp();
	gameboxsvc_logic::CacheManagerOp::FreeWholeCacheManager();
}

bool Gameboxlogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);
	gameboxsvc_logic::DBComm::Init(config->mysql_db_list_);
	gameboxsvc_logic::CacheManagerOp::GetCacheManagerOp();
	gameboxsvc_logic::CacheManagerOp::GetWholeManager();

	gameboxsvc_logic::CacheManagerOp::FetchDBAppInfo();
    return true;
}

Gameboxlogic*
Gameboxlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Gameboxlogic();

    return instance_;
}



void Gameboxlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Gameboxlogic::OnGameboxConnect(struct server *srv,const int socket){

    return true;
}



bool Gameboxlogic::OnGameboxMessage(struct server *srv, const int socket, const void *msg,const int len){
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
		case GAME_BOX_CHECK_GAME:
			OnCheckGame(srv,socket,value);
			break;
		case GAME_BOK_SHARK_GAME:
			OnSharkGame(srv,socket,value);
			break;
		}

		return true;
    return true;
}

bool Gameboxlogic::OnGameboxClose(struct server *srv,const int socket){

    return true;
}



bool Gameboxlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Gameboxlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Gameboxlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Gameboxlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Gameboxlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Gameboxlogic::OnCheckGame(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
   		const void* msg,const int len){
	scoped_ptr<netcomm_recv::CheckGame> checkgame(new netcomm_recv::CheckGame(netbase));
	//std::list<base_logic::AppInfos> remond_game_list;
	std::map<std::string,base_logic::AppInfos> remond_game_list;
	std::string error_str;
	int jerror_code = 0;
	bool r = false;
	int error_code = checkgame->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//获取推荐游戏
	gameboxsvc_logic::CacheManagerOp::GetWholeManager()->GetRecommend(remond_game_list);

	std::string content = checkgame->content();
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	base_logic::DictionaryValue*  value = (base_logic::DictionaryValue* )serializer->Deserialize(&jerror_code,&error_str);
	scoped_ptr<base_logic::ListValue> list;
	base_logic::ListValue* tp =NULL;
	r = value->GetList(L"list",&tp);
	list.reset(tp);
	if(list->GetSize()>0)
		gameboxsvc_logic::CacheManagerOp::GetWholeManager()->CheckGame(list.get(),remond_game_list);

	scoped_ptr<netcomm_send::CheckGame> sendcheckgame(new netcomm_send::CheckGame());

	for(std::map<std::string,base_logic::AppInfos>::iterator it = remond_game_list.begin();
			it!=remond_game_list.end();it++){
		base_logic::AppInfos appinfo = it->second;
		if(appinfo.attr()==1)
			sendcheckgame->set_own_app(appinfo.Release(false,true,true));
		else
			sendcheckgame->set_recomm_app(appinfo.Release(false,true,true));
	}
	send_message(socket,(netcomm_send::HeadPacket*)sendcheckgame.get());
	remond_game_list.clear();
	return true;
}

bool Gameboxlogic::OnSharkGame(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::HeadPacket> shark(new netcomm_recv::HeadPacket(netbase));
	bool r = false;
	int error_code = shark->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	std::list<base_logic::AppInfos> list;
	gameboxsvc_logic::CacheManagerOp::GetWholeManager()->GetRamdominApp(list);
	scoped_ptr<netcomm_send::SharkGame> sendsharkgame(new netcomm_send::SharkGame());
	while(list.size()>0){
		base_logic::AppInfos info = list.front();
		list.pop_front();
		sendsharkgame->set_app(info.Release(false,true,true));
	}
	send_message(socket,(netcomm_send::HeadPacket*)sendsharkgame.get());
	return true;
}

}

