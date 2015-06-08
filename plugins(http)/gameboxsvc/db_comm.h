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
#include <map>
#include <list>

namespace gameboxsvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();
public:
	static bool GetAllGame(std::map<std::string,base_logic::AppInfos>& packet_map,
			std::map<int64,base_logic::AppInfos>& id_map);

	static bool GetAllApp(std::map<std::string,base_logic::AppInfos>& map);

	static bool GetRecommendGame(std::map<int64,base_logic::AppInfos>& map,std::vector<int64>& vec);
};
}



#endif /* PLUGINS_HTTP__GAMEBOXSVC_DB_COMM_H_ */
