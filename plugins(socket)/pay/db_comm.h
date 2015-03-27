/*
 * db_comm.h
 *
 *  Created on: 2015年3月10日
 *      Author: pro
 */

#ifndef __ABHEG_PAYSVC_DB_COMM_H_
#define __ABHEG_PAYSVC_DB_COMM_H_
#include "pay_basic_info.h"
#include "config/config.h"
#include <list>

namespace paysvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();

	static bool OnPayUserLogin(const int32 platform,paysvc_logic::PayUserInfo& userinfo);

	static bool OnGetPayChrPoint(const int32 platform,const int64 uid,const std::string& serial,
			paysvc_logic::ChrPoint& point);

	static bool OnUpdateSerialnumber(const int32 state,const char* serialnumber,
			const char* operator_serial);
};

}




#endif /* DB_COMM_H_ */
