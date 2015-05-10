#include "miyo_logic.h"
#include "db_comm.h"
#include "dic_comm.h"
#include "miyo_basic_info.h"
#include "miyo_http_api.h"
#include "whole_manager.h"
#include "net/miyo_comm_head.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "common.h"

namespace miyosvc_logic{

Miyologic*
Miyologic::instance_=NULL;

Miyologic::Miyologic(){
   if(!Init())
      assert(0);
}

Miyologic::~Miyologic(){
	miyosvc_logic::CacheManagerOp::FreeCacheManagerOp();
	miyosvc_logic::CacheManagerOp::FreeWholeCacheManager();
	miyosvc_logic::DBComm::Dest();
	miyosvc_logic::RedisComm::Dest();
}


bool Miyologic::Init(){
	miyosvc_logic::CacheManagerOp::GetCacheManagerOp();
	miyosvc_logic::CacheManagerOp::GetWholeCacheManager();
	bool r =false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);
	miyosvc_logic::DBComm::Init(config->mysql_db_list_);
	miyosvc_logic::RedisComm::Init(config->redis_list_);
	return true;
}


Miyologic*
Miyologic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Miyologic();

    return instance_;
}



void Miyologic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Miyologic::OnMiyoConnect(struct server *srv,const int socket){

    return true;
}



bool Miyologic::OnMiyoMessage(struct server *srv, const int socket, const void *msg,const int len){
	const char* packet_stream = (char*)(msg);
	std::string http_str(packet_stream,len);
	std::string error_str;
	int error_code = 0;

	LOG_DEBUG2("%s",packet_stream);

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
	   case THIRID_LOGIN:
		   OnThirdLogin(srv,socket,value,msg,len);
		   break;
	   case MUSIC_GAIN_COLLECT_LIST:
		   OnGainCollectList(srv,socket,value);
		   break;
	   case MUSIC_GAIN_DIMENSION_LIST:
		   OnGainDimensionList(srv,socket,value);
		   break;
	   case MUSIC_GAIN_SET_COLLECT:
		   OnSetCollectMusic(srv,socket,value);
		   break;
	   case MUSIC_GAIN_DEL_COLLECT:
		   OnDelCollectMusic(srv,socket,value);
		   break;
	   case MUSIC_GAIN_SET_HATE:
		   OnSetHateMusic(srv,socket,value);
		   break;
	}
    return true;
}

bool Miyologic::OnMiyoClose(struct server *srv,const int socket){

    return true;
}



bool Miyologic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Miyologic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Miyologic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Miyologic::OnIniTimer(struct server *srv){

    return true;
}



bool Miyologic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Miyologic::OnThirdLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){

	scoped_ptr<netcomm_recv::ThirdLogin> login(new netcomm_recv::ThirdLogin(netbase));
	std::string token;
	bool r = false;
	miyosvc_logic::UserInfo abheg_userinfo;
	miyosvc_logic::UserInfo miyo_userinfo;
	int error_code = login->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	abheg_userinfo.set_imei(login->imei());
	abheg_userinfo.set_machine(login->machine());
	abheg_userinfo.set_type(login->source());
	abheg_userinfo.set_nickname(login->nickanme());
	abheg_userinfo.set_sex(login->sex());
	abheg_userinfo.set_birthday(login->birthday());
	abheg_userinfo.set_head(login->head());
	abheg_userinfo.set_session(login->session());
	//深拷贝
	//scoped_ptr<netcomm_recv::ThirdLogin> tlogin(new netcomm_recv::ThirdLogin((netcomm_recv::NetBase*)(login->DeepCopy())));
	login->RemoveElement(L"type");
	login->RemoveElement(L"remote_addr");

	r = miyosvc_logic::DBComm::OnThirdLogin(abheg_userinfo);
	r =miyosvc_logic::MiyoHttpAPI::ThirdLogin(login->Ptr(),miyo_userinfo);
	if(!r)
		return false;
	//写入缓存
	CacheManagerOp::GetWholeCacheManager()->SetMiyoUserInfo(abheg_userinfo.uid(),miyo_userinfo);
	//写入存储介质
	miyosvc_logic::RedisComm::SetMiyoUserInfo(abheg_userinfo.uid(),miyo_userinfo);
	return true;
}


