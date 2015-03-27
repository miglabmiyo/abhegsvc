/*
 * db_comm.cc
 *
 *  Created on: 2015年3月10日
 *      Author: pro
 */




#include "db_comm.h"
#include "db/base_db_mysql_auto.h"
#include <sstream>
#include <mysql.h>

namespace paysvc_logic{

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


bool DBComm::OnPayUserRegister(const int64 platform,const std::string& imei,
		const int64 phone,const std::string& sim,const std::string& pkg){
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

    //call `proc_PayUserRegister`(10000,'353589054483206','18668169052','353589054483206','com.miglab.sypd')
	os<<"call proc_PayUserRegister("<<platform<<",\'"<<imei<<"\',\'"<<phone<<"\',\'"<<sim<<"\',\'"<<pkg<<"\');";
	std::string sql = os.str();
	LOG_MSG2("[%s]", sql.c_str());
	r = engine->SQLExec(sql.c_str());

	if (!r) {
		LOG_ERROR("exec sql error");
		return false;
	}
	return true;
}


bool DBComm::OnPayUserLogin(const int32 platform,paysvc_logic::PayUserInfo& userinfo){
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
	os<<"call proc_PayUserLogin(\'"<<userinfo.imei()<<"\',\'"<<userinfo.sim()
			<<"\'"<<");";
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
				userinfo.set_uid(atoll(rows[0]));
		}
		return true;
	}
	return false;
}


bool DBComm::OnGetPayChrPoint(const int32 platform,const int64 uid,
		const int64 payment,const std::string& serial,
				paysvc_logic::ChrPoint& point){
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

    //call proc_V2GetPayChrPonit(10002,100001,1,'123123ee3123')
	os<<"call proc_V2GetPayChrPonit("<<platform<<","<<uid<<","<<payment
			<<",\'"<<serial<<"\');";
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
				point.set_phone(rows[0]);
			if(rows[1]!=NULL)
				point.set_content(rows[1]);
			if(rows[2]!=NULL)
				point.set_remark(rows[2]);
		}
		return true;
	}
	return false;

}

/*
bool DBComm::OnGetPayChrPoint(const int32 platform,const int64 uid,const std::string& serial,
			paysvc_logic::ChrPoint& point){
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

    //call proc_GetPayChrPonit(10002,100001,0,0,2,'123123ee3123')
	os<<"call proc_GetPayChrPonit("<<platform<<","<<uid<<","<<point.type()
			<<","<<point.flag()<<","<<point.money()<<",\'"<<serial<<"\');";
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
				point.set_phone(rows[0]);
			if(rows[1]!=NULL)
				point.set_content(rows[1]);
		}
		return true;
	}
	return false;
}*/

bool DBComm::OnUpdateSerialnumber(const int32 state,const char* serialnumber,
			const char* operator_serial){
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

    //call proc_UpdateSerialnumber('123213e123','213123123321',1)
	os<<"call proc_UpdateSerialnumber(\'"<<serialnumber<<"\',\'"<<operator_serial<<"\',"
			<<state<<");";
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
