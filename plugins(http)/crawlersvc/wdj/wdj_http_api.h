/*
 * wdj_http_api.h
 *
 *  Created on: 2015年5月12日
 *      Author: pro
 */

#ifndef WDJ_HTTP_API_H_
#define WDJ_HTTP_API_H_

#include "crawl/http_api.h"
#include "logic/base_values.h"
namespace crawlersvc_logic{

class WDJHttpAPI:public HttpApi{
public:
	static base_logic::Value* APPDetailInfo(const std::string& identifier,
			base_logic::DictionaryValue* value);

	//static void ClearAPPDetailInfo(base_logic::Value* value);
};

}


#endif /* WDJ_HTTP_API_H_ */
