/*
 * news_connector.cc
 *
 *  Created on: 2015年4月23日
 *      Author: pro
 */
#include "news_connector.h"
#include "news_snssdk_connector.h"

namespace hacksvc_logic{

NewsConnector* NewsConnector::Create(int32 type){
	NewsConnector* engine = NULL;

	switch(type){
	case IMPL_SNSSDK:
		engine = new NewsSnsSDKImpl();
		break;
	default:
		break;
	}
	return engine;
}
}
