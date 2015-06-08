/*
 * wdj_parser.cc
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */

#include "wdj/wdj_parser.h"
#include "check/newmacro.h"

namespace crawlersvc_logic{

bool WdjParser::WdjAppDetailsDataFormat(std::string* content){
	base_logic::Value* detail = crawlersvc_logic::JsonRspParser::Deserialization(content);
	return true;
}

}




