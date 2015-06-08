/*
 * RedisCrawlWDJStorage.cc
 *
 *  Created on: 2015年5月22日
 *      Author: Administrator
 */


#include "redis_crawl_wdj_storage.h"
#include "storage/redis_crawl_storage.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{

RedisCrawlWDJStorage::RedisCrawlWDJStorage(){
	redis_engine_.reset(crawlersvc_logic::CrawlerStorageBaseEngine::Create(REIDS_TYPE));
}

RedisCrawlWDJStorage::~RedisCrawlWDJStorage(){

}

bool RedisCrawlWDJStorage::WriteAppDetailType(const std::string& name,
		base_logic::Value* value){
	//map，key 写入value
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)value;
	dict->SetString(L"reidsmap","wandoujia_detail_type");
	dict->SetString(L"rediskey",name);
	//return crawlersvc_logic::RedisCrawlStorage::Instance()->WriteData(APP_DETAIL_TYPE,(base_logic::Value*)dict);
	return redis_engine_->WriteData(APP_DETAIL_TYPE,(base_logic::Value*)dict);
}

}


