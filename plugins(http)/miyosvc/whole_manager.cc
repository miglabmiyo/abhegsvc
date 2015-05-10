/*
 * whole_manager.cc
 *
 *  Created on: 2015年5月8日
 *      Author: pro
 */
#include "whole_manager.h"
#include "dic_comm.h"
#include "logic/logic_comm.h"
#include "basic/template.h"

namespace miyosvc_logic{

CacheManagerOp* CacheManagerOp::cache_manager_op_ = NULL;
WholeManager* CacheManagerOp::whole_manager_op_ = NULL;

WholeManager::WholeManager(){
	InitThreadrw(&lock_);
	whole_cache_ = new WholeCache();
}

WholeManager::~WholeManager(){
	DeinitThreadrw(lock_);
}

bool WholeManager::SetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo){
	base_logic::WLockGd lk(lock_);
	//return base::MapAdd<std::map<int64,miyosvc_logic::UserInfo>,int64,miyosvc_logic::UserInfo>
		//(whole_cache_->user_miyo_info_,uid,userinfo);
	//return base::MapAdd(whole_cache_->user_miyo_info_,uid,userinfo);
	whole_cache_->user_miyo_info_[uid] = userinfo;
	return true;
}

bool WholeManager::GetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo){
	bool r =false;
	{
		base_logic::RLockGd lk(lock_);
		r =  base::MapGet<std::map<int64,miyosvc_logic::UserInfo>,std::map<int64,miyosvc_logic::UserInfo>::iterator,int64,miyosvc_logic::UserInfo>
			(whole_cache_->user_miyo_info_,uid,userinfo);
	}
	if(r)
		return r;
	//存储介质读取
	r = miyosvc_logic::RedisComm::GetMiyoUserInfo(uid,userinfo);
	{
		base_logic::WLockGd lk(lock_);
		whole_cache_->user_miyo_info_[uid] = userinfo;
	}
	return true;
}

bool WholeManager::DelMiyoUserInfo(const int64 uid){
	base_logic::WLockGd lk(lock_);
	return base::MapDel<std::map<int64,miyosvc_logic::UserInfo>,std::map<int64,miyosvc_logic::UserInfo>::iterator,int64>
	(whole_cache_->user_miyo_info_,uid);
}
CacheManagerOp::CacheManagerOp(){

}

CacheManagerOp::~CacheManagerOp(){

}

}


