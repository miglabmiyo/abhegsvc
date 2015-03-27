#ifndef __ABHEG_PAY_SOCKET_COMM_HEAD_H__
#define __ABHEG_PAY_SOCKET_COMM_HEAD_H__
#include "basic/basictypes.h"
#include <list>
#include <string>


#define IMEI_LEN      			32
#define SIM_LEN       			32
#define TOKEN_LEN     			32
#define NUMBER_LEN    			32
#define CONTENT_LEN   			64
#define SERIALNUMBER_LEN        128
enum socketoperatorcode
{
	HEART_PACKET = 100,
	PAY_USER_LOGIN = 6000,
	PAY_USER_LOGIN_SUCESS = 6001,
	PAY_USER_LOGIN_FAILED = 6002,
	PAY_GET_SMS_CHR_POINT = 6011, //获取计费点
	PAY_SEND_SMS_UNI = 6012,//返回三网融合计费点
	PAY_UPDATE_SERIALNUMBER_STATE = 6021
};

enum msgtype
{
	ERROR_TYPE = 0,
	PAY_TYPE = 1,
};

enum chargetype
{
	PLAY_CHANNEL = 0 //电信爱游戏渠道
};

struct PacketHead{
   int32 packet_length;//4
   int32 operate_code; //4
   int32 data_length;//4
   int32 msg_id;//4
   int64 current_time;//8
   int64 reserverd;//8
   int16 is_zip;//2
   int16 msg_type;//2
}; //36
#define PACKET_HEAD_LENGTH (sizeof(int32) * 4 + sizeof(int16) * 2 + sizeof(int64) * 2)

//PAY_USER_LOGIN = 6000
#define PAY_USER_LOGIN_SIZE (sizeof(int32) + IMEI_LEN + SIM_LEN) //68
struct PayUserLogin:public PacketHead{
	int32 platform;
	char imei[IMEI_LEN];
	char sim[SIM_LEN];
};

//PAY_USER_LOGIN_SUCESS = 6001
#define PAY_USER_LOGIN_SUCESS_SIZE (sizeof(int64) * 2 + TOKEN_LEN)
struct PayUserLoginSucess:public PacketHead
{
	int64 uid;
	int64 login_time;
	char  token[TOKEN_LEN];
};

//PAY_USER_LOGIN_FAILED = 6002
#define ERROR_PACKET_SIZE (sizeof(int32))
struct ErrorPacket:public PacketHead{
	int32 error_code;
};

//PAY_GET_SMS_CHR_POINT = 6011
#define PAY_GET_SMS_CHR_POINT_SIZE (sizeof(int64) + sizeof(int32) * 4 + TOKEN_LEN)
struct PayGetSMSChrPoint:public PacketHead
{
	int32  platform;
	int64  uid; //用户ID
	int32  type; //类别 //单机或弱联网游戏为0 联网游戏为1
	int32  flag; // 计费类型 // 全网0 电信1 移动2 联通3
	int32  money; //金额
	char   token[TOKEN_LEN];
};

//PAY_SEND_SMS_UNI = 6012
#define PAY_SEND_SMS_UNI_SIZE (sizeof(int32) + NUMBER_LEN + CONTENT_LEN + SERIALNUMBER_LEN)
struct PaySendSMSUni:public PacketHead
{
	int32       charging_channel; //计费渠道
	char        target_number[NUMBER_LEN];//目标号码
	char        target_content[CONTENT_LEN];//内容
	char        serial_number[SERIALNUMBER_LEN];//流水号
};

//PAY_UPDATE_SERIALNUMBER_STATE
#define PAY_UPDATE_SERIALNUMBER_STATE_SIZE (sizeof(int32) + SERIALNUMBER_LEN * 2)
struct PayUpdateSerialState:public PacketHead{
	int32 state; //1 成功 -1失败
	char serial_number[SERIALNUMBER_LEN];//流水号
	char opertor_serial[SERIALNUMBER_LEN];//运营商流水号
};


#endif
