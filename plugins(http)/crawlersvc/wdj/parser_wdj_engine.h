/*
 * parser_wdj_engine.h
 *
 *  Created on: 2015年6月4日
 *      Author: pro
 */

#ifndef PARSER_WDJ_ENGINE_H_
#define PARSER_WDJ_ENGINE_H_


#include "logic/base_values.h"
#include "logic/logic_infos.h"
namespace crawlersvc_logic{

class ParserWDJEngine{
public:
	ParserWDJEngine();
	virtual ~ParserWDJEngine();
public:
	bool PaserCompleteAppInfo(base_logic::Value* value,base_logic::AppInfos& info);
private:
	bool ParserCompleteApkUrl(base_logic::ListValue* apks_list,base_logic::AppInfos& info);
	bool ParserCompleteScreenshots(base_logic::DictionaryValue* screen,base_logic::AppInfos& info);
	bool ParserCompleteContent(std::string& content);

};
}




#endif /* PARSER_WDJ_ENGINE_H_ */
