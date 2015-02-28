/*
 * find_cache_manager.h
 *
 *  Created on: 2015年1月24日
 *      Author: mac
 */

#ifndef FIND_CACHE_MANAGER_H_
#define FIND_CACHE_MANAGER_H_

#include "net/find_comm_head.h"
#include "logic/logic_infos.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"
#include <list>

namespace findsvc_logic{
class FindCache{
public:
	std::list<base_logic::AdvertInfos>   find_adver_list_;
	std::list<base_logic::AppInfos>      find_app_list_;
	std::list<base_logic::AppInfos>      find_game_list_;
	std::list<base_logic::BookInfo>      find_book_list_;

	std::list<base_logic::AppInfos>      app_store_list_; //应用商场推荐，热门，人气APP
	std::list<base_logic::AdvertInfos>   app_adver_list_;//应用商场广告
	std::list<base_logic::Topics>        app_topics_list_;//应用商场专题

	std::list<base_logic::AppInfos>      game_store_list_; //游戏商场推荐，热门，人气APP

	std::list<base_logic::AppInfos>      game_rank_list_;//排行榜

	std::list<base_logic::BookInfo>      book_store_list_; //书城推荐
	std::list<base_logic::AdvertInfos>   book_adver_list_;//书城广告
	std::list<base_logic::Topics>        book_topics_list_;//书城专题
};


class FindCacheManager{
public:
	FindCacheManager();
	virtual ~FindCacheManager();

	//获取商场APP
	//bool GetFindAppInfos();
	bool SendFindAppInfos(netcomm_send::FindAppStore* appfind);
	//获取商场广告
	//bool GetAdverInfos();
	bool SendAdverAppInfos(netcomm_send::FindAppStore* appfind);
	//获取商城专题
	//bool GetTopicsInfos();
	bool SendTopicsAppInfos(netcomm_send::FindAppStore* appfind);

	//书城
	bool SendFindBookInfos(netcomm_send::FindBookStore* bookfind);

	bool SendAdverBookInfos(netcomm_send::FindBookStore* bookfind);

	bool SendTopicsBookInfos(netcomm_send::FindBookStore* bookfind);

	//游戏发送

	bool SendFindGameInfos(netcomm_send::FindGameStore* bookfind);
	//首页发送
	bool SendFindMain(netcomm_send::FindMain* main);

	//游戏排行榜发送
	bool SendGameRank(netcomm_send::FindGameRank* rank);

public:
	FindCache* GetFindCache(){return this->find_cache_;}
private:
	struct threadrw_t*            lock_;
	FindCache*                    find_cache_;
};



class CacheManagerOp{
private:
	static CacheManagerOp*            cache_manager_op_;
	static FindCacheManager*          find_cache_manager_;

	CacheManagerOp();
	virtual ~CacheManagerOp();
public:
	static void FreeFindCacheManager(){
		delete find_cache_manager_;
	}

	static void FreeCacheManagerOp(){
		delete cache_manager_op_;
	}
	static FindCacheManager* GetFindCacheManager(){
		if(find_cache_manager_==NULL)
			find_cache_manager_ = new FindCacheManager();
		return find_cache_manager_;
	}

	static CacheManagerOp* GetCacheManagerOp(){
		if(cache_manager_op_==NULL)
			cache_manager_op_ = new CacheManagerOp();
		return cache_manager_op_;
	}

public:
	//获取APP商城的推荐
	static void FetchDBFindAppStore();
	//获取书城的推荐
	static void FetchDBFindBookStore();
	//获取游戏商城的推荐
	static void FetchDBFindGameStore();
	//首页推荐
	static void FetchDBFindMain();
};
}



#endif /* FIND_CACHE_MANAGER_H_ */
