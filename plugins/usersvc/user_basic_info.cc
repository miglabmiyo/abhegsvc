/*
 * user_basic_info.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#include "user_basic_info.h"
namespace usersvc_logic{

UserInfo::UserInfo(){
	data_ = new Data();
}


UserInfo::UserInfo(const UserInfo& userinfo)
:data_(userinfo.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

UserInfo& UserInfo::operator =(const UserInfo& userinfo){
	if(userinfo.data_!=NULL){
		userinfo.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = userinfo.data_;
	return (*this);
}

}
