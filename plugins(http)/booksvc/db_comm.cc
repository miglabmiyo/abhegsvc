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

namespace booksvc_logic{

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

bool DBComm::GetBookTopics(const int64 tid,std::list<base_logic::BookInfo>& list){
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

    //call proc_GetBookTopics(5)
	os<<"call proc_V2GetBookTopics("<<tid<<")";
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
				bookinfo.set_down(atol(rows[3]));
			if(rows[4]!=NULL)
				bookinfo.set_name(rows[4]);
			if(rows[5]!=NULL)
				bookinfo.set_author(rows[5]);
			if(rows[6]!=NULL)
				bookinfo.set_pic(rows[6]);
			if(rows[7]!=NULL)
				bookinfo.set_freecount(atoll(rows[7]));
			if(rows[8]!=NULL)
				bookinfo.set_summary(rows[8]);
			list.push_back(bookinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::GetBookSearch(const int32 type,std::list<base_logic::BookInfo>& list){
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

    //call proc_GetBooksByType(1001)
	os<<"call proc_V2GetBooksByType("<<type<<")";
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
				bookinfo.set_down(atoll(rows[3]));
			if(rows[4]!=NULL)
				bookinfo.set_attr(atol(rows[4]));
			if(rows[5]!=NULL)
				bookinfo.set_name(rows[5]);
			if(rows[6]!=NULL)
				bookinfo.set_author(rows[6]);
			if(rows[7]!=NULL)
				bookinfo.set_pic(rows[7]);
			if(rows[8]!=NULL)
				bookinfo.set_freecount(atoll(rows[8]));
			if(rows[9]!=NULL)
				bookinfo.set_summary(rows[9]);
			list.push_back(bookinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::OnWantGetBook(const int64 uid,const int64 bid,const std::string& token){
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

    //call proc_SetUserBookList(10039,9)
	os<<"call proc_SetUserBookList("<<uid<<","<<bid<<",\'"<<token<<"\');";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}
	return true;
}

bool DBComm::OnGetBookList(const int64 uid,std::list<base_logic::BookInfo>& list){
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

    //call proc_GetOwnBook(10039)
	os<<"call proc_GetOwnBook("<<uid<<");";
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
			base_logic::BookInfo book;
			if(rows[0]!=NULL)
				book.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				book.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				book.set_name(rows[2]);
			if(rows[3]!=NULL)
				book.set_pic(rows[3]);
			if(rows[4]!=NULL)
				book.set_token(rows[4]);
			list.push_back(book);
		}
		return true;
	}
	return false;
}

bool DBComm::OnGetBookChapters(const int64 uid,const int64 bid,const std::string& token,
		const int64 from,const int64 count,
		std::list<booksvc_logic::ChapterInfo>& list){
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

    //call abheg.proc_GetBookChapter(49,10009,'b9a8eb0d5cc1fc26e6f87b8ed31bca65',0,4)
	os<<"call proc_GetBookChapter("<<bid<<","<<uid<<",\'"<<token<<"\',"<<from
			<<","<<count<<");";
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
			booksvc_logic::ChapterInfo chapter;
			if(rows[0]!=NULL)
				chapter.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				chapter.set_bid(atol(rows[1]));
			if(rows[2]!=NULL)
				chapter.set_url(rows[2]);
			if(rows[3]!=NULL)
				chapter.set_name(rows[3]);
			list.push_back(chapter);
		}
		return true;
	}
	return false;
}

bool DBComm::OnGetBookComInfo(const int64 bookid,base_logic::BookInfo& bookinfo){
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

	//call abheg.proc_GetBookCompInfo(49)
	os<<"call proc_GetBookCompInfo("<<bookid<<");";
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
			if(rows[0]!=NULL)
				bookinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				bookinfo.set_type(atol(rows[1]));
			if(rows[2]!=NULL)
				bookinfo.set_name(rows[2]);
			if(rows[3]!=NULL)
				bookinfo.set_author(rows[3]);
			if(rows[4]!=NULL)
				bookinfo.set_pubtime(rows[4]);
			if(rows[5]!=NULL)
				bookinfo.set_pic(rows[5]);
			if(rows[6]!=NULL)
				bookinfo.set_chapter(atoll(rows[6]));
			if(rows[7]!=NULL)
				bookinfo.set_summary(rows[7]);
			if(rows[8]!=NULL)
				bookinfo.set_free_url(rows[8]);
		}
		return true;
	}
	return true;


}
bool DBComm::OnGetBookSummary(const int64 uid,const int64 bookid,int32& issave,
			base_logic::BookInfo& bookinfo){
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

    //call proc_GetBookSummary(2)
	os<<"call proc_GetBookSummary("<<bookid<<","<<uid<<");";
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
			bookinfo.set_id(bookid);
			if(rows[0]!=NULL)
				bookinfo.set_author(rows[0]);
			if(rows[0]!=NULL)
				bookinfo.set_pubtime(rows[1]);
			if(rows[2]!=NULL)
				bookinfo.set_chapter(atol(rows[2]));
			if(rows[3]!=NULL)
				bookinfo.set_summary(rows[3]);
			if(rows[4]!=NULL)
				bookinfo.set_free_url(rows[4]);
			if(rows[5]!=NULL)
				issave = atol(rows[5]);
		}
		return true;
	}
	return true;
}


}
