/*
 * personal_recommend.h
 *
 *  Created on: 2015年4月27日
 *      Author: pro
 */

#ifndef PERSONAL_RECOMMEND_H_
#define PERSONAL_RECOMMEND_H_

#include "logic/logic_infos.h"
#include "basic/basictypes.h"
#include <list>

namespace findsvc_logic{

class PersonalRecommend{
public:
	PersonalRecommend(){}
	virtual ~PersonalRecommend(){}
public:
	static PersonalRecommend* GetInstance();
	static void FreeInstance();
private:
	static PersonalRecommend* instance_;

public:
	void PersonalRecommendApp(const int64 uid,std::list<base_logic::AppInfos>& list);
	void PersonalRecommendGame(const int64 uid,std::list<base_logic::AppInfos>& list);
	void PersonalRecommendBook(const int64 uid,std::list<base_logic::BookInfo>& list);
	void PersonalRecommendMovie(const int64 uid,std::list<base_logic::Movies>& list);
};
}



#endif /* PERSONAL_RECOMMEND_H_ */
