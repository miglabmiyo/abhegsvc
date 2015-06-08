/*
 * redis_crawl_storage.h
 *
 *  Created on: 2015年5月21日
 *      Author: Administrator
 */

#ifndef PLUGINS_CRAWLERSVC_STORAGE_REDIS_CRAWL_STORAGE_H_
#define PLUGINS_CRAWLERSVC_STORAGE_REDIS_CRAWL_STORAGE_H_
#include "storage_base_engine.h"
#include "logic/base_values.h"
#include <list>

namespace crawlersvc_logic{

class RedisCrawlStorage:public CrawlerStorageBaseEngine{
public:
	static RedisCrawlStorage* Instance();
	static void FreeInstance();
public:
	RedisCrawlStorage(){}
	virtual ~RedisCrawlStorage(){}
public:
	void Init(std::list<base::ConnAddr>& addrlist); //初始化
	void Release();//释放
public:
	bool WriteData(const int32 type,base_logic::Value* value) ;

	bool ReadData(const std::string& sql,base_logic::Value* value,
			void (*storage_get)(void*,base_logic::Value*)){return true;}
private:
	bool WriteHashData(base_logic::Value* value);
private:
	static RedisCrawlStorage*  instance_;
};
}


#endif /* PLUGINS_CRAWLERSVC_STORAGE_REDIS_CRAWL_STORAGE_H_ */
