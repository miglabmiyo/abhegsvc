/*
 * http_api.h
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */

#ifndef HTTP_API_H_
#define HTTP_API_H_
#include "crawl/crawler_api.h"
namespace crawlersvc_logic{

class BaseHttpApi:public CrawlerApi{
public:
	BaseHttpApi(){}
	virtual ~BaseHttpApi(){}
};

class HttpApi:public BaseHttpApi{
public:
	HttpApi(){}
	virtual ~HttpApi(){}
};

class HttpsApi:public BaseHttpApi{
public:
	HttpsApi(){}
	virtual ~HttpsApi(){}
};


}




#endif /* HTTP_API_H_ */