bool Miyologic::OnGainCollectList(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::Collect> collect(new netcomm_recv::Collect(netbase));
	int error_code = collect->GetResult();
	if(error_code!=0){
		send_error(error_code,socket);
		return false;
	}

	bool r = false;

	miyosvc_logic::UserInfo userinfo;
	//替换ID删除多余的参数
	collect->RemoveElement(L"type");
	collect->RemoveElement(L"remote_addr");

	CacheManagerOp::GetWholeCacheManager()->GetMiyoUserInfo(collect->uid(),userinfo);
	collect->set_tid(userinfo.uid());
	collect->set_uid(userinfo.uid());
	std::string content;
	r = miyosvc_logic::MiyoHttpAPI::GainCollectMusicList(collect->Ptr(),content);
	//发送用户
	base_logic::LogicComm::SendFull(socket,content.c_str(),content.length());
	return true;
}

bool Miyologic::OnGainDimensionList(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::Dimension> dimension(new netcomm_recv::Dimension(netbase));
	int error_code = dimension->GetResult();
	if(error_code!=0){
		send_error(error_code,socket);
		return false;
	}

	bool r = false;

	miyosvc_logic::UserInfo userinfo;
	//替换ID删除多余的参数
	dimension->RemoveElement(L"type");
	dimension->RemoveElement(L"remote_addr");

	std::string content;
	CacheManagerOp::GetWholeCacheManager()->GetMiyoUserInfo(dimension->uid(),userinfo);
	dimension->set_uid(userinfo.uid());
	r = miyosvc_logic::MiyoHttpAPI::GainDimensionMusicList(dimension->Ptr(),content);
	//发送用户
	base_logic::LogicComm::SendFull(socket,content.c_str(),content.length());
	return true;
}


bool Miyologic::OnSetCollectMusic(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::SetCollect> collect(new netcomm_recv::SetCollect(netbase));
	int error_code = collect->GetResult();
	if(error_code!=0){
		send_error(error_code,socket);
		return false;
	}

	bool r = false;

	miyosvc_logic::UserInfo userinfo;
	//替换ID删除多余的参数
	collect->RemoveElement(L"type");
	collect->RemoveElement(L"remote_addr");

	std::string content;
	CacheManagerOp::GetWholeCacheManager()->GetMiyoUserInfo(collect->uid(),userinfo);
	collect->set_uid(userinfo.uid());
	r = miyosvc_logic::MiyoHttpAPI::SetCollectMusic(collect->Ptr(),content);
	//发送用户
	base_logic::LogicComm::SendFull(socket,content.c_str(),content.length());
	return true;
}

bool Miyologic::OnDelCollectMusic(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::DelCollect> delcollect(new netcomm_recv::DelCollect(netbase));
	int error_code = delcollect->GetResult();
	if(error_code!=0){
		send_error(error_code,socket);
		return false;
	}

	bool r = false;

	miyosvc_logic::UserInfo userinfo;
	//替换ID删除多余的参数
	delcollect->RemoveElement(L"type");
	delcollect->RemoveElement(L"remote_addr");
	delcollect->set_uid(userinfo.uid());
	std::string content;
	CacheManagerOp::GetWholeCacheManager()->GetMiyoUserInfo(delcollect->uid(),userinfo);
	delcollect->set_uid(userinfo.uid());
	r = miyosvc_logic::MiyoHttpAPI::DelCollectMusic(delcollect->Ptr(),content);
	//发送用户
	base_logic::LogicComm::SendFull(socket,content.c_str(),content.length());
	return true;
}


bool Miyologic::OnSetHateMusic(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::SetHateCollect> sethate(new netcomm_recv::SetHateCollect(netbase));
	int error_code = sethate->GetResult();
	if(error_code!=0){
		send_error(error_code,socket);
		return false;
	}

	bool r = false;

	miyosvc_logic::UserInfo userinfo;
	//替换ID删除多余的参数
	sethate->RemoveElement(L"type");
	sethate->RemoveElement(L"remote_addr");
	sethate->set_uid(userinfo.uid());
	std::string content;
	CacheManagerOp::GetWholeCacheManager()->GetMiyoUserInfo(sethate->uid(),userinfo);
	sethate->set_uid(userinfo.uid());
	r = miyosvc_logic::MiyoHttpAPI::SetHateMusic(sethate->Ptr(),content);
	//发送用户
	base_logic::LogicComm::SendFull(socket,content.c_str(),content.length());
	return true;
}


}

