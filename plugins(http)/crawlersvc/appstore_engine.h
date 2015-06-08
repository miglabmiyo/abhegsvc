/*
 * appstore_connector.h
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */

#ifndef APP_STORE_ENGINE_H_
#define APP_STORE_ENGINE_H_

#include "logic/base_values.h"
#include "basic/basic_info.h"
#include "config/config.h"
#include "basic/basictypes.h"
#include "check/debugnew.h"
#include <list>

namespace crawlersvc_logic{

enum AppStoreType{
	IMPL_WANDOUJIA = 1,
	IMPL_QIHOOSTORE = 2
};

enum CRAWLERTYPE{
	IMPL_UNIT_DETAIL_INFO = 0
};

class AppStoreEngine{
public:
	static AppStoreEngine* Create(int32 type);
	virtual ~AppStoreEngine(){}
public:
	virtual void Init(std::list<base::ConnAddr>& addrlist) = 0; //初始化
	virtual void Release() = 0;//释放

	//virtual bool OnRequestAppStoreInfo(const int32 type,base_logic::Value* value) = 0;

	virtual bool OnTasks(const int32 type) = 0;

	virtual void OnTimeCheck() = 0;
};


}




#endif /* APP_STORE_SPRIDER_H_ */
