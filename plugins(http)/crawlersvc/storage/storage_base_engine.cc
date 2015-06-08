/*
 * storage_engine.cc
 *
 *  Created on: 2015年5月21日
 *      Author: Administrator
 */
#include "storage_base_engine.h"
#include "redis_crawl_storage.h"、
#include "mysql_crawl_storage.h"
#include "text_crawl_storage.h"
#include "dic/base_dic_redis_auto.h"
#include "db/base_db_mysql_auto.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{

CrawlerStorageBaseEngine* CrawlerStorageBaseEngine::Create(int32 type){
	CrawlerStorageBaseEngine* engine = NULL;
	switch(type){
	case REIDS_TYPE:
		engine = new RedisCrawlStorage();
		break;
	case MYSQL_TYPE:
		engine = new MysqlCrawlStorage();
		break;
	case TEXT_TYPE:
		engine = new TextCrawlStorage();
		break;
	default:
		break;
	}

	return engine;
}

void CrawlerStorageBaseEngine::Init(config::FileConfig* config){
	base_dic::RedisPool::Init(config->redis_list_);
	base_db::MysqlDBPool::Init(config->mysql_db_list_);
}

void CrawlerStorageBaseEngine::Dest(){
	base_dic::RedisPool::Dest();
	base_db::MysqlDBPool::Dest();
}

}



