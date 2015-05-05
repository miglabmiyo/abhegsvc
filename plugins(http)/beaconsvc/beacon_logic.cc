#include "beacon_logic.h"
#include "db_comm.h"
#include "basic/basic_util.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "common.h"

namespace beaconsvc_logic{

Beaconlogic*
Beaconlogic::instance_=NULL;

Beaconlogic::Beaconlogic(){
   if(!Init())
      assert(0);
}

Beaconlogic::~Beaconlogic(){
	beaconsvc_logic::DBComm::Dest();
}

bool Beaconlogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);

	beaconsvc_logic::DBComm::Init(config->mysql_db_list_);
    return true;
}

Beaconlogic*
Beaconlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Beaconlogic();

    return instance_;
}



void Beaconlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Beaconlogic::OnBeaconConnect(struct server *srv,const int socket){

    return true;
}



bool Beaconlogic::OnBeaconMessage(struct server *srv, const int socket, const void *msg,const int len){

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
		case BEACON_SHARK:
			OnSharkBeacon(srv,socket,value);
			break;
	}
    return true;
}

bool Beaconlogic::OnBeaconClose(struct server *srv,const int socket){

    return true;
}



bool Beaconlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Beaconlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Beaconlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Beaconlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Beaconlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Beaconlogic::OnSharkBeacon(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::SharkBeacon> shark(new netcomm_recv::SharkBeacon(netbase));
	bool r = false;
	int error_code = shark->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	//网卡地址
	std::string mac;
	std::string urlcodemac;
	mac = shark->mac();
	if(!shark->mac().empty())
		base::BasicUtil::UrlDecode(mac,urlcodemac);
	else
		urlcodemac = shark->mac();
	beaconsvc_logic::BeaconInfo  info;
	info.set_uuid(shark->uuid());
	info.set_mac(urlcodemac);
	beaconsvc_logic::BeaconMerchant  merchant;

	beaconsvc_logic::DBComm::GetBeaconMerchantInfo(info,merchant);
	scoped_ptr<netcomm_send::SharkBeacon> sshark(new netcomm_send::SharkBeacon());
	sshark->SetBeaconMerChant(merchant.Release());
	send_message(socket,(netcomm_send::HeadPacket*)sshark.get());
	return true;
}

}

