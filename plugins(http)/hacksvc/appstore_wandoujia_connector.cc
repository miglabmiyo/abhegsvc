/*
 * appstore_wandoujia_connector.cc
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */

#include "appstore_wandoujia_connector.h"

namespace hacksvc_logic{

AppStoreWandoujiaImpl::AppStoreWandoujiaImpl(){

}

AppStoreWandoujiaImpl::~AppStoreWandoujiaImpl(){

}

void AppStoreWandoujiaImpl::Init(std::list<base::ConnAddr>& addrlist){

}

void AppStoreWandoujiaImpl::Release(){

}

bool AppStoreWandoujiaImpl::GetAppSummaryInfo(const std::string& host,const std::string& path){

	//向豌豆荚请求应用信息详情
	bool r = false;
	std::stringstream os;
	std::string content;
	return true;
}
}




