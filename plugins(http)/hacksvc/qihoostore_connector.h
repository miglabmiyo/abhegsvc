/*
 * 360store_connector.h
 *
 *  Created on: 2015年4月29日
 *      Author: pro
 */

#ifndef QIHOOSTORE_CONNECTOR_H_
#define QIHOOSTORE_CONNECTOR_H_

#include "appstore_connector.h"
#include "basic/basic_info.h"
#include "basic/scoped_ptr.h"
#include <list>
#include <string>

namespace hacksvc_logic{

class QIHOOStoreImpl:public AppStoreConnector{
public:
	QIHOOStoreImpl();
	virtual ~QIHOOStoreImpl();
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
private:
	base_logic::Value* ParserContent(std::string& content);

	void OnMainRecommend();

	bool OnReplaceMain(base_logic::Value* value);

	void StorageData(base_logic::Value* value);

private:
	bool OnRequestMainRecommend(std::string& content);


	std::string    content_;
};
}

#endif /* 360STORE_CONNECTOR_H_ */
