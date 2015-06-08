/*
 * wdj_http_api.cc
 *
 *  Created on: 2015年5月12日
 *      Author: pro
 */
#include "wdj/wdj_http_api.h"
#include "http/http_api.h"
#include "parser/rsp_parser.h"
#include "basic/scoped_ptr.h"
#include "logic/logic_comm.h"
#include "definition.h"

namespace crawlersvc_logic{


base_logic::Value* WDJHttpAPI::APPDetailInfo(const std::string& identifier,
		base_logic::DictionaryValue* value){

	std::string url = WDJ_DETAILS_HOST+identifier;
	std::string result;
	base_http::HttpAPI::RequestGetMethod(url,value,result);
	if(result.empty())
		return NULL;

	//base_logic::DictionaryValue* response = (base_logic::DictionaryValue*)(crawlersvc_logic::JsonRspParser::Deserialization(&result));
	//if(response){delete response;response = NULL;}
	base_logic::Value* response = crawlersvc_logic::JsonRspParser::Deserialization(&result);
	//if(response!=NULL){delete repsonse;response=NULL;}
	//ClearAPPDetailInfo(response);
	return NULL;
}



/*
void WDJHttpAPI::ClearAPPDetailInfo(base_logic::Value* value){
	base_logic::DictionaryValue* response = (base_logic::DictionaryValue*)(value);
	base_logic::DictionaryValue::key_iterator it = response->begin_keys();
	for(;it!=response->end_keys();++it){
		bool r = false;
		base_logic::Value* dict_value = NULL;
		std::wstring key = (*it);
		r  =response->Get(key,&dict_value);
		if(!r)
			continue;
		//LOG_DEBUG2("key %s value type %d",key.c_str(),dict_value->GetType());
		if(dict_value->GetType()==base_logic::Value::TYPE_DICTIONARY){
			base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)(dict_value);
			if(dict!=NULL){delete dict;dict=NULL;}
		}else if(dict_value->GetType()==base_logic::Value::TYPE_LIST){
			base_logic::ListValue* list = (base_logic::ListValue*)(dict_value);
			if(list!=NULL){delete list;list=NULL;}
		}
	}

	//if(response!=NULL){delete response;response=NULL;}
}
*/
}



