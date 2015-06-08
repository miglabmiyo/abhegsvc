/*
 * db_comm.h
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */

#ifndef PLUGINS_HTTP__GAMEBOXSVC_DB_COMM_H_
#define PLUGINS_HTTP__GAMEBOXSVC_DB_COMM_H_

#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>

namespace gameboxsvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static bool Init(std::list<base::ConnAddr>& addrlist);
	static bool Dest();
public:
	static bool GetAllGame(std::list<base_logic::AppInfos>& list);
};
}



#endif /* PLUGINS_HTTP__GAMEBOXSVC_DB_COMM_H_ */
