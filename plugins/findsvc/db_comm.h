/*
 * db_comm.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#ifndef __ABHEG__FINDSVC__DB_COMM___
#define __ABHEG__FINDSVC__DB_COMM___
//#include "user_basic_info.h"
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace findsvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();
public:
	static bool GetFindStoreApp(std::list<base_logic::AppInfos>& list);
};

}
#endif


