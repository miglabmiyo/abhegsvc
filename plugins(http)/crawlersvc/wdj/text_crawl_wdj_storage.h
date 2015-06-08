/*
 * text_crawl_wdj_storage.h
 *
 *  Created on: 2015年5月27日
 *      Author: Administrator
 */

#ifndef PLUGINS_CRAWLERSVC_WDJ_TEXT_CRAWL_WDJ_STORAGE_H_
#define PLUGINS_CRAWLERSVC_WDJ_TEXT_CRAWL_WDJ_STORAGE_H_
#include "storage/storage_base_engine.h"
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/zip.h"
#include "basic/unzip.h"
#include <string>

namespace crawlersvc_logic{

#define PACKET_LENGTH  sizeof(int32)
#define APPDETAILTYPE_SIZE sizeof(int32) + 64 +32
struct AppDetailType{
	int32 packet_length;
	char app_pack_name[64];
	char str_type[32];
};


#define APPDETAILCOMPLETE_SIZE sizeof(32) +
struct AppDetailComplete{
	int32 packet_length;
	std::string info;
};


class TestCrawlWDJStorage{
public:
	TestCrawlWDJStorage();
	virtual ~TestCrawlWDJStorage();
public:
	bool WriteAppDetailType(const std::string& name,base_logic::Value* value);
	bool WriteAppDetailComplete(const std::string& name,base_logic::Value* value);
private:
	scoped_ptr<crawlersvc_logic::CrawlerStorageBaseEngine> text_engine_;
	MZip                      mzip_;
	MUnZip                    munzip_;
	int64                     txt_indetfity_;
};
}




#endif /* PLUGINS_CRAWLERSVC_WDJ_TEXT_CRAWL_WDJ_STORAGE_H_ */
