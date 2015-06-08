/*
 * redis_crawl_storage.cc
 *
 *  Created on: 2015年5月21日
 *      Author: Administrator
 */
#include "redis_crawl_storage.h"
#include "dic/base_dic_redis_auto.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{


RedisCrawlStorage* RedisCrawlStorage::instance_ = NULL;

RedisCrawlStorage* RedisCrawlStorage::Instance(){
	if(instance_==NULL)
		instance_ = new RedisCrawlStorage();
	return instance_;
}

void RedisCrawlStorage::FreeInstance(){
	delete instance_;
	instance_ = NULL;
}

void RedisCrawlStorage::Init(std::list<base::ConnAddr>& addrlist){
}

void RedisCrawlStorage::Release(){

}


bool RedisCrawlStorage::WriteData(const int32 type,base_logic::Value* value){

	switch(type){
	case APP_DETAIL_TYPE:
		WriteHashData(value);
		break;
	default:
		break;
	}
	return true;
}

bool RedisCrawlStorage::WriteHashData(base_logic::Value* value){
	std::string redis_map;
	std::string name;
	std::string type;
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)value;
	dict->GetString(L"reidsmap",&redis_map);
	dict->GetString(L"rediskey",&name);
	dict->GetString(L"type",&type);
	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine = auto_engine.GetDicEngine();
	return redis_engine->SetHashElement(redis_map.c_str(),name.c_str(),
			name.length(),type.c_str(),type.length());
}

}
