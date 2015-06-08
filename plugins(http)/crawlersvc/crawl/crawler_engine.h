/*
 * crawler_engine.h
 *
 *  Created on: 2015年5月12日
 *      Author: pro
 */

#ifndef CRAWLER_ENGINE_H_
#define CRAWLER_ENGINE_H_

#include "appstore_engine.h"
#include "basic/basictypes.h"

namespace crawlersvc_logic{

enum CRAWLERENGINE{
	CRAWLER_ENGINE_WDJ = 0
};

class CrawlerEngine{
public:
	virtual base_logic::Value*  OnCrawlInfo(const int32 type,base_logic::Value* value) = 0;
};



class CrawlerStoreEngine:public CrawlerEngine{
public:
	static CrawlerStoreEngine* Create(int32 type);
};

}



#endif /* CRAWLER_ENGINE_H_ */
