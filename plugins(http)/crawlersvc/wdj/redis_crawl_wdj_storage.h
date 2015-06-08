/*
 * redis_crawl_wdj_storage.h
 *
 *  Created on: 2015年5月22日
 *      Author: Administrator
 */

#ifndef PLUGINS_CRAWLERSVC_WDJ_REDIS_CRAWL_WDJ_STORAGE_H_
#define PLUGINS_CRAWLERSVC_WDJ_REDIS_CRAWL_WDJ_STORAGE_H_
#include "storage/storage_base_engine.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "check/newmacro.h"

#include <string>

namespace crawlersvc_logic{

class RedisCrawlWDJStorage{
public:
	RedisCrawlWDJStorage();
	virtual ~RedisCrawlWDJStorage();
public:
	bool WriteAppDetailType(const std::string& name,
			base_logic::Value* value);
private:
	scoped_ptr<crawlersvc_logic::CrawlerStorageBaseEngine>  redis_engine_;//
};

}


#endif /* PLUGINS_CRAWLERSVC_WDJ_REDIS_CRAWL_WDJ_STORAGE_H_ */
