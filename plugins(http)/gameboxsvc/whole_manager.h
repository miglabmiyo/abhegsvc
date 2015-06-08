/*
 * whole_manager.h
 *
 *  Created on: 2015年6月1日
 *      Author: Administrator
 */

#ifndef PLUGINS_HTTP__GAMEBOXSVC_WHOLE_MANAGER_H_
#define PLUGINS_HTTP__GAMEBOXSVC_WHOLE_MANAGER_H_

#include "logic/logic_infos.h"
#include "thread/base_thread_handler.h"
#include "thread/base_thread_lock.h"
#include "basic/radom_in.h"
#include <map>
#include <list>
namespace gameboxsvc_logic{


class GameCache{
public:
	std::map<std::string,base_logic::AppInfos>       game_packet_name_map_;
	std::map<int64,base_logic::AppInfos>             game_id_map_;

	std::map<std::string,base_logic::AppInfos>       app_packet_name_map_;

	std::map<int64,base_logic::AppInfos>             recommend_game_map_;
	base::MigRadomInV2*                              recommend_radomin_;
	std::vector<int64>                               recommend_vec_;

};


class WholeManager{
public:
	WholeManager();
	virtual ~WholeManager();
public:
	void Init();
	bool CheckGame(base_logic::ListValue* list,std::map<std::string,base_logic::AppInfos>& app_map);
	bool GetRecommend(std::map<std::string,base_logic::AppInfos>& app_map);
	bool GetRamdominApp(std::list<base_logic::AppInfos>& list);
public:
	GameCache* GetFindCache(){return this->game_cache_;}
private:
	GameCache*                   game_cache_;
	struct threadrw_t*           lock_;
};


class CacheManagerOp{
private:
	static WholeManager              *whole_mgr_;
	static CacheManagerOp            *cache_manager_op_;

	CacheManagerOp(){};
	virtual ~CacheManagerOp(){};
public:
	static WholeManager* GetWholeManager (){
		if (whole_mgr_ == NULL)
			whole_mgr_ = new WholeManager ();

		return whole_mgr_;
	}

	static CacheManagerOp* GetCacheManagerOp(){
		if(cache_manager_op_ == NULL){
			cache_manager_op_ = new CacheManagerOp();
		}
		return cache_manager_op_;
	}

	static void FreeWholeCacheManager(){
		delete whole_mgr_;
	}

	static void FreeCacheManagerOp(){
		delete cache_manager_op_;
	}
public:
	static void FetchDBAppInfo();
};
}



#endif /* PLUGINS_HTTP__GAMEBOXSVC_WHOLE_MANAGER_H_ */
