/*
 * appstore_sprider.cc
 *
 *  Created on: 2015年4月16日
 *      Author: pro
 */
#include "appstore_engine.h"
#include "wdj/wdjstore_impl.h"
#include "check/newmacro.h"

namespace crawlersvc_logic{


AppStoreEngine* AppStoreEngine::Create(int32 type){

	AppStoreEngine* engine = NULL;
    switch(type){
    	case IMPL_WANDOUJIA:
    		engine =  new crawlersvc_logic::WDJStoreImpl();
    		break;
        default:
        	break;
    }
    return engine;
}


}
