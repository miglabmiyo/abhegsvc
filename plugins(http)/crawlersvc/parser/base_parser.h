/*
 * base_parser.h
 *
 *  Created on: 2015年6月4日
 *      Author: pro
 */

#ifndef CRAWLER_SVC_BASE_PARSER_H_
#define CRAWLER_SVC_BASE_PARSER_H_

#include "logic/base_values.h"
#include "basic/basictypes.h"

namespace crawlersvc_logic{


enum PARSERTYPE{
	JSON_TYPE = 1,
	XML_TYPE = 2
};

class ParserEngine{
public:
	ParserEngine* Create(int32 type);
public:
	virtual ~ParserEngine(){};
public:
	virtual base_logic::Value* Serialization(const std::string& str) = 0;
	virtual bool DeSerialization(std::string& str,base_logic::Value* value) = 0;

};

class JsonParserEngine:public ParserEngine{
public:
	JsonParserEngine();
	virtual ~JsonParserEngine(){};
public:
	bool Serialization(std::string& str);
	base_logic::Value* DeSerialization(std::string& str);
};

class XmlParserEngine:public ParserEngine{

};

}


#endif /* BASE_PARSER_H_ */
