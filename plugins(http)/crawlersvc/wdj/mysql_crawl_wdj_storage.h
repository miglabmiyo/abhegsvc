/*
 * mysql_crawl_wdj_storage.h
 *
 *  Created on: 2015年5月25日
 *      Author: Administrator
 */

#ifndef PLUGINS_CRAWLERSVC_WDJ_MYSQL_CRAWL_WDJ_STORAGE_H_
#define PLUGINS_CRAWLERSVC_WDJ_MYSQL_CRAWL_WDJ_STORAGE_H_

#include "parser_wdj_engine.h"
#include "storage/storage_base_engine.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include <string>

namespace crawlersvc_logic{


class MysqlCrawlWDJStorage{
public:
	MysqlCrawlWDJStorage();
	virtual ~MysqlCrawlWDJStorage();
public:
	bool ReadWDJDetailInfo(const int32 from,const int32 count,base_logic::Value* value);
	bool UpdateCrawlerURLState(const int64 id,const int32 status);
	bool CreaeAppDetailInfo(base_logic::Value* value);
public:
	static void CallBackGetWDJDetailInfo(void* param,base_logic::Value* value);


private:
	scoped_ptr<crawlersvc_logic::CrawlerStorageBaseEngine> mysql_engine_;
	scoped_ptr<crawlersvc_logic::ParserWDJEngine>       parser_engine_;//
};
}

#endif /* PLUGINS_CRAWLERSVC_WDJ_MYSQL_CRAWL_WDJ_STORAGE_H_ */
