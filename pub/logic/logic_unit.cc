/*
 * logic_unit.cc
 *
 *  Created on: 2014年12月2日
 *      Author: kerry
 */
#include "logic/logic_unit.h"
#include "net/comm_head.h"
#include "net/error_comm.h"
#include "socket/protocol.h"
#include "lbs/lbs_connector.h"
#include "logic/logic_comm.h"
#include "basic/scoped_ptr.h"
#include "basic/basic_util.h"
#include "basic/md5sum.h"
#include "basic/radom_in.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
namespace base_logic{

base_logic::LBSInfos* LogicUnit::GetGeocderAndAddress(netcomm_recv::HeadPacket* packet){
	std::string latitude;
	std::string longitude;
	std::string city;
	std::string district;
	std::string province;
	std::string street;
	double latitude_double = 0;
	double longitude_double = 0;
	bool r = false;
	std::string host = packet->remote_addr();
	base_lbs::LbsConnector* engine = base_lbs::LbsConnectorEngine::GetLbsConnectorEngine();
	if(packet->latitude()==0||packet->longitude()==0){//ip获取地址
		bool r = engine->IPtoAddress(host,latitude_double,
				longitude_double,city,district,province,street);
		if(!r)
			return false;
		/*const std::wstring num_wstring_latitude(latitude.begin(),latitude.end());
		const std::string  num_string_latitude =  base::BasicUtil::StringConversions::WideToASCII(num_wstring_latitude);
		if(base::BasicUtil::StringUtil::StringToDouble(num_string_latitude,&latitude_double)&&finite(latitude_double))
			packet->set_latitude(latitude_double);


		const std::wstring num_wstring_longitude(longitude.begin(),longitude.end());
		const std::string  num_string_longitude =  base::BasicUtil::StringConversions::WideToASCII(num_wstring_longitude);
		if(base::BasicUtil::StringUtil::StringToDouble(num_string_longitude,&longitude_double)&&finite(longitude_double))
			packet->set_latitude(latitude_double);*/
	}else{

		latitude_double = packet->latitude();
		longitude_double = packet->longitude();
		r = engine->GeocoderForAddress(latitude_double,longitude_double,city,district,province,street);
		if(!r)
			return false;
	}

	scoped_ptr<base_logic::LBSInfos>temp_lbs(new base_logic::LBSInfos(host,latitude_double,longitude_double,
			city,district,province,street));
	return temp_lbs.release();


}
bool LogicUnit::IPToGeocoderAndAddress(netcomm_recv::HeadPacket* packet,
		base_logic::LBSInfos* lbs_infos){
	std::string latitude;
	std::string longitude;
	std::string city;
	std::string district;
	std::string province;
	std::string street;
	double latitude_double;
	double longitude_double;
	std::string host = packet->remote_addr();
	base_lbs::LbsConnector* engine = base_lbs::LbsConnectorEngine::GetLbsConnectorEngine();
	bool r = engine->IPtoAddress(host,latitude_double,
			longitude_double,city,district,province,street);
	if(!r)
		return false;

	/*const std::wstring num_wstring_latitude(latitude.begin(),latitude.end());
		const std::string  num_string_latitude =  base::BasicUtil::StringConversions::WideToASCII(num_wstring_latitude);
		if(base::BasicUtil::StringUtil::StringToDouble(num_string_latitude,&latitude_double)&&finite(latitude_double))
				packet->set_latitude(latitude_double);


	const std::wstring num_wstring_longitude(longitude.begin(),longitude.end());
	const std::string  num_string_longitude =  base::BasicUtil::StringConversions::WideToASCII(num_wstring_longitude);
	if(base::BasicUtil::StringUtil::StringToDouble(num_string_longitude,&longitude_double)&&finite(longitude_double))
					packet->set_latitude(latitude_double);*/

	scoped_ptr<base_logic::LBSInfos>temp_lbs(new base_logic::LBSInfos(host,latitude_double,longitude_double,
			city,district,province,street));

	lbs_infos = temp_lbs.get();
	return true;
}



void LogicUnit::CreateToken(const int64 uid,std::string& token){
	std::stringstream os;
	os<<uid;
	//create token
	int32 random_num = base::SysRadom::GetInstance()->GetRandomID();
	//md5
	token="miglab";
	std::string key;
	os<<random_num;
	base::MD5Sum md5(os.str());
	token = md5.GetHash();
}

void LogicUnit::CreateSerialNumber(const int32 platform,const int64 uid,
		const int32 type,const int32 money,std::string& serial_number){
	std::stringstream os;
	int32 random_num = base::SysRadom::GetInstance()->GetRandomID();
	random_num = abs(random_num);
	os<<money<<random_num<<platform<<uid<<type;
	serial_number = os.str();
}

void LogicUnit::SendMessage(const int socket,netcomm_send::HeadPacket* packet){
	std::string json;
	packet->GetJsonSerialize(&json);
	LOG_DEBUG2("%s",json.c_str());
	base_logic::LogicComm::SendFull(socket,json.c_str(),json.length());
}

void LogicUnit::SendErrorMsg(const int32 error_code,const int socket){
	scoped_ptr<netcomm_send::HeadPacket> packet(new netcomm_send::HeadPacket());
	std::string error_msg = buddha_strerror(error_code);
	packet->set_flag(error_code);
	packet->set_msg(error_msg);
	packet->set_status(0);
	SendMessage(socket,packet.get());
}

bool LogicUnit::SendErrorMsg(const int socket,const int32 operator_code,
			const int32 error_code){
	struct ErrorPacket error;
	MAKE_HEAD(error, operator_code,ERROR_TYPE,0,0);
	error.error_code = error_code;
	SendMessage(socket,&error);
	return true;
}

bool LogicUnit::SendMessage(const int32 socket,struct PacketHead* packet){

	bool r = false;
	void *packet_stream = NULL;
	int32 packet_stream_length = 0;
	int32 ret = 0;
	if (socket <= 0 || packet == NULL)
		return false;

	if (ProtocolPack::PackStream (packet, &packet_stream, &packet_stream_length) == false) {
		LOG_ERROR2 ("Call PackStream failed in %s:%d", file, line);
		r = false;
		goto MEMFREE;
	}
	//LOG_DEBUG2("opcode[%d]\n",packet->operate_code);
	ProtocolPack::DumpPacket(packet);
	ret = base_logic::LogicComm::SendFull(socket, (char *) packet_stream, packet_stream_length);
	//ProtocolPack::HexEncode(packet_stream,packet_stream_length);
	if (ret != packet_stream_length) {
		LOG_ERROR2 ("Sent msg failed in %s:%d", file, line);
		r = false;
		goto MEMFREE;
	} else {
		r = true;
		goto MEMFREE;
	}
MEMFREE:
	char* stream = (char*)packet_stream;
	if (stream){
		delete[] stream;
		stream = NULL;
	}
	return r;
}

//（单个下载次数%所有下载总次数）*30% + （单个点赞次数%所有点赞总次数）*70%

double LogicUnit::CalculationAppStar(const int64 down,const int64 down_total,
		const int64 like,const int64 like_total){
     double down_weight = ((down*100/down_total) * 0.3)/100;
     double like_weight = ((like*100/like_total) * 0.7)/100;
     return (down_weight+like_weight) *10;
}

/*double LogicUnit::CalculationBookStar(const int64 down,const int64 down_total){
	 double down_weight = ((down*100/down_total) * 1)/100;
	 return 3.5;
}*/


/*
 * like 为 5-4星  其中60%为5星  40%为星
 *
 * down 为 3-1星 其中 50%为3星 30%为2星 20%为1星.
 *
 * 50.6%×5+35.7%×4+12.1%×3+1.2%×2+0.3%×1=4.348星
 * */
double LogicUnit::CalculationAppStar(const int64 down,const int64 like){
	double fiveper  = (like * 0.6) /(down+like);
	double fourper  = (like * 0.4) /(down+like);
	double threeper  = (down * 0.5) /(down+like);
	double twoper  = (down * 0.3) /(down+like);
	double oneper  = (down * 0.2) /(down+like);

	double star  =  (fiveper * 100 *5) + (fourper * 100 *4) + (threeper * 100 *3) + (twoper * 100 *2)+(oneper * 100 *1);
	return star/100>5?5:(star/100);
}

/*
 * down 为 5-4星  其中60%为5星  40%为星
 *
 * free 为 3-1星 其中 50%为3星 30%为2星 20%为1星.
 *
 * 50.6%×5+35.7%×4+12.1%×3+1.2%×2+0.3%×1=4.348星
 * */

double LogicUnit::CalculationBookStar(const int64 free,const int64 down){
	double fiveper  = (down * 0.6) /(free+down);
	double fourper  = (down * 0.4) /(down+free);
	double threeper  = (free * 0.5) /(down+free);
	double twoper  = (free * 0.3) /(down+free);
	double oneper  = (free * 0.2) /(down+free);

	double star  =  (fiveper * 100 *5) + (fourper * 100 *4) + (threeper * 100 *3) + (twoper * 100 *2)+(oneper * 100 *1);
	return star/100>5?5:(star/100);
}

double LogicUnit::CalculationMovieStar(const int64 play,const int64 like){
	double fiveper  = (like * 0.6) /(play+like);
	double fourper  = (like * 0.4) /(play+like);
	double threeper  = (play * 0.5) /(play+like);
	double twoper  = (play * 0.3) /(play+like);
	double oneper  = (play * 0.2) /(play+like);

	double star  =  (fiveper * 100 *5) + (fourper * 100 *4) + (threeper * 100 *3) + (twoper * 100 *2)+(oneper * 100 *1);
	return star/100>5?5:(star/100);
}


}
