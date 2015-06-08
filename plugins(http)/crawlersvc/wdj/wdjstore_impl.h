/*
 * wdjstore_impl.h
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */

#ifndef WDJSTORE_IMPL_H_
#define WDJSTORE_IMPL_H_

#include "appstore_engine.h"
#include "wdj/wdjstore_impl.h"
#include "redis_crawl_wdj_storage.h"
#include "mysql_crawl_wdj_storage.h"
#include "parser_wdj_engine.h"
#include "text_crawl_wdj_storage.h"
#include "crawl/crawler_engine.h"
#include "basic/basictypes.h"
#include "config/config.h"
#include "basic/scoped_ptr.h"
namespace crawlersvc_logic{

class WDJStoreImpl:public AppStoreEngine{
public:
	WDJStoreImpl();
	virtual ~WDJStoreImpl();
public:
	void Init(std::list<base::ConnAddr>& addrlist);

	void Release();

	bool OnTasks(const int32 type);

	void OnTimeCheck();
public:
	bool OnReadDBInfoCrawl();
private:
	bool OnTest();
private:
	bool CrawlDetail(const int64 id,const std::string& url);

	base_logic::DictionaryValue* ParserUrl(const std::string& url);
private:
	scoped_ptr<crawlersvc_logic::CrawlerStoreEngine>    engine_; //爬虫引擎
	scoped_ptr<crawlersvc_logic::RedisCrawlWDJStorage>  redis_engine_;//
	scoped_ptr<crawlersvc_logic::MysqlCrawlWDJStorage>  mysql_engine_;//
	scoped_ptr<crawlersvc_logic::TestCrawlWDJStorage>   text_engine_;//
	scoped_ptr<crawlersvc_logic::ParserWDJEngine>       parser_engine_;//

private:
	int64                          from_;
	int64                          count_;

};

}




#endif /* WDJSTORE_IMPL_H_ */
