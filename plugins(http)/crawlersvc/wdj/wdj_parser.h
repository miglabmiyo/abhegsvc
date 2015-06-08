/*
 * wdj_parser.h
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */

#ifndef WDJ_PARSER_H_
#define WDJ_PARSER_H_
#include "parser/rsp_parser.h"
#include "logic/base_values.h"

namespace crawlersvc_logic{

class WdjParser{
public:
	static bool WdjAppDetailsDataFormat(std::string* content);
};


}




#endif /* WDJ_PARSER_H_ */
