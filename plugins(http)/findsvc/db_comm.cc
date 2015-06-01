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


bool DBComm::GetFindStoreMovies(std::list<base_logic::Movies>& list){
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

    //call proc_GetAdverStoreMovie()
	os<<"call proc_GetFindStoreMovie();";
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
				movie.set_name(rows[1]);
			if(rows[2]!=NULL)
				movie.set_logo(rows[2]);
			if(rows[3]!=NULL)
				movie.set_summary(rows[3]);
			if(rows[4]!=NULL)
				movie.set_type(atol(rows[4]));
			if(rows[5]!=NULL)
				movie.set_play_count(atoll(rows[5]));
			if(rows[6]!=NULL)
				movie.set_like(atoll(rows[6]));
			if(rows[7]!=NULL)
				movie.set_attr(atol(rows[7]));
			list.push_back(movie);
		}
	}
	return true;
}

bool DBComm::GetAdverMoviesStore(std::list<base_logic::AdvertInfos>& list){
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

    //call proc_GetAdverStoreMovie()
	os<<"call proc_GetAdverStoreMovie();";
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

bool DBComm::GetAdverGameStore(std::list<base_logic::AdvertInfos>& list){
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
	os<<"call abheg.proc_GetAdverStoreGame();";
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

bool DBComm::GetFindEmblemStore(base_logic::AppInfos& app){
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

    //call abheg.proc_GetAppPicList(20000024,1,2)
	os<<"call proc_GetAppPicList("<<app.id()<<",1,2"<<");";
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
				app.set_emblem_pic(rows[0]);
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
			if(rows[7]!=NULL)
				bookinfo.set_down(atoll(rows[7]));
			if(rows[8]!=NULL)
				bookinfo.set_freecount(atoll(rows[9]));

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

bool DBComm::GetFindMusic(std::list<base_logic::Dimension>& list){
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

    //call proc_GetFindMusic()
	os<<"call proc_GetFindMusic();";
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
			base_logic::Dimension dimension;
			if(rows[0]!=NULL)
				dimension.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				dimension.set_name(rows[1]);
			if(rows[2]!=NULL)
				dimension.set_logo(rows[2]);
			if(rows[3]!=NULL)
				dimension.set_dimension(rows[3]);
			if(rows[4]!=NULL)
				dimension.set_sid(atol(rows[4]));
			if(rows[5]!=NULL)
				dimension.set_desc(rows[5]);

			list.push_back(dimension);
		}
		return true;
	}
	return false;

}

bool DBComm::GetFindMovie(std::list<base_logic::Movies>& list){
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

    //call proc_GetFindMovie()
	os<<"call proc_GetFindMovie();";
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
			base_logic::Movies movieinfo;
			if(rows[0]!=NULL)
				movieinfo.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				movieinfo.set_name(rows[1]);
			if(rows[2]!=NULL)
				movieinfo.set_logo(rows[2]);
			if(rows[3]!=NULL)
				movieinfo.set_summary(rows[3]);
			if(rows[4]!=NULL)
				movieinfo.set_type(atol(rows[4]));
			if(rows[5]!=NULL)
				movieinfo.set_play_count(atoll(rows[5]));
			if(rows[6]!=NULL)
				movieinfo.set_like(atoll(rows[6]));
			list.push_back(movieinfo);
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

bool DBComm::GetFindAppRank(std::list<base_logic::AppInfos>& list){
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

    //call proc_GetAppRank()
	os<<"call proc_GetAppRank();";
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
			//按照星级排序
			list.sort(base_logic::AppInfos::cmp);
		}
		return true;
	}
	return false;
}

bool DBComm::GetFindGameRank(std::list<base_logic::AppInfos>& list){
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

    //call proc_GetGameRank
	os<<"call proc_GetGameRank();";
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
			//按照星级排序
			list.sort(base_logic::AppInfos::cmp);
		}
		return true;
	}
	return false;
}

bool DBComm::GetPersonalAppAndGame(const int64 uid,const int32 type,std::list<base_logic::AppInfos>& list){
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

    //call abheg.proc_GetPersonalApp(2001,0)
	os<<"call proc_GetPersonalApp("<<uid<<","<<type<<");";
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
				appinfo.set_like(atoll(rows[4]));
			if(rows[5]!=NULL)
				appinfo.set_down(atoll(rows[5]));
			if(rows[6]!=NULL)
				appinfo.set_summary(rows[6]);

			list.push_back(appinfo);
		}
		return true;
	}
	return false;
}

bool  DBComm::GetPersonalApp(const int64 uid,std::list<base_logic::AppInfos>& list){
	return GetPersonalAppAndGame(uid,1,list);
}

bool  DBComm::GetPersonalGame(const int64 uid,std::list<base_logic::AppInfos>& list){
	return GetPersonalAppAndGame(uid,2,list);
}



bool DBComm::GetPersonalBook(const int64 uid,std::list<base_logic::BookInfo>& list){
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

    //call proc_GetPersonalBook(1008)
	os<<"call proc_GetPersonalBook("<<uid<<")";
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
				bookinfo.set_freecount(atoll(rows[4]));
			if(rows[5]!=NULL)
				bookinfo.set_attr(atol(rows[5]));
			if(rows[6]!=NULL)
				bookinfo.set_name(rows[6]);
			if(rows[7]!=NULL)
				bookinfo.set_author(rows[7]);
			if(rows[8]!=NULL)
				bookinfo.set_pic(rows[8]);
			if(rows[9]!=NULL)
				bookinfo.set_summary(rows[9]);
			list.push_back(bookinfo);
		}
		return true;
	}
	return false;
}

bool DBComm::GetMovieRank(int32 type,std::list<base_logic::Movies>& list){
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

    //call proc_GetPersonalMovie(1008)
	os<<"call proc_GetMovieRank("<<type<<");";
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
				movie.set_name(rows[1]);
			if(rows[2]!=NULL)
				movie.set_logo(rows[2]);
			if(rows[3]!=NULL)
				movie.set_type(atol(rows[3]));
			if(rows[4]!=NULL)
				movie.set_play_count(atoll(rows[4]));
			if(rows[5]!=NULL)
				movie.set_like(atoll(rows[5]));
			list.push_back(movie);

		}
		return true;
	}
	return false;
}
bool DBComm::GetPersonalMovie(const int64 uid, std::list<base_logic::Movies>& list){
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

    //call proc_GetPersonalMovie(1008)
	os<<"call proc_GetPersonalMovie("<<uid<<");";
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
				movie.set_name(rows[1]);
			if(rows[2]!=NULL)
				movie.set_logo(rows[2]);
			if(rows[3]!=NULL)
				movie.set_summary(rows[3]);
			if(rows[4]!=NULL)
				movie.set_type(atol(rows[4]));
			if(rows[5]!=NULL)
				movie.set_play_count(atoll(rows[5]));
			if(rows[6]!=NULL)
				movie.set_like(atoll(rows[6]));
			if(rows[7]!=NULL)
				movie.set_attr(atol(rows[7]));
			list.push_back(movie);

		}
		return true;
	}
	return false;
}

}
