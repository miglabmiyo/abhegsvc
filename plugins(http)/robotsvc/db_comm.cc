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


bool DBComm::GainMovie(const int64 from,const int32 count,
		std::list<base_logic::Movies>& list){
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

	//call abheg.proc_RobotGainMovie(0,10)
	os<<"call proc_RobotGainMovie("<<from<<","<<count<<");";

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
			base_logic::Movies movie;
			if(rows[0]!=NULL)
				movie.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				movie.set_token(rows[1]);
			list.push_back(movie);
		}
		return true;
	}
	return true;

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

bool DBComm::UpdateMovie(const int64 id,const std::string& name,const std::string& url,
			const std::string& logo,const std::string& desc){
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

	/*call proc_UpdateMovieInfo(3,'翔飞人十二载光辉岁月 细数刘翔身边风云人物','http://pl.youku.com/playlist/m3u8?ctype=12&ep=eiaWE0yKX8wE7SPciD8bYX7icSEHXJZ1kmaA%2fLYxAsZQH%2bzQnz%2fSwg%3d%3d&ev=1&keyframe=1&oip=1019168418&sid=8429579248030126b05f8&token=6135&type=flv&vid=XOTI5MTc2MDg4','http://g2.ykimg.com/1100641F4655241FE14F6A042CFD0A13320779-EA9C-C23A-D8BB-0CE31F0796B8','视频简介:翔飞人十二载光辉岁月 细数刘翔身边风云人物的视频描述稍后补充')
	 *
	 *
	 *
	 */

	os<<"call proc_UpdateMovieInfo("<<id<<",\'"<<name.c_str()<<"\',\'"<<url.c_str()<<"\',\'"
			<<logo.c_str()<<"\',\'"<<desc.c_str()<<"\');";

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
