/*
 * rsp_parser.h
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */

#ifndef RSP_PARSER_H_
#define RSP_PARSER_H_
#include "logic/base_values.h"
namespace crawlersvc_logic{

class BaseRspParser{
public:
	BaseRspParser(){};
	virtual ~BaseRspParser() = 0;
};


class JsonRspParser/*:public BaseRspParser*/{
public:
	static base_logic::Value* Deserialization(std::string* content);
};

class XmlRspParser:public BaseRspParser{
public:
	static base_logic::Value* Deserialization(std::string* content);
};




}



#endif /* RSP_PARSER_H_ */
