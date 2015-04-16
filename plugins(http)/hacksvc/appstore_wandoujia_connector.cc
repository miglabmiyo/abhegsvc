/*
 * appstore_wandoujia_connector.cc
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */

#include "appstore_wandoujia_connector.h"
#include "http/http_method.h"
#include "basic/basic_util.h"
#include <sstream>

namespace hacksvc_logic{

AppStoreWandoujiaImpl::AppStoreWandoujiaImpl(){

}

AppStoreWandoujiaImpl::~AppStoreWandoujiaImpl(){

}

void AppStoreWandoujiaImpl::Init(std::list<base::ConnAddr>& addrlist){

}

void AppStoreWandoujiaImpl::Release(){

}

bool AppStoreWandoujiaImpl::OnRequestAppStoreInfo(const std::string& url,std::string& content){

	//向豌豆荚请求应用信息详情
	bool r = false;
	int i = 0;

	do{
		r = RequestWandoujiaUrl(url,content);
		if(!r)
			return false;
		i++;
		if(i>=3)
			return false;
	}while(true);
	return true;
}

bool AppStoreWandoujiaImpl::RequestWandoujiaUrl(const std::string& url,std::string& content){
	http::HttpMethodGet wandoujia_http(url);
	bool r = wandoujia_http.Get();
	if(!r)
		return r;
	r = wandoujia_http.GetContent(content);
	if(!r)
		return r;
	return true;
}

}




