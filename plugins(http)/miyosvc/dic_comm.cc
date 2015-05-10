/*
 * dic_comm.cc
 *
 *  Created on: 2015年5月10日
 *      Author: pro
 */


#include "dic_comm.h"
#include "whole_manager.h"
#include "dic/base_dic_redis_auto.h"
#include "basic/basic_util.h"
#include <string>
#include <sstream>

namespace miyosvc_logic{

RedisComm::RedisComm(){

}

RedisComm::~RedisComm(){
	Dest();
}

void RedisComm::Init(std::list<base::ConnAddr>& addrlist){
	base_dic::RedisPool::Init(addrlist);
}

void RedisComm::Dest(){
	base_dic::RedisPool::Dest();
}

void RedisComm::SetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo){
	std::string key;
	std::string hash_name;
	std::string content;
	bool r = userinfo.JsonSerialization(content);
	if(!r)
		return ;
	hash_name = "miyo:userinfo";
	key = base::BasicUtil::StringUtil::Int64ToString(uid);
	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
	LOG_DEBUG2("key:%s",key.c_str());
	redis_engine_->SetHashElement(hash_name.c_str(),key.c_str(),key.length(),content.c_str(),
			content.length());

}
bool RedisComm::GetMiyoUserInfo(const int64 uid,miyosvc_logic::UserInfo& userinfo){
	std::string key;
	std::string hash_name;
	char* value;
	size_t value_len = 0;
	std::string content;
	hash_name = "miyo:userinfo";
	key = base::BasicUtil::StringUtil::Int64ToString(uid);
	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
	LOG_DEBUG2("key:%s",key.c_str());
	bool r = redis_engine_->GetHashElement(hash_name.c_str(),key.c_str(),key.length(),&value,
			&value_len);
	content.assign(value,value_len);
	if (value){
		free(value);
		value = NULL;
	}
	return userinfo.JsonDeserialization(content);
}


}
