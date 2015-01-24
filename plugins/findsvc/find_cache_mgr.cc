/*
 * find_cache_mgr.cc
 *
 *  Created on: 2015年1月24日
 *      Author: mac
 */
#include "find_cache_mgr.h"

namespace findsvc_logic{

CacheManagerOp* CacheManagerOp::cache_manager_op_ = NULL;
FindCacheManager* CacheManagerOp::find_cache_manager_ = NULL;


FindCacheManager::FindCacheManager(){
	InitThreadrw(&lock_);
	find_cache_ = new FindCache();
}

FindCacheManager::~FindCacheManager(){
	DeinitThreadrw(lock_);
}

CacheManagerOp::CacheManagerOp(){

}

CacheManagerOp::~CacheManagerOp(){

}


void CacheManagerOp::FetchDBFindAppStore(){
	FindCache* find_cache = find_cache_manager_->GetFindCache();
	findsvc_logic::DBComm::GetFindStoreApp(find_cache->app_store_list_);
	findsvc_logic::DBComm::GetAdverAppStore(find_cache->app_adver_list_);
	findsvc_logic::DBComm::GetTopicsAppStore(find_cache->app_topics_list_);
}


}



