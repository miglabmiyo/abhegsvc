/*
 * ppstore_connector.h
 *
 *  Created on: 2015年4月28日
 *      Author: pro
 */

#ifndef PPSTORE_CONNECTOR_H_
#define PPSTORE_CONNECTOR_H_

#include "appstore_connector.h"
#include "basic/basic_info.h"
#include <list>
#include <string>

namespace hacksvc_logic{
class PPStoreImpl:public AppStoreConnector{
public:
	PPStoreImpl();
	virtual ~PPStoreImpl();
public:
	virtual void Init(std::list<base::ConnAddr>& list);
	virtual void Release();//释放

	virtual bool OnRequestAppStoreInfo(const int32 type);

	virtual void OnTimeCheck();

	//可删除
#if defined (__OLD_INTERFACE__)
	virtual bool OnRequestAppStoreInfo(const std::string& url,std::string& content){return true;}
#endif
private:
	bool OnRequestMainRecommend();
};
}




#endif /* PPSTORE_CONNECTOR_H_ */
