/*
 * appstore_sprider.cc
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */
#include "appstore_connector.h"
#include "appstore_wandoujia_connector.h"
#include "qihoostore_connector.h"



namespace hacksvc_logic{


AppStoreConnector* AppStoreConnector::Create(int32 type){

	AppStoreConnector* engine = NULL;
    switch(type){

        case IMPL_WANDOUJIA:
        	engine = new AppStoreWandoujiaImpl();
            break;
        case IMPL_QIHOOSTORE:
        	engine = new QIHOOStoreImpl();
        	break;
        default:
        	break;
    }
    return engine;
}

}
