/*
 * db_comm.cc
 *
 *  Created on: 2015年3月27日
 *      Author: pro
 */
#include "db_comm.h"
#include "db/base_db_mysql_auto.h"
#include <sstream>
#include <mysql.h>

namespace moviesvc_logic{

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

bool DBComm::OnGetMovieSummary(const int64 uid,const int64 moiveid,const int32 machine,
			int32& like,base_logic::Movies& movie){
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

    //call proc_GetMovieSummary(1008,1,0)
	os<<"call proc_GetMovieSummary("<<uid<<","<<moiveid
			<<","<<machine<<");";
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
				movie.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				movie.set_name(rows[1]);
			if(rows[2]!=NULL)
				movie.set_summary(rows[2]);
			if(rows[3]!=NULL)
				movie.set_type(atol(rows[3]));
			if(rows[4]!=NULL)
				movie.set_play_count(atoll(rows[4]));
			if(rows[5]!=NULL)
				movie.set_like(atoll(rows[5]));
			if(rows[6]!=NULL)
				movie.set_url(rows[6]);
			if(rows[7]!=NULL)
				like = atol(rows[7]);
		}
		return true;
	}
	return false;
}

bool DBComm::OnGetMovieByType(const int32 type,std::list<base_logic::Movies>& list){
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

    //call proc_GetMoivesByType(1)
	os<<"call proc_GetMoivesByType("<<type<<");";
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

bool DBComm::OnGetAboutAdvert(const int64 movieid,const int32 type,
			base_logic::AdvertInfos& advert){
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
			if(rows[0]!=NULL)
				advert.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				advert.set_name(rows[1]);
			if(rows[2]!=NULL)
				advert.set_type(atoll(rows[2]));
			if(rows[4]!=NULL)
				advert.set_pic(rows[4]);
			return true;
		}
		return true;
	}
	return false;
}

bool DBComm::OnMovieLike(const int64 uid,const int64 movieid){
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

    //call proc_LikeMovie(1008,2)
	os<<"call proc_LikeMovie("<<uid<<","<<movieid<<");";
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
