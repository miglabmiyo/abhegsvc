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

bool DBComm::GetTopicsAppStore(std::list<base_logic::Topics>& list){
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

    //call proc_GetTopicsStoreApp()
	os<<"call proc_GetTopicsStoreApp();";
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
			base_logic::Topics topics;
			if(rows[0]!=NULL)
				topics.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				topics.set_name(rows[1]);
			if(rows[2]!=NULL)
				topics.set_pic(rows[2]);
			list.push_back(topics);
		}
		return true;
	}
	return false;
}


bool DBComm::GetAdverAppStore(std::list<base_logic::AdvertInfos>& list){
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

    //call proc_GetAdverStoreApp()
	os<<"call proc_GetAdverStoreApp();";
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
			base_logic::AdvertInfos advertinfo;
			if(rows[0]!=NULL)
				advertinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				advertinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				advertinfo.set_type(atoll(rows[2]));
			if(rows[4]!=NULL)
				advertinfo.set_pic(rows[4]);
			list.push_back(advertinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::GetFindStoreGame(std::list<base_logic::AppInfos>& list){
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

    //call proc_GetFindStoreGame
	os<<"call proc_GetFindStoreGame();";
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


bool DBComm:: GetFindStoreBook(std::list<base_logic::BookInfo>& list){
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

    //call proc_GetFindBookStore()
	os<<"call proc_V2GetFindBookStore()";
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
			base_logic::BookInfo bookinfo;
			if(rows[0]!=NULL)
				bookinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				bookinfo.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				bookinfo.set_parent(atol(rows[2]));
			if(rows[3]!=NULL)
				bookinfo.set_name(rows[3]);
			if(rows[4]!=NULL)
				bookinfo.set_author(rows[4]);
			if(rows[5]!=NULL)
				bookinfo.set_pic(rows[5]);
			if(rows[6]!=NULL)
				bookinfo.set_summary(rows[6]);
			//下载次数
			if(rows[7]!=NULL)
				bookinfo.set_down(atoll(rows[7]));
			//免费试看次数
			if(rows[8]!=NULL)
				bookinfo.set_freecount(atoll(rows[8]));

			if(rows[9]!=NULL)
				bookinfo.set_attr(atol(rows[9]));
			list.push_back(bookinfo);
		}
		return true;
	}
	return false;
}



bool DBComm::GetAdverBookStore(std::list<base_logic::AdvertInfos>& list){
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

    //call proc_GetAdverStoreBook()
	os<<"call proc_GetAdverStoreBook();";
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
			base_logic::AdvertInfos advertinfo;
			if(rows[0]!=NULL)
				advertinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				advertinfo.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				advertinfo.set_pic(rows[2]);
			list.push_back(advertinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::GetTopicsBookStore(std::list<base_logic::Topics>& list){
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

    //call proc_GetTopicsStoreBook()
	os<<"call proc_GetTopicsStoreBook()";
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
			base_logic::Topics topics;
			if(rows[0]!=NULL)
				topics.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				topics.set_name(rows[1]);
			if(rows[2]!=NULL)
				topics.set_pic(rows[2]);
			if(rows[3]!=NULL)
				topics.set_follower(atoll(rows[3]));
			list.push_back(topics);

		}
		return true;
	}
	return false;
}


bool DBComm::GetFindApp(std::list<base_logic::AppInfos>& list){
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

    //call proc_GetFindApp()
	os<<"call proc_GetFindApp();";
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
				appinfo.set_name(rows[4]);
			if(rows[5]!=NULL)
				appinfo.set_logo(rows[5]);
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}


bool DBComm:: GetFindBook(std::list<base_logic::BookInfo>& list){
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

    //call proc_GetFindBook()
	os<<"call proc_GetFindBook()";
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
			base_logic::BookInfo bookinfo;
			if(rows[0]!=NULL)
				bookinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				bookinfo.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				bookinfo.set_parent(atol(rows[2]));
			if(rows[3]!=NULL)
				bookinfo.set_name(rows[3]);
			if(rows[4]!=NULL)
				bookinfo.set_author(rows[4]);
			if(rows[5]!=NULL)
				bookinfo.set_pic(rows[5]);
			if(rows[6]!=NULL)
				bookinfo.set_summary(rows[6]);
			list.push_back(bookinfo);
		}
		return true;
	}
	return false;
}


bool DBComm::GetFindGame(std::list<base_logic::AppInfos>& list){
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

    //call proc_GetFindGame
	os<<"call proc_GetFindGame();";
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
				appinfo.set_name(rows[4]);
			if(rows[5]!=NULL)
				appinfo.set_logo(rows[5]);
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}




bool DBComm::GetAdver(std::list<base_logic::AdvertInfos>& list){
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

    //call proc_GetAdverMain()
	os<<"call proc_GetAdverMain();";
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
			base_logic::AdvertInfos advertinfo;
			if(rows[0]!=NULL)
				advertinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				advertinfo.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				advertinfo.set_subtype(atoll(rows[2]));
			if(rows[3]!=NULL)
				advertinfo.set_pic(rows[3]);
			list.push_back(advertinfo);
		}
		return true;
	}
	return false;
}

}
