/*
 * db_comm.h
 *
 *  Created on: 2015年4月22日
 *      Author: pro
 */

#ifndef __ABHEG__BEACON__DB_COMM___
#define __ABHEG__BEACON__DB_COMM___
#include "beacon_basic_info.h"
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace beaconsvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();

public:
	static bool GetBeaconMerchantInfo(beaconsvc_logic::BeaconInfo& beacon,
			beaconsvc_logic::BeaconMerchant& merchant);

};

}

#endif /* DB_COMM_H_ */
