/*
 * find_cache_mgr.cc
 *
 *  Created on: 2015年1月24日
 *      Author: mac
 */
#include "find_cache_mgr.h"
#include "db_comm.h"
#include "logic/logic_comm.h"


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

//APP专题
bool FindCacheManager::SendTopicsAppInfos(netcomm_send::FindAppStore* appfind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->app_topics_list_.size()<=0)
		return false;
	std::list<base_logic::Topics>::iterator topicsinfo_iterator;
	for(topicsinfo_iterator=find_cache_->app_topics_list_.begin();
			topicsinfo_iterator!=find_cache_->app_topics_list_.end();
			topicsinfo_iterator++){
		base_logic::Topics topics = (*topicsinfo_iterator);
		appfind->set_topics(topics.Release());
	}
	return true;
}
//APP广告
bool FindCacheManager::SendAdverAppInfos(netcomm_send::FindAppStore* appfind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->app_adver_list_.size()<=0)
		return false;
	std::list<base_logic::AdvertInfos>::iterator adverinfo_iterator;
	for(adverinfo_iterator=find_cache_->app_adver_list_.begin();
			adverinfo_iterator!=find_cache_->app_adver_list_.end();
			adverinfo_iterator++){
		base_logic::AdvertInfos advert = (*adverinfo_iterator);
		appfind->set_advert(advert.Release());
	}
	return true;

}
//APP推荐
bool FindCacheManager::SendFindAppInfos(netcomm_send::FindAppStore* appfind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->app_store_list_.size()<=0)
		return false;
	std::list<base_logic::AppInfos>::iterator appinfo_iterator;
	for(appinfo_iterator=find_cache_->app_store_list_.begin();
			appinfo_iterator!=find_cache_->app_store_list_.end();
			appinfo_iterator++){
		base_logic::AppInfos appinfo = (*appinfo_iterator);
		if(appinfo.attr()==0)
			appfind->set_important(appinfo.Release());
		else if(appinfo.attr()==1)
			appfind->set_popularity(appinfo.Release());
		else if(appinfo.attr()==2)
			appfind->set_hot(appinfo.Release());
	}
	return true;
}
//APP广告

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



