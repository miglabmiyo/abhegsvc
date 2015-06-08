/*
 * whole_manager.h
 *
 *  Created on: 2015年6月1日
 *      Author: Administrator
 */

#ifndef PLUGINS_HTTP__GAMEBOXSVC_WHOLE_MANAGER_H_
#define PLUGINS_HTTP__GAMEBOXSVC_WHOLE_MANAGER_H_

namespace gameboxsvc_logic{


class GameCache{
public:
	std::map<std::string&,base_logic::AppInfos> packet_name_map_;
	std::map<int64,base_logic::AppInfos>        id_map_;
};


class WholeManager{
public:
	WholeManager();
	virtual ~WholeManager();
public:
	void Init();
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
};
}



#endif /* PLUGINS_HTTP__GAMEBOXSVC_WHOLE_MANAGER_H_ */
