/*
 * rsp_parser.h
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */

#include "parser/rsp_parser.h"
#include "http/http_api.h"
#include "check/newmacro.h"
#include "basic/scoped_ptr.h"
#include <string>
namespace crawlersvc_logic{


base_logic::Value* JsonRspParser::Deserialization(std::string* content){
	std::string error_str;
	int error_code = 0;
	scoped_ptr<base_logic::ValueSerializer>engine(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,content));
	return engine->Deserialize(&error_code,&error_str);
	//return base_http::HttpAPI::ResponseJsonSerialization(content);
}

base_logic::Value* XmlRspParser::Deserialization(std::string* content){

	std::string error_str;
	int error_code = 0;
	scoped_ptr<base_logic::ValueSerializer> engine(base_logic::ValueSerializer::Create(base_logic::IMPL_XML,content));
	return engine->Deserialize(&error_code,&error_str);
	//return base_http::HttpAPI::ResponseXmlSerializetion(content);
}




}

