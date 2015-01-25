/*
 * stroe_basic_info.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */

#ifndef STORE_BASIC_INFO_H_
#define STORE_BASIC_INFO_H_
#include "logic/logic_infos.h"
#include "basic/basictypes.h"
#include <string>
#include <list>
namespace storesvc_logic{


class AppSummaryInfo:public base_logic::AppInfos{
public:
	explicit AppSummaryInfo();
	AppSummaryInfo(const AppSummaryInfo& appsummary);

	AppSummaryInfo& operator = (const AppSummaryInfo& appsummary);

	base_logic::DictionaryValue* Release();

};

}



#endif /* STORE_BASIC_INFO_H_ */



