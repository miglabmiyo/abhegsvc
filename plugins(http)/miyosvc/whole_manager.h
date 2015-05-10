/*
 * whole_manager.h
 *
 *  Created on: 2015年5月7日
 *      Author: pro
 */

#ifndef MIYO_WHOLE_MANAGER_H_
#define MIYO_WHOLE_MANAGER_H_

#include "miyo_basic_info.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"
#include <list>

namespace miyosvc_logic{

class WholeCache{
public:
	std::map<int64,miyosvc_logic::UserInfo>  user_miyo_info_;
};

class WholeManager{
public:
	WholeManager();
	virtual ~WholeManager();
public:
	//设置关联
	bool SetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo);
	bool GetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo);
	bool DelMiyoUserInfo(const int64 uid);
public:
	WholeCache*  GetWholeCache(){return this->whole_cache_;}
private:
	struct threadrw_t*    lock_;
	WholeCache*           whole_cache_;
};


class CacheManagerOp{
private:
	static WholeManager*              whole_manager_op_;
	static CacheManagerOp*            cache_manager_op_;

	CacheManagerOp();
	virtual ~CacheManagerOp();

public:
	static void FreeWholeCacheManager(){
		delete whole_manager_op_;
	}

	static void FreeCacheManagerOp(){
		delete whole_manager_op_;
	}
	static WholeManager* GetWholeCacheManager(){
		if(whole_manager_op_==NULL)
			whole_manager_op_ = new WholeManager();
		return whole_manager_op_;
	}

	static CacheManagerOp* GetCacheManagerOp(){
		if(cache_manager_op_==NULL)
			cache_manager_op_ = new CacheManagerOp();
		return cache_manager_op_;
	}
};


}




#endif /* WHOLE_MANAGER_H_ */
