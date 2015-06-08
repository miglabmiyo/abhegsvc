/*
 * mysql_crawl_wdj_storage.cc
 *
 *  Created on: 2015年5月25日
 *      Author: Administrator
 */
#include "mysql_crawl_storage.h"
#include "db/base_db_mysql_auto.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{


void MysqlCrawlStorage::Init(std::list<base::ConnAddr>& addrlist){

}

void MysqlCrawlStorage::Release(){

}


bool MysqlCrawlStorage::WriteData(const int32 type,base_logic::Value* value){
	return true;
}


bool MysqlCrawlStorage::ReadData(const std::string& sql,base_logic::Value* value,
		void (*storage_get)(void*,base_logic::Value*)){
	bool r = false;
	base_db::AutoMysqlCommEngine auto_engine;
	base_storage::DBStorageEngine* engine  = auto_engine.GetDBEngine();
	if (engine==NULL){
		LOG_ERROR("GetConnection Error");
		return false;
	}
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}

	if(storage_get==NULL)
		return r;
	storage_get((void*)(engine),value);
	return r;
}


}



