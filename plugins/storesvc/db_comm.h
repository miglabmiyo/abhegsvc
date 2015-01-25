/*
 * db_comm.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#ifndef __ABHEG__STORE__DB_COMM___
#define __ABHEG__STORE__DB_COMM___
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace storesvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();

public:
	static bool GetAppSummary(const int64 appid,const int32 tclass,base_logic::AppInfos& appinfo);

	static bool SearchTypeApp(const int32 type,const int32 tclass,std::list<base_logic::AppInfos>& list);

	static bool GetWantUrl(const int64 appid,const int32 tclass,const int32 machine,
			std::string& url);

	static bool WantAppLike(const int64 uid,const int64 appid,const int32 tclass);
};

}
#endif


