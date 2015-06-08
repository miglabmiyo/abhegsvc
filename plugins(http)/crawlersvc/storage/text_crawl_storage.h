/*
 * txt_crawl_storage.h
 *
 *  Created on: 2015年5月27日
 *      Author: Administrator
 */

#ifndef PLUGINS_CRAWLERSVC_STORAGE_TEXT_CRAWL_STORAGE_H_
#define PLUGINS_CRAWLERSVC_STORAGE_TEXT_CRAWL_STORAGE_H_
#include "storage/storage_base_engine.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include <string>

namespace crawlersvc_logic{

class TextCrawlStorage:public CrawlerStorageBaseEngine{
public:
	TextCrawlStorage();
	virtual ~TextCrawlStorage();
public:
	void Init(std::list<base::ConnAddr>& addrlist);
	void Release();
public:
	bool ReadData(const std::string& sql,base_logic::Value* value,
			void (*storage_get)(void*,base_logic::Value*));

	bool WriteData(const int32 type,base_logic::Value* value);

};
}


#endif /* PLUGINS_CRAWLERSVC_STORAGE_TEXT_CRAWL_STORAGE_H_ */
