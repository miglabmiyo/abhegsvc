/*
 * wdj_crawler_engine.cc
 *
 *  Created on: 2015骞�5鏈�12鏃�
 *      Author: pro
 */


#include "wdj/wdj_crawler_engine.h"
#include "wdj/wdj_http_api.h"
#include "definition.h"
#include "logic/base_values.h"
#include "logic/logic_comm.h"
#include "basic/scoped_ptr.h"
#include "check/newmacro.h"
#include <string>
namespace crawlersvc_logic{

base_logic::Value* WDJCrawlerImpl::OnCrawlInfo(const int32 type,base_logic::Value* value){
	base_logic::Value* result = NULL;
	switch(type){
	case IMPL_APP_DETAILS:
		result = OnCrawlAppDetails(value);
		break;
	default:
		break;
	}
	return result;
}



base_logic::Value* WDJCrawlerImpl::OnCrawlAppDetails(base_logic::Value* value){
	http://api.wandoujia.com/v1/apps/com.fingersoft.hillclimb?timestamp=1428992136630&id=wandoujia_android&token=f0ca1ccc1a60ef3e0ce6105b353ab762
	base_logic::DictionaryValue* dict =(base_logic::DictionaryValue*)value;
	std::string identifier;
	dict->GetString(L"identifier",&identifier);
	LOG_DEBUG2("identifier %s",identifier.c_str());
	return crawlersvc_logic::WDJHttpAPI::APPDetailInfo(identifier,dict);
}

}
