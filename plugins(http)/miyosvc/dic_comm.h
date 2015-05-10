/*
 * dic_comm.h
 *
 *  Created on: 2015年5月10日
 *      Author: pro
 */

#ifndef __MIYO_SVC_DIC_COMM_H_
#define __MIYO_SVC_DIC_COMM_H_

#include "miyo_basic_info.h"
#include "config/config.h"
#include "storage/storage.h"
#include <list>
#include <map>
namespace miyosvc_logic{

class RedisComm{
public:
	RedisComm();
	~RedisComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();
public:
	static void SetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo);
};

}



#endif /* DIC_COMM_H_ */
