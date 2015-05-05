/*
 * ppstore_connector.cc

 *
 *  Created on: 2015年4月28日
 *      Author: pro
 */
#include "appstore_connector.h"
#include "ppstore_connector.h"

namespace hacksvc_logic{
PPStoreImpl::PPStoreImpl(){

}

PPStoreImpl::~PPStoreImpl(){

}


bool PPStoreImpl::OnRequestAppStoreInfo(const int32 type){
	bool r = false;
	switch(type){
	case IMPL_MAIN_RECOMMEND:
		break;
	case IMPL_ADVERT:
		break;
	case IMPL_GAME_RECOMMEND:
		break;
	case IMPL_GAME_RANK:
		break;
	}

	return true;

}


bool PPStoreImpl::OnRequestMainRecommend(){
	std::string url = "http://sjzs-api.25pp.com/api/op.rec.app.list";
	bool r = false;
	std::string content = "{\"sign\":\"a8445a99c43e754c245358b8eda5023d\",\"data\":{\"flags\":193,\"offset\":0,\"count\":10,\"screenWidth\":1080,\"positionId\":465},\"id\":4376037553632202584,\"client\":{\"caller\":\"secret.pp.client\",\"versionCode\":1335,\"ex\":{\"aid\":\"QYQxbsG5YPnu0TJkxtVt\/g==\",\"productId\":2001,\"ch\":\"PP_2\",\"osVersion\":19},\"VName\":\"3.3.0\",\"uuid\":\"MI 4LTE|Xiaomi|866963027412875|74:51:ba:d4:1f:d0\"},\"encrypt\":\"md5\"}";
	r = base_logic::LogicUnit::RequestPostMethod(url,content);
	return r;
}


}


