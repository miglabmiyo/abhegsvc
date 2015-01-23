/*
 * db_comm.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#include "db_comm.h"
#include "db/base_db_mysql_auto.h"
#include <sstream>
#include <mysql.h>

namespace findsvc_logic{

void DBComm::Init(std::list<base::ConnAddr>& addrlist){
#if defined (_DB_POOL_)
	base_db::MysqlDBPool::Init(addrlist);
#endif
}

void DBComm::Dest(){
#if defined (_DB_POOL_)
	base_db::MysqlDBPool::Dest();
#endif
}

bool DBComm::GetFindStoreApp(std::list<base_logic::AppInfos>& list){
	bool r = false;
#if defined (_DB_POOL_)
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
#endif
	std::stringstream os;
	MYSQL_ROW rows;

	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}

    //call proc_GetFindStoreApp()
	os<<"call proc_GetFindStoreApp();";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}


	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			base_logic::AppInfos appinfo;
			if(rows[0]!=NULL)
				appinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				appinfo.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				appinfo.set_down(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_like(atoll(rows[3]));
			if(rows[4]!=NULL)
				appinfo.set_attr(atol(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_name(rows[5]);
			if(rows[6]!=NULL)
				appinfo.set_logo(rows[6]);
			if(rows[7]!=NULL)
				appinfo.set_summary(rows[7]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}

}
