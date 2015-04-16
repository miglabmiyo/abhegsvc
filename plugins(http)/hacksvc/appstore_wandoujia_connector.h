/*
 * appstore_wandoujia_connector.h
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */

#ifndef APPSTORE_WANDOUJIA_CONNECTOR_H_
#define APPSTORE_WANDOUJIA_CONNECTOR_H_

#include "appstore_connector.h"
#include "basic/basic_info.h"
#include <list>
#include <string>

namespace hacksvc_logic{

class AppStoreWandoujiaImpl:public AppStoreConnector{
public:
	AppStoreWandoujiaImpl();
	virtual ~AppStoreWandoujiaImpl();
public:
	virtual void Init(std::list<base::ConnAddr>& addrlist); //初始化
	virtual void Release();//释放

	virtual bool OnRequestAppStoreInfo(const std::string& url,std::string& content);
private:
	bool RequestWandoujiaUrl(const std::string& url,std::string& content);
};

}

#endif /* APPSTORE_WANDOUJIA_CONNECTOR_H_ */
