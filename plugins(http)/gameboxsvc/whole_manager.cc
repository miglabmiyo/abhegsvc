/*
 * whole_manager.cc
 *
 *  Created on: 2015年6月1日
 *      Author: Administrator
 */
#include "whole_manager.h"
#include "db_comm.h"
#include "basic/template.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include <sstream>

namespace gameboxsvc_logic{

WholeManager* CacheManagerOp::whole_mgr_ = NULL;
CacheManagerOp* CacheManagerOp::cache_manager_op_ = NULL;

WholeManager::WholeManager(){
	game_cache_ = new GameCache();
	Init();
}

WholeManager::~WholeManager(){
	DeinitThreadrw(lock_);
}

void WholeManager::Init(){
	//读取当前所有信息
	InitThreadrw(&lock_);

	//读取推荐游戏
	gameboxsvc_logic::DBComm::GetRecommendGame(game_cache_->recommend_game_map_,game_cache_->recommend_vec_);
	//创建随机数
	game_cache_->recommend_radomin_ = new base::MigRadomInV2(game_cache_->recommend_game_map_.size());

}

bool WholeManager::CheckGame(base_logic::ListValue* list,std::map<std::string,base_logic::AppInfos>& app_map){
	base_logic::RLockGd lk(lock_);
	int32 index = 0;
	bool r =false;
	std::list<std::string> remove_list;
	while(index<list->GetSize()){
		std::string packet_name;
		base_logic::AppInfos appinfo;
		r = list->GetString(index,&packet_name);
		index++;
		if(!r)
			continue;
		r = base::MapGet<std::map<std::string,base_logic::AppInfos>,std::map<std::string,base_logic::AppInfos>::iterator,std::string,base_logic::AppInfos>
				(game_cache_->game_packet_name_map_,packet_name,appinfo);
		if(r){//游戏
			appinfo.set_attr(1);//
			app_map[appinfo.packetname()] = appinfo;
		}
	}
	return true;
}

bool WholeManager::GetRecommend(std::map<std::string,base_logic::AppInfos>& app_map){
	base_logic::RLockGd lk(lock_);
	int32 num = 5;
	int32 i = 0;
	int32* rands = new int32[num];
	game_cache_->recommend_radomin_->GetPrize(rands,num);
	while(i<num){
		int64 appid = game_cache_->recommend_vec_[rands[i]];
		base_logic::AppInfos appinfo = game_cache_->game_id_map_[appid];
		app_map[appinfo.packetname()] = appinfo;
		i++;
	}
	if(rands){delete [] rands;rands=NULL;}
}


bool WholeManager::GetRamdominApp(std::list<base_logic::AppInfos>& list){
	base_logic::RLockGd lk(lock_);
	int32 num = 5;
	int32 i = 0;
	int32* rands = new int32[num];
	game_cache_->recommend_radomin_->GetPrize(rands,num);
	while(i<num){
		int64 appid = game_cache_->recommend_vec_[rands[i]];
		base_logic::AppInfos appinfo = game_cache_->game_id_map_[appid];
		list.push_back(appinfo);
		i++;
	}
	if(rands){delete [] rands;rands=NULL;}
}


void CacheManagerOp::FetchDBAppInfo(){
	GameCache* game_cache = whole_mgr_->GetFindCache();
	std::list<base_logic::AppInfos> list;
	gameboxsvc_logic::DBComm::GetAllGame(game_cache->game_packet_name_map_,game_cache->game_id_map_);
	gameboxsvc_logic::DBComm::GetAllApp(game_cache->app_packet_name_map_);
}



}

