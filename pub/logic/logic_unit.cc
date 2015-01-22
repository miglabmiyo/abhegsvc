/*
 * logic_unit.cc
 *
 *  Created on: 2014年12月2日
 *      Author: kerry
 */
#include "logic/logic_unit.h"
#include "net/comm_head.h"
#include "net/error_comm.h"
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
/*
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
}*/


}
