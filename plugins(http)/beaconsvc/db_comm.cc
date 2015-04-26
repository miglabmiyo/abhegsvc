/*
 * db_comm.cc
 *
 *  Created on: 2015年4月22日
 *      Author: pro
 */
#include "db_comm.h"
#include "db/base_db_mysql_auto.h"
#include <sstream>
#include <mysql.h>

namespace beaconsvc_logic{

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

bool DBComm::GetBeaconMerchantInfo(beaconsvc_logic::BeaconInfo& beacon,
		beaconsvc_logic::BeaconMerchant& merchant){
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

    //call abheg.proc_GetBeaconMerchantInfo('FDA50693-A4E2-4FB1-AFCF-C6EB07647825','54:4A:16:3B:70:5E')
	os<<"call proc_GetBeaconMerchantInfo(\'"<<beacon.uuid().c_str()<<"\',\'"<<beacon.mac()<<"\');";
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
				merchant.set_id(atoll(rows[0]));
			if(rows[1]!=NULL)
				merchant.set_bid(atol(rows[1]));
			if(rows[2]!=NULL)
				merchant.set_name(rows[2]);
			if(rows[3]!=NULL)
				merchant.set_intor(rows[3]);
			if(rows[4]!=NULL)
				merchant.set_pic(rows[4]);
			if(rows[5]!=NULL)
				merchant.set_url(rows[5]);
		}
		return true;
	}
	return false;
}

}
