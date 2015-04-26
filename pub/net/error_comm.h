/*
 * error_comm.h
 *
 *  Created on: 2014年12月5日
 *      Author: kerry
 */

#ifndef ERROR_COMM_H_
#define ERROR_COMM_H_

enum neterrorcode{
	STRUCT_ERROR = -100,
	NULL_DATA = -200,
	////用户管理相关错误
	//登陆
	LOGIN_TYPE_LACK = -1100,
	IMEI_LACK = -1101,
	MACHINE_LACK = -1102,
	SOUCE_LACK = -1103,
	NICKNAME_LACK = -1104,
	SEX_LACK = -1105,
	SESSION_LACK = -1106,
	PLATFORM_LACK = -1107,
	UID_LACK = -1108,
	TOKEN_LACK = -1109,
	PHONE_LACK = -1110,

	//推送绑定
	BD_CHANNEL_LACK = -1200,
	BD_USERID_LACK = -1201,
	PKG_NAME_LACK = -1202,
	TAG_LACK = -1203,
	APPID_LACK = -1204,
	REQUEST_LACK = -1205,


	//书城
	BOOK_BTYPE_LACK = -1300,
	BOOK_ID_LACK = -1301,
	BOOK_TOKEN_LACK = -1302,

	//商城
	STORE_SEACH_BTYPE_LACK = -1400,

	SEARCH_KEY_LACK = -1401,

	//影音
	MOVIE_ID_LACK = -1500,
	MOVIE_BTYPE_LACK = -1501,

	//支付相关
	SIM_LACK = -1111,
	SIGN_LACK = -1113,
	MONEY_LACK = -1114,
	STATE_LACK = -1115,
	SERIAL_NUMBER_LACK = -1116,
	PAY_USER_LACK = -1117,

	//机器人相关
	MOVIE_CONTENT_LACK = -1200,

	//beacon
	BEACON_MAC_LACK = -1600,
	BEACON_UUID_LACK = -1601

};


#define STRUCT_ERROR_STR                  "请求结构错误"
#define NULL_DATA_STR                     "空数据"

////USER PLUGIN////
#define LOGIN_TYPE_LACK_STR               "登陆类别不存在"
#define IMEI_LACK_STR                     "缺少IMEI"
#define MACHINE_LACK_STR                  "缺少机型"
#define SOUCE_LACK_STR                    "缺少登陆来源"
#define NICKNAME_LACK_STR                 "缺少昵称"
#define SEX_LACK_STR                      "缺少性别"
#define SESSION_LACK_STR                  "缺少第三方凭据"
#define PLATFORM_LACK_STR                 "缺少第三方平台信息"
#define UID_LACK_STR                      "缺少用户ID"
#define TOKEN_LACK_STR                    "TOKEN不存在或错误"
#define SIGN_LACK_STR                     "sign不存在或错误"
#define PHONE_LACK_STR                    "缺少电话号码"

#define BD_CHANNEL_LACK_STR               "缺少百度绑定信息"
#define BD_USER_LACK_STR                  "缺少百度ID"
#define PKG_NAME_LACK_STR                 "缺少包名"
#define TAG_LACK_STR                      "缺少标签"
#define APPID_LACK_STR                    "缺少APPID"
#define REQUEST_LACK_STR                  "缺少请求ID"

#define BOOK_BTYPE_LACK_STR               "缺少书类别"
#define BOOK_ID_LACK_STR                  "缺少书ID"
#define BOOK_TOKEN_LACK_STR               "此书并未购买"

#define MOVIE_ID_LACK_STR                 "影视ID不存在"

#define STORE_SEACH_BTYPE_LACK_STR        "缺少类别"
#define STORE_SEARCH_KEY_LACK_STR         "缺少关键字"

#define MONEY_LACK_STR                    "缺少金额"
#define STATE_LACK_STR                    "缺少状态"
#define SERIAL_NUMBER_LACK_STR            "缺少流水号"
#define PAY_USER_LACK_STR                 "用户未注册"


#define MOVIE_CONTENT_LACK_STR            "缺少电影内容"

#define BEACON_MAC_LACK_STR               "缺少网卡地址"
#define BEACON_UUID_LACK_STR              "缺少设备号"


const char*
buddha_strerror(int error_code);
#endif /* ERROR_COMM_H_ */
