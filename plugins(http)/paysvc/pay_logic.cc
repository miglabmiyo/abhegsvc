#include "pay_logic.h"
#include "db_comm.h"
#include "logic/logic_infos.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "net/pay_comm_head.h"
#include "common.h"

namespace paysvc_logic{

Paylogic*
Paylogic::instance_=NULL;

Paylogic::Paylogic(){
   if(!Init())
      assert(0);
}

Paylogic::~Paylogic(){
	paysvc_logic::DBComm::Dest();
}

bool Paylogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);

	paysvc_logic::DBComm::Init(config->mysql_db_list_);
    return true;
}

Paylogic*
Paylogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Paylogic();

    return instance_;
}



void Paylogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Paylogic::OnPayConnect(struct server *srv,const int socket){

    return true;
}



bool Paylogic::OnPayMessage(struct server *srv, const int socket, const void *msg,const int len){
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
		case PAY_PHONE_REGISTER:
			OnPhoneRegister(srv,socket,value);
			break;
		case PAY_PHONE_LOGIN:
			OnPayUserLogin(srv,socket,value);
			break;
		case PAY_GET_CHR:
			OnGetSMSChrgPoint(srv,socket,value);
			break;
		case PAY_UPDATE_STATE:
			OnUpdateSerialnumber(srv,socket,value);
			break;
	}

    return true;
}

bool Paylogic::OnPayClose(struct server *srv,const int socket){

    return true;
}



bool Paylogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Paylogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Paylogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Paylogic::OnIniTimer(struct server *srv){

    return true;
}



bool Paylogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Paylogic::OnPhoneRegister(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){

	//
	scoped_ptr<netcomm_recv::PhoneRegister> phone_regiser(new netcomm_recv::PhoneRegister(netbase));
	bool r = false;
	int error_code = phone_regiser->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	//注册数据库
	paysvc_logic::DBComm::OnPayUserRegister(phone_regiser->platform(),phone_regiser->imei(),
			phone_regiser->phone_number(),phone_regiser->sim(),phone_regiser->pkg_name());

	//回复包头
	scoped_ptr<netcomm_send::HeadPacket> qphone_register(new netcomm_send::HeadPacket);
	qphone_register->set_status(1);
	send_message(socket,(netcomm_send::HeadPacket*)qphone_register.get());
	return true;

}

bool Paylogic::OnPayUserLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
		const void* msg,const int len){
	scoped_ptr<netcomm_recv::PayUserLogin> user_login(new netcomm_recv::PayUserLogin(netbase));
	bool r = false;
	int error_code = user_login->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	paysvc_logic::PayUserInfo userinfo;
	std::string token;
	userinfo.set_imei(user_login->imei());
	userinfo.set_sim(user_login->sim());
	r = paysvc_logic::DBComm::OnPayUserLogin(user_login->platform(),userinfo);
	if(!r){
		send_error(PAY_USER_LACK,socket);
		return false;
	}

	base_logic::LogicUnit::CreateToken(userinfo.uid(),token);
	//发送信息
	scoped_ptr<netcomm_send::PayUserLogin> quser_login(new netcomm_send::PayUserLogin);
	quser_login->set_token(token);
	quser_login->set_uid(userinfo.uid());
	quser_login->set_login_time(time(NULL));
	send_message(socket,(netcomm_send::HeadPacket*)quser_login.get());
	return true;
}


bool Paylogic::OnGetSMSChrgPoint(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::PayGetSMSChrPoint> point(new netcomm_recv::PayGetSMSChrPoint(netbase));
	bool r = false;
	int error_code = point->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	int64 charging_channel = 0;
	std::string serial_number;
	paysvc_logic::ChrPoint chr_point;

	//验证TOKEN
	//生成唯一的订单号
	base_logic::LogicUnit::CreateSerialNumber(point->platform(),point->uid(),time(NULL),time(NULL),serial_number);

	//获取计费点 并在数据库生成订单
	r = paysvc_logic::DBComm::OnGetPayChrPoint(point->platform(),point->uid(),point->paynumber(),
			serial_number,chr_point);
	if(!r){
		send_error(error_code,socket);
		return true;
	}
	//发送消息
	scoped_ptr<netcomm_send::PayGetSMSChrPoint> qpoint(new netcomm_send::PayGetSMSChrPoint);
	qpoint->set_charging_channel(charging_channel);
	qpoint->set_serial_number(serial_number);
	qpoint->set_tagrget_number(chr_point.phone());
	qpoint->set_target_content(chr_point.content());
	qpoint->set_remark(chr_point.remark());
	send_message(socket,(netcomm_send::HeadPacket*)qpoint.get());
	return true;
}

bool Paylogic::OnUpdateSerialnumber(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::PayUpdateSerialState> state(new netcomm_recv::PayUpdateSerialState(netbase));
	bool r = false;
	int error_code = state->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	r = paysvc_logic::DBComm::OnUpdateSerialnumber(state->state(),state->serial_number().c_str(),
			state->opertor_serial().c_str());
	scoped_ptr<netcomm_send::HeadPacket> head(new netcomm_send::HeadPacket);
	head->set_status(1);
	send_message(socket,(netcomm_send::HeadPacket*)head.get());
	return true;
}

}

