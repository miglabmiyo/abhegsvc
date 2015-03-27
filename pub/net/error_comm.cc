/*
 * error_comm.cc
 *
 *  Created on: 2014年12月5日
 *      Author: kerry
 */
#include "net/error_comm.h"

const char*
buddha_strerror(int error_code){
	switch (error_code) {
	  case STRUCT_ERROR:
		  return STRUCT_ERROR_STR;
	  case NULL_DATA:
		  return NULL_DATA_STR;
	  case LOGIN_TYPE_LACK:
		  return LOGIN_TYPE_LACK_STR;
	  case IMEI_LACK:
		  return IMEI_LACK_STR;
	  case MACHINE_LACK:
		  return MACHINE_LACK_STR;
	  case SOUCE_LACK:
		  return SOUCE_LACK_STR;
	  case NICKNAME_LACK:
		  return NICKNAME_LACK_STR;
	  case SEX_LACK :
		  return SEX_LACK_STR;
	  case SESSION_LACK:
		  return SESSION_LACK_STR;
	  case PLATFORM_LACK:
		  return PLATFORM_LACK_STR;
	  case UID_LACK:
		  return UID_LACK_STR;
	  case TOKEN_LACK:
		  return TOKEN_LACK_STR;
	  case BD_CHANNEL_LACK:
		  return BD_CHANNEL_LACK_STR;
	  case BD_USERID_LACK:
		  return BD_USER_LACK_STR;
	  case PKG_NAME_LACK :
		  return PKG_NAME_LACK_STR;
	  case APPID_LACK:
		  return APPID_LACK_STR;
	  case BOOK_BTYPE_LACK:
		  return BOOK_BTYPE_LACK_STR;
	  case BOOK_TOKEN_LACK:
		  return BOOK_TOKEN_LACK_STR;
	  case STORE_SEACH_BTYPE_LACK:
		  return STORE_SEACH_BTYPE_LACK_STR;
	  case STORE_SEARCH_KEY_LACK:
		  return STORE_SEARCH_KEY_LACK_STR;
	  case PAY_USER_LACK:
		  return PAY_USER_LACK_STR;
	  case SERIAL_NUMBER_LACK:
		  return SERIAL_NUMBER_LACK_STR;
	  case STATE_LACK:
		  return STATE_LACK_STR;
	  case MONEY_LACK:
		  return MONEY_LACK_STR;
	  case SIGN_LACK:
		  return SIGN_LACK_STR;
	  default:
		  return "未知错误";
	}
}


