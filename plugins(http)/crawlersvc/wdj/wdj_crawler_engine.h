/*
 * wdj_crawler_engine.h
 *
 *  Created on: 2015年5月12日
 *      Author: pro
 */

#ifndef WDJ_CRAWLER_ENGINE_H_
#define WDJ_CRAWLER_ENGINE_H_

#include "crawl/crawler_engine.h"
#include "logic/base_values.h"

namespace crawlersvc_logic{

class WDJCrawlerImpl:public CrawlerStoreEngine{
public:
	WDJCrawlerImpl(){}
	virtual ~WDJCrawlerImpl(){}
public:
	base_logic::Value*  OnCrawlInfo(const int32 type,base_logic::Value* value);
private:
	base_logic::Value* OnCrawlAppDetails(base_logic::Value* value);
};

}




#endif /* WDJ_CRAWLER_ENGINE_H_ */
