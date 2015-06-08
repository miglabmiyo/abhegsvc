/*
 * crawler_engine.cc
 *
 *  Created on: 2015年5月12日
 *      Author: pro
 */
#include "crawl/crawler_engine.h"
#include "definition.h"
#include "wdj/wdj_crawler_engine.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{


CrawlerStoreEngine* CrawlerStoreEngine::Create(int32 type){
	CrawlerStoreEngine* engine = NULL;
	switch(type){
	case CRAWLER_ENGINE_WDJ:
		engine = new crawlersvc_logic::WDJCrawlerImpl();
		break;
	default:
		break;
	}

	return engine;
}

}



