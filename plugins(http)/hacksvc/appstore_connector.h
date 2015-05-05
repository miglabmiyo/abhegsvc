/*
 * appstore_connector.h
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */

#ifndef APP_STORE_CONNECTOR_H_
#define APP_STORE_CONNECTOR_H_

#include "logic/base_values.h"
#include "basic/basic_info.h"
#include <list>

namespace hacksvc_logic{

enum AppStoreType{
	IMPL_WANDOUJIA = 0,
	IMPL_PPSTORE = 1,
	IMPL_QIHOOSTORE = 2
};

enum AppReqType{
	IMPL_MAIN_RECOMMEND =0,
	IMPL_ADVERT = 1,
	IMPL_GAME_RECOMMEND = 2,
	IMPL_GAME_RANK = 3
};

class AppStoreConnector{
public:
	static AppStoreConnector* Create(int32 type);
public:
	virtual void Init(std::list<base::ConnAddr>& addrlist) = 0; //初始化
	virtual void Release() = 0;//释放

	//可删除
#if defined (__OLD_INTERFACE__)
	virtual bool OnRequestAppStoreInfo(const std::string& url,std::string& content) =0;
#endif
	virtual bool OnRequestAppStoreInfo(const int32 type) = 0;

	virtual void OnTimeCheck() = 0;

	virtual bool GetTestContent(std::string& content) = 0;
};

/*
class AppStoreConnectorEngine{
public:
	AppStoreConnectorEngine(){}

	virtual ~AppStoreConnectorEngine(){}

	static void Create(int32 type){
		appstore_connector_engine_ = AppStoreConnector::Create(hacksvc_logic::IMPL_WANDOUJIA);
	}

	static AppStoreConnector* GetAppStoreConnctorEngine(){
		return appstore_connector_engine_;
	}

	static void FreeAppStoreConnectorEngine(){
		delete appstore_connector_engine_;
	}

private:
	static AppStoreConnectorEngine* appstore_connector_engine_;
};*/
}




#endif /* APP_STORE_SPRIDER_H_ */
