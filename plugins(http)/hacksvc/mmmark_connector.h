/*
 * mmmark_connector.h
 *
 *  Created on: 2015年5月6日
 *      Author: pro
 */

#ifndef MMMARK_CONNECTOR_H_
#define MMMARK_CONNECTOR_H_
#include "appstore_connector.h"
#include "basic/basic_info.h"
#include "basic/scoped_ptr.h"
#include <list>
#include <string>


namespace hacksvc_logic{

class MMMarkStoreImpl:public AppStoreConnector{
public:
	MMMarkStoreImpl();
	virtual ~MMMarkStoreImpl();
public:
	virtual void Init(std::list<base::ConnAddr>& list);
	virtual void Release();//释放

	virtual bool OnRequestAppStoreInfo(const int32 type);

	virtual void OnTimeCheck();

	virtual bool GetTestContent(std::string& content);
	//可删除
#if defined (__OLD_INTERFACE__)
	virtual bool OnRequestAppStoreInfo(const std::string& url,std::string& content){return true;}
#endif
};

}

#endif /* MMMARK_CONNECTOR_H_ */
