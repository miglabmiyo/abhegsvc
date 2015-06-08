/*
 * db_comm.cc
 *
 *  Created on: 2015年6月8日
 *      Author: Administrator
 */
#include "db_comm.h"
#include "db/base_db_mysql_auto.h"
#include <sstream>
#include <mysql.h>

namespace gameboxsvc_logic{

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

bool DBComm::GetRecommendGame(std::map<int64,base_logic::AppInfos>& map,std::vector<int64>& vec){
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

    //call proc_GetRecommendGame()
	os<<"call proc_GetRecommendGame();";
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

			map[appinfo.id()] = appinfo;
			vec.push_back(atoll(rows[0]));
		}
		return true;
	}
	return false;
}


bool DBComm::GetAllApp(std::map<std::string,base_logic::AppInfos>& map){
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

    //call proc_GetAPPInfo()
	os<<"call proc_GetAPPInfo();";
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
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_down(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_introduction(rows[5]);
			if(rows[6]!=NULL)
				appinfo.set_like(atoll(rows[6]));
			if(rows[7]!=NULL)
				appinfo.set_packetname(rows[7]);
			if(rows[8]!=NULL)
				appinfo.set_provider(rows[8]);
			if(rows[9]!=NULL)
				appinfo.set_android_url(rows[9]);
			if(rows[10]!=NULL)
				appinfo.set_content(rows[10]);
			map[appinfo.packetname()] = appinfo;
		}
		return true;
	}
	return false;
}

bool DBComm::GetAllGame(std::map<std::string,base_logic::AppInfos>& packet_map,
		std::map<int64,base_logic::AppInfos>& id_map){
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

    //call proc_GetGameInfo()
	os<<"call proc_GetGameInfo();";
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
				appinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				appinfo.set_type(atoll(rows[2]));
			if(rows[3]!=NULL)
				appinfo.set_logo(rows[3]);
			if(rows[4]!=NULL)
				appinfo.set_down(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_introduction(rows[5]);
			if(rows[6]!=NULL)
				appinfo.set_like(atoll(rows[6]));
			if(rows[7]!=NULL)
				appinfo.set_packetname(rows[7]);
			if(rows[8]!=NULL)
				appinfo.set_provider(rows[8]);
			if(rows[9]!=NULL)
				appinfo.set_android_url(rows[9]);
			if(rows[10]!=NULL)
				appinfo.set_content(rows[10]);
			packet_map[appinfo.packetname()] = appinfo;
			id_map[appinfo.id()] = appinfo;
		}
		return true;
	}
	return false;
}

}



