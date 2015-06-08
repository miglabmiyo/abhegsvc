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

}

void WholeManager::Init(){
	//读取当前所有信息
}



}

