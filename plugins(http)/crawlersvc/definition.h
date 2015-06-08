/*
 * definition.h
 *
 *  Created on: 2015年5月12日
 *      Author: pro
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_


enum CRAWLERSTORE_TYPE{
	IMPL_WANDOUJIA = 0
};

enum APPSTORE_REQ_TYPE{
	IMPL_MAIN_RECOMMEND = 0,
	IMPL_APP_DETAILS = 1
};

enum TASK_TYPE{
	TASK_TEST = 0,
	TASK_DB_READ = 1,
};





//url

#define WDJ_DETAILS_HOST "http://api.wandoujia.com/v1/apps/"

#endif /* DEFINITION_H_ */
