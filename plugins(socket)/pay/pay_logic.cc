#include "pay_logic.h"
#include "db_comm.h"
#include "logic/logic_unit.h"
#include "socket/error_comm.h"
#include "logic/logic_comm.h"
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
	struct PacketHead *packet = NULL;
	if (srv == NULL
		||socket<=0
		||msg == NULL
		||len < PACKET_HEAD_LENGTH)
		return false;

	if (!ProtocolPack::UnpackStream(msg,len,&packet)){
		struct PacketHead *ph = (struct PacketHead*) msg;
		LOG_ERROR2("Call UnpackStream failed.operate_code %d packet_length %d len %d",
			ph->operate_code,ph->packet_length,len);
		return false;
	}

	assert (packet);
	LOG_DEBUG2("packet->packet_length[%d],packet->packet_operate[%d],packet->data_length[%d]",
			packet->packet_length,packet->operate_code,packet->data_length);

	//ProtocolPack::HexEncode(msg,len);
	ProtocolPack::DumpPacket(packet);
	switch(packet->operate_code){
		case PAY_USER_LOGIN:
			OnPayUserLogin(srv,socket,packet);
			break;
		case PAY_GET_SMS_CHR_POINT:
			OnGetSMSChrgPoint(srv,socket,packet);
			break;
		case PAY_UPDATE_SERIALNUMBER_STATE:
			OnUpdateSerialnumber(srv,socket,packet);
			break;
		default:
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

bool Paylogic::OnPayUserLogin(struct server *srv, int socket, struct PacketHead *packet,
	           const void *msg, int len){
	//登陆验证
	struct PayUserLogin* login = (struct PayUserLogin*)packet;
	//
	bool r = false;
	paysvc_logic::PayUserInfo userinfo;
	std::string token;
	userinfo.set_imei(login->imei);
	userinfo.set_sim(login->sim);
	r = paysvc_logic::DBComm::OnPayUserLogin(login->platform,userinfo);
	if(!r){//发送错误数据
		base_logic::LogicUnit::SendErrorMsg(socket,PAY_USER_LOGIN_FAILED,PAY_USER_NOT_EXIST);
		return true;
	}
	base_logic::LogicUnit::CreateToken(userinfo.uid(),token);
	struct PayUserLoginSucess login_sucess;
	MAKE_HEAD(login_sucess, PAY_USER_LOGIN_SUCESS,PAY_TYPE,0,0);
	login_sucess.uid = userinfo.uid();
	login_sucess.login_time = time(NULL);
	base::BasicUtil::StringUtil::Copy(login_sucess.token,
			TOKEN_LEN,0,token.c_str(),token.length());
	return base_logic::LogicUnit::SendMessage(socket,&login_sucess);
}

bool Paylogic::OnGetSMSChrgPoint(struct server *srv, int socket, struct PacketHead *packet,
	           const void *msg, int len){
	struct PayGetSMSChrPoint* point = (struct PayGetSMSChrPoint*)packet;
	bool r = false;
	int64 charging_channel = 0;
	std::string serial_number;
	paysvc_logic::ChrPoint chr_point;

	//验证TOKEN
	chr_point.set_type(point->type);
	chr_point.set_flag(point->flag);
	chr_point.set_money(point->money);
	//生成唯一的订单号
	base_logic::LogicUnit::CreateSerialNumber(point->platform,point->uid,point->type,point->money,serial_number);

	//获取计费点 并在数据库生成订单
	r = paysvc_logic::DBComm::OnGetPayChrPoint(point->platform,point->uid,serial_number,chr_point);

	struct PaySendSMSUni sms_uni;
	MAKE_HEAD(sms_uni,PAY_GET_SMS_CHR_POINT,PAY_TYPE,0,0);
	sms_uni.charging_channel = charging_channel;
	base::BasicUtil::StringUtil::Copy(sms_uni.target_number,
			NUMBER_LEN,0,chr_point.phone().c_str(),chr_point.phone().length());
	base::BasicUtil::StringUtil::Copy(sms_uni.target_content,
			CONTENT_LEN,0,chr_point.content().c_str(),chr_point.content().length());
	base::BasicUtil::StringUtil::Copy(sms_uni.serial_number,
			SERIALNUMBER_LEN,0,serial_number.c_str(),serial_number.length());
	return  base_logic::LogicUnit::SendMessage(socket,&sms_uni);
}

bool Paylogic::OnUpdateSerialnumber(struct server *srv, int socket, struct PacketHead *packet,
	           const void *msg, int len){
	struct PayUpdateSerialState* state = (struct PayUpdateSerialState*)packet;
	//操作数据库 更新状态
	bool r = paysvc_logic::DBComm::OnUpdateSerialnumber(state->state,state->serial_number,state->opertor_serial);
	return true;
}
}

