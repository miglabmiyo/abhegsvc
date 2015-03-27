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

namespace robotsvc_logic{

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


bool DBComm::GetCTPhoneNumber(std::list<std::string>& list){
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

	os<<"call abheg.proc_GetSpiderPhoneNumber()";

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
			list.push_back(rows[0]);
		}
		return true;
	}
	return true;
}


bool DBComm::CollectionBookInfo(std::list<BookInfo>& list){
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


	while(list.size()>0){
		BookInfo bookinfo = list.front();
		list.pop_front();
		os<<"call buddha.proc_AddBookInfoSummary("<<bookinfo.book_name()<<",\'"
				<<bookinfo.book_hash_name()<<"\',\'"<<bookinfo.book_intro()<<"\',\'"<<bookinfo.book_pubtime()
				<<"\',\'"<<bookinfo.book_author()<<"\',\'"<<bookinfo.book_cover()<<"\',"<<bookinfo.type()<<");";
	}

	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}
	return true;
}

bool DBComm::CollectionBookChapter(std::list<BookChapterCollection>& list){
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
	/*
	 * call buddha.proc_CollectionBookChapter(0,'时间简史','54E0B9C54E105287A72E8077D77941EA',
'我们的宇宙图像','B72FD981CCADD7CAB0B322452651702E','http://game.adadad.com/1.txt')
	 * */

	while(list.size()>0){
		BookChapterCollection collection = list.front();
		list.pop_front();
		os<<"call buddha.proc_CollectionBookChapter("<<collection.book_id()<<",\'"
				<<collection.book_name()<<"\',\'"<<collection.hash_book_name()<<"\',\'"<<collection.chapter_name()
				<<"\',\'"<<collection.hash_chapter_name()<<"\',\'"<<collection.chapter_address()<<"\');";
	}

	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}
	return true;
}

}
