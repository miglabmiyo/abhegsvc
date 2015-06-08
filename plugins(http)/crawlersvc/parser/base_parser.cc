/*
 * base_parser.cc
 *
 *  Created on: 2015年6月4日
 *      Author: pro
 */
#include "base_parser.h"
#include "logic/http_serializer.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{

ParserEngine* ParserEngine::Create(int32 type){
	ParserEngine* engine = NULL;
	return engine;
}

JsonParserEngine::JsonParserEngine(){
}

bool JsonParserEngine::Serialization(std::string& str){

	return true;
}

base_logic::Value* JsonParserEngine::DeSerialization(std::string& str){
	std::string error_str;
	int error_code = 0;
	base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&str);
	return engine->Deserialize(&error_code,&error_str);
}

}


