/*
 * hack_basic_info.cc
 *
 *  Created on: 2015年4月16日
 *      Author: kerry
 */

#include "hack_basic_info.h"

namespace hacksvc_logic{

AppSummaryParam::AppSummaryParam(){
	data_ = new Data();
}

AppSummaryParam::AppSummaryParam(const AppSummaryParam& param)
:data_(param.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

AppSummaryParam& AppSummaryParam::operator =(const AppSummaryParam& param){
	if(param.data_!=NULL){
		param.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}

	data_ = param.data_;
	return (*this);
}

}
