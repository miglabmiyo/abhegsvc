#include "user_logic.h"
#include "user_basic_info.h"
#include "db_comm.h"
#include "logic/logic_unit.h"
#include "logic/logic_infos.h"
#include "lbs/lbs_connector.h"
#include "lbs/lbs_logic_unit.h"
#include "basic/scoped_ptr.h"
#include "pushmsg/basic_push_info.h"
#include "logic/logic_comm.h"
#include "config/config.h"
#include "common.h"

namespace usersvc_logic{

Userlogic*
Userlogic::instance_=NULL;

Userlogic::Userlogic(){
   if(!Init())
      assert(0);
}

Userlogic::~Userlogic(){
}

bool Userlogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL){
		return false;
	}
	r = config->LoadConfig(path);
	base_lbs::LbsConnectorEngine::Create(base_lbs::IMPL_BAIDU);
	base_lbs::LbsConnector* engine = base_lbs::LbsConnectorEngine::GetLbsConnectorEngine();
	engine->Init(config->mysql_db_list_);
    return true;
}

Userlogic*
Userlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Userlogic();

    return instance_;
}



void Userlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Userlogic::OnUserConnect(struct server *srv,const int socket){

    return true;
}



bool Userlogic::OnUserMessage(struct server *srv, const int socket, const void *msg,const int len){

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
		case QUICK_LOGIN:
			OnQuickLogin(srv,socket,value);
			break;
		case THIRID_LOGIN:
			OnThirdLogin(srv,socket,value);
			break;
	}

	return true;
}

bool Userlogic::OnUserClose(struct server *srv,const int socket){

    return true;
}



bool Userlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Userlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Userlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Userlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Userlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}


bool Userlogic::OnQuickLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::QucikLogin> login(new netcomm_recv::QucikLogin(netbase));
	scoped_ptr<base_logic::LBSInfos> lbs_info;
	usersvc_logic::UserInfo userinfo;
	std::string token;
	bool r = false;
	int error_code = login->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//获取地址
	lbs_info.reset(base_logic::LogicUnit::GetGeocderAndAddress((netcomm_recv::HeadPacket*)login.get()));
	if(r)
		login.get()->Reset();
	userinfo.set_imei(login->imei());
	userinfo.set_machine(login->machine());
	//存储用户信息
	usersvc_logic::DBComm::OnQuickRegister(userinfo,lbs_info.get());
	base_logic::LogicUnit::CreateToken(userinfo.uid(),token);
	scoped_ptr<netcomm_send::Login> qlogin(new netcomm_send::Login());


	qlogin->set_userinfo_address(userinfo.city());
	qlogin->set_userinfo_token(token);
	qlogin->set_userinfo_uid(userinfo.uid());
	qlogin->set_userinfo_nickname(userinfo.nickname());
	qlogin->set_userinfo_source(userinfo.type());
	qlogin->set_useromfo_head(userinfo.head());
	send_message(socket,(netcomm_send::HeadPacket*)qlogin.get());
	return true;
}

bool Userlogic::OnThirdLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::ThirdLogin> login(new netcomm_recv::ThirdLogin(netbase));
	scoped_ptr<base_logic::LBSInfos> lbs_info;
	usersvc_logic::UserInfo userinfo;
	std::string token;
	bool r = false;
	int error_code = login->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	//获取地址
	lbs_info.reset(base_logic::LogicUnit::GetGeocderAndAddress((netcomm_recv::HeadPacket*)login.get()));
	if(r)
		login.get()->Reset();
	userinfo.set_imei(login->imei());
	userinfo.set_machine(login->machine());
	userinfo.set_type(login->source());
	userinfo.set_nickname(login->nickanme());
	userinfo.set_sex(login->sex());
	userinfo.set_birthday(login->birthday());
	userinfo.set_head(login->head());
	userinfo.set_session(login->session());
	//存储用户信息
	usersvc_logic::DBComm::OnThirdLogin(userinfo,lbs_info.get());
	base_logic::LogicUnit::CreateToken(userinfo.uid(),token);
	scoped_ptr<netcomm_send::Login> qlogin(new netcomm_send::Login());

	qlogin->set_userinfo_address(userinfo.city());
	qlogin->set_userinfo_token(token);
	qlogin->set_userinfo_uid(userinfo.uid());
	qlogin->set_userinfo_nickname(userinfo.nickname());
	qlogin->set_userinfo_source(userinfo.type());
	qlogin->set_useromfo_head(userinfo.head());
	send_message(socket,(netcomm_send::HeadPacket*)qlogin.get());
	return true;
}

bool Userlogic::OnBDBindPush(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
   		const void* msg,const int len){
	scoped_ptr<netcomm_recv::BDBindPush> bind(new netcomm_recv::BDBindPush(netbase));
	/*
	 * const int64 platform,const int64 uid,const int64 channel,const int64 bd_userid,
			const std::string& pkg_name,const std::string& tag,const int64 appid,
			const int64 requestid,const int32 machine)
	 * */
	base_push::BaiduBindPushInfo bindinfo(bind->platform(),bind->uid(),bind->channel(),
			bind->bduserid(),bind->pkg_name(),bind->tag(),bind->appid(),bind->request(),
			bind->machine());


}

}

