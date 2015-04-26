/*
 * news_connector.h
 *
 *  Created on: 2015年4月23日
 *      Author: pro
 */

#ifndef NEWS_CONNECTOR_H_
#define NEWS_CONNECTOR_H_
#include "logic/base_values.h"
#include "basic/basic_info.h"
#include <list>

namespace hacksvc_logic{

enum NewsType{
	IMPL_SNSSDK = 0,
	IMPL_163 = 1
};

enum ReqType{
	TYPE_RECOMMEND = 0
};

class NewsConnector{
public:
	static NewsConnector* Create(int32 type);
public:
	virtual void Init(std::list<base::ConnAddr>& addrlist) = 0; //初始化
	virtual void Release() = 0;//释放

	virtual bool OnRequestNews(const int32 type) = 0; //请求

	virtual base_logic::Value*  ParserNewsContent(std::string& content) = 0;

	virtual void OnTimeCheck() = 0;

	virtual bool GetTestContent(std::string& content) = 0;
};
}





#endif /* NEWS_CONNECTOR_H_ */
