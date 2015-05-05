/*
 * personal_recommend.cc
 *
 *  Created on: 2015年4月27日
 *      Author: pro
 */
#include "personal_recommend.h"
#include "db_comm.h"

namespace findsvc_logic{


PersonalRecommend* PersonalRecommend::instance_ =  NULL;

PersonalRecommend* PersonalRecommend::GetInstance(){
	if(instance_==NULL){
		instance_ = new PersonalRecommend();
	}
	return instance_;
}

void PersonalRecommend::FreeInstance(){
	delete instance_;
}

void PersonalRecommend::PersonalRecommendApp(const int64 uid,
		std::list<base_logic::AppInfos>& list){
	findsvc_logic::DBComm::GetPersonalApp(uid,list);
}

void PersonalRecommend::PersonalRecommendGame(const int64 uid,
		std::list<base_logic::AppInfos>& list){
	findsvc_logic::DBComm::GetPersonalGame(uid,list);
}

void PersonalRecommend::PersonalRecommendBook(const int64 uid,
		std::list<base_logic::BookInfo>& list){
	findsvc_logic::DBComm::GetPersonalBook(uid,list);
}

void PersonalRecommend::PersonalRecommendMovie(const int64 uid,
		std::list<base_logic::Movies>& list){
	findsvc_logic::DBComm::GetPersonalMovie(uid,list);
}


}


