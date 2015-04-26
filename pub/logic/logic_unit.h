/*
 * logic_unit.h
 *
 *  Created on: 2014年12月2日
 *      Author: kerry
 */
#ifndef _BUDDHA_LOGIC_UNIT_H__
#define _BUDDHA_LOGIC_UNIT_H__

#include "logic/logic_infos.h"
#include "net/comm_head.h"
#include "socket/comm_head.h"
namespace base_logic{

class LogicUnit{
public:
	static bool IPToGeocoderAndAddress(netcomm_recv::HeadPacket* packet,
			base_logic::LBSInfos* lbs_infos);

	static base_logic::LBSInfos*  GetGeocderAndAddress(netcomm_recv::HeadPacket* packet);

	static void CreateToken(const int64 uid,std::string& token);

	static void CreateSerialNumber(const int32 platform,const int64 uid,
			const int32 type,const int32 money,std::string& serial_number);

	static void SendMessage(const int socket,netcomm_send::HeadPacket* packet);

	static void SendErrorMsg(const int32 error_code,const int socket);

	static bool SendMessage(const int32 socket,struct PacketHead* packet);

	static bool SendErrorMsg(const int socket,const int32 operator_code,
			const int32 error_code);

	static double CalculationAppStar(const int64 down,const int64 down_total,
			const int64 like,const int64 like_total);

	static double CalculationAppStar(const int64 down,const int64 like);

	static double CalculationBookStar(const int64 free,const int64 down);

	static double CalculationMovieStar(const int64 play,const int64 like);


	static bool RequestGetMethod(const std::string& url,std::string& content,const int count = 3);
	//static double CalculationBookStar(const int64 down,const int64 down_total);
};
}

#define send_error      base_logic::LogicUnit::SendErrorMsg
#define send_message    base_logic::LogicUnit::SendMessage

//通过ID区间判定类别 10000000 为应用  200000000 为游戏
#define TYPE_BASIC              10000000
#define TYPE_BASIC_PARENT       1000
#define TYPE_APP_BASIC          1
#define TYPE_GAME_BASIC         2

#endif

