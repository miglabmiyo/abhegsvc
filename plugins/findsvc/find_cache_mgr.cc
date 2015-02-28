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

//书城广告
bool FindCacheManager::SendAdverBookInfos(netcomm_send::FindBookStore* bookfind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->book_adver_list_.size()<=0)
		return false;
	std::list<base_logic::AdvertInfos>::iterator adverinfo_iterator;
	for(adverinfo_iterator=find_cache_->book_adver_list_.begin();
			adverinfo_iterator!=find_cache_->book_adver_list_.end();
			adverinfo_iterator++){
		base_logic::AdvertInfos advert = (*adverinfo_iterator);
		bookfind->set_advert(advert.Release());
	}
	return true;
}

//书城专题
bool FindCacheManager::SendTopicsBookInfos(netcomm_send::FindBookStore* bookfind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->book_topics_list_.size()<=0)
		return false;
	std::list<base_logic::Topics>::iterator topicsinfo_iterator;
	for(topicsinfo_iterator=find_cache_->book_topics_list_.begin();
			topicsinfo_iterator!=find_cache_->book_topics_list_.end();
			topicsinfo_iterator++){
		base_logic::Topics topics = (*topicsinfo_iterator);
		bookfind->set_topics(topics.Release());
	}
	return true;
}


//推荐书
bool FindCacheManager::SendFindBookInfos(netcomm_send::FindBookStore* bookfind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->book_store_list_.size()<=0)
		return false;
	std::list<base_logic::BookInfo>::iterator bookinfo_iterator;
	for(bookinfo_iterator=find_cache_->book_store_list_.begin();
			bookinfo_iterator!=find_cache_->book_store_list_.end();
			bookinfo_iterator++){
		base_logic::BookInfo bookinfo = (*bookinfo_iterator);
		if(bookinfo.attr()==0)
			bookfind->set_hot(bookinfo.Release());
		else if(bookinfo.attr()==1)
			bookfind->set_boys(bookinfo.Release());
		else if(bookinfo.attr()==2)
			bookfind->set_girls(bookinfo.Release());
	}
	return true;
}


bool FindCacheManager::SendFindGameInfos(netcomm_send::FindGameStore* gamefind){
	base_logic::RLockGd lk(lock_);
	if(find_cache_->game_store_list_.size()<=0)
		return false;
	std::list<base_logic::AppInfos>::iterator appinfo_iterator;
	for(appinfo_iterator=find_cache_->game_store_list_.begin();
			appinfo_iterator!=find_cache_->game_store_list_.end();
			appinfo_iterator++){
		base_logic::AppInfos appinfo = (*appinfo_iterator);
		if(appinfo.attr()==0)
			gamefind->set_emblem(appinfo.Release());
		else if(appinfo.attr()==1) //精品推荐
			gamefind->set_important(appinfo.Release());
		else if(appinfo.attr()==2) //人气推荐
			gamefind->set_popularity(appinfo.Release());
	}

	//图片
	std::string pic1 = "http://pic.desgin.miglab.com/abheg/store/game/products/20000024/summary/1.png";
	std::string pic2 = "http://pic.desgin.miglab.com/abheg/store/game/products/20000024/summary/2.png";
	std::string pic3 = "http://pic.desgin.miglab.com/abheg/store/game/products/20000024/summary/3.png";
	std::string pic4 = "http://pic.desgin.miglab.com/abheg/store/game/products/20000024/summary/4.png";
	std::string pic5 = "http://pic.desgin.miglab.com/abheg/store/game/products/20000024/summary/5.png";

	gamefind->set_pic(pic1);
	gamefind->set_pic(pic2);
	gamefind->set_pic(pic3);
	gamefind->set_pic(pic4);
	gamefind->set_pic(pic5);
	return true;
}

bool FindCacheManager::SendGameRank(netcomm_send::FindGameRank* rank){
	base_logic::RLockGd lk(lock_);

	int32 i = 0;
	if(find_cache_->game_rank_list_.size()>0){
		std::list<base_logic::AppInfos>::iterator appinfo_iterator;
		i = 0;
		for(appinfo_iterator=find_cache_->game_rank_list_.begin();
				i<10&&
				appinfo_iterator!=find_cache_->game_rank_list_.end();
				appinfo_iterator++,i++){
			base_logic::AppInfos appinfo = (*appinfo_iterator);
			rank->set_game(appinfo.Release());
		}
	}
	return true;
}

bool FindCacheManager::SendFindMain(netcomm_send::FindMain* main){
	base_logic::RLockGd lk(lock_);
	//广告
	if(find_cache_->find_adver_list_.size()>0){
		std::list<base_logic::AdvertInfos>::iterator adverinfo_iterator;
		for(adverinfo_iterator=find_cache_->find_adver_list_.begin();
				adverinfo_iterator!=find_cache_->find_adver_list_.end();
				adverinfo_iterator++){
			base_logic::AdvertInfos advert = (*adverinfo_iterator);
			main->set_advert(advert.Release());
		}
	}

	//APP
	if(find_cache_->find_app_list_.size()>0){
		std::list<base_logic::AppInfos>::iterator appinfo_iterator;
		for(appinfo_iterator=find_cache_->find_app_list_.begin();
				appinfo_iterator!=find_cache_->find_app_list_.end();
				appinfo_iterator++){
			base_logic::AppInfos appinfo = (*appinfo_iterator);
			main->set_app(appinfo.Release());
		}
	}
	//游戏
	if(find_cache_->find_game_list_.size()>0){
		std::list<base_logic::AppInfos>::iterator appinfo_iterator;
		for(appinfo_iterator=find_cache_->find_game_list_.begin();
				appinfo_iterator!=find_cache_->find_game_list_.end();
				appinfo_iterator++){
			base_logic::AppInfos appinfo = (*appinfo_iterator);
			main->set_game(appinfo.Release());
		}
	}
	//书
	if(find_cache_->find_book_list_.size()>0){
		std::list<base_logic::BookInfo>::iterator bookinfo_iterator;
		for(bookinfo_iterator=find_cache_->find_book_list_.begin();
				bookinfo_iterator!=find_cache_->find_book_list_.end();
				bookinfo_iterator++){
			base_logic::BookInfo bookinfo = (*bookinfo_iterator);
			main->set_book(bookinfo.Release());
		}
	}
	return true;
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

void CacheManagerOp::FetchDBFindBookStore(){
	FindCache* find_cache = find_cache_manager_->GetFindCache();
	findsvc_logic::DBComm::GetFindStoreBook(find_cache->book_store_list_);
	findsvc_logic::DBComm::GetAdverBookStore(find_cache->book_adver_list_);
	findsvc_logic::DBComm::GetTopicsBookStore(find_cache->book_topics_list_);

}

void CacheManagerOp::FetchDBFindGameStore(){
	FindCache* find_cache = find_cache_manager_->GetFindCache();
	findsvc_logic::DBComm::GetFindStoreGame(find_cache->game_store_list_);
	findsvc_logic::DBComm::GetFindGameRank(find_cache->game_rank_list_);
}

void CacheManagerOp::FetchDBFindMain(){
	FindCache* find_cache = find_cache_manager_->GetFindCache();
	findsvc_logic::DBComm::GetFindApp(find_cache->find_app_list_);
	findsvc_logic::DBComm::GetFindBook(find_cache->find_book_list_);
	findsvc_logic::DBComm::GetFindGame(find_cache->find_game_list_);
	findsvc_logic::DBComm::GetAdver(find_cache->find_adver_list_);
}

}



