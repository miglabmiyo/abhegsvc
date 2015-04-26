/*
 * news_snssdk_connector.h
 *
 *  Created on: 2015年4月23日
 *      Author: pro
 */

#ifndef NEWS_SNSSDK_CONNECTOR_H_
#define NEWS_SNSSDK_CONNECTOR_H_

#include "news_connector.h"
#include "basic/basic_info.h"
#include "basic/scoped_ptr.h"
#include <list>
#include <string>
namespace hacksvc_logic{

class NewsSnsSDKImpl:public NewsConnector{
public:
	NewsSnsSDKImpl();
	virtual ~NewsSnsSDKImpl();
public:
	virtual void Init(std::list<base::ConnAddr>& addrlist); //初始化
	virtual void Release();//释放

	virtual bool OnRequestNews(const int32 type);

	virtual base_logic::Value*  ParserNewsContent(std::string& content);
	virtual void OnTimeCheck();


	bool GetTestContent(std::string& content);

private:
	bool OnNewsRecommend();
	bool OnRequestNewsRecommend(std::string& content);
	bool OnReplaceRecommend(base_logic::Value* value,const bool del_last = false);
	void ReadContentData();
private:
	void CreateAdValue();
	void StorageData(base_logic::Value* value);
private:
	scoped_ptr<base_logic::DictionaryValue>  ad_value_;
	std::string                              content_;
};

}


#endif /* NEWS_SNSSDK_CONNECTOR_H_ */
