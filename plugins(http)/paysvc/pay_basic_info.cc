/*
 * pay_basic_info.cc
 *
 *  Created on: 2015年3月12日
 *      Author: pro
 */

#ifndef PAY_BASIC_INFO_CC_
#define PAY_BASIC_INFO_CC_

#include "pay_basic_info.h"
namespace paysvc_logic{

PayUserInfo::PayUserInfo(){
	data_ = new Data();
}

PayUserInfo::PayUserInfo(const PayUserInfo& pay)
:data_(pay.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

PayUserInfo& PayUserInfo::operator =(const PayUserInfo& pay){
	if(pay.data_!=NULL){
		pay.data_->AddRef();
	}
	if(data_!=NULL){
		data_->Release();
	}
	data_ = pay.data_;
	return (*this);
}

ChrPoint::ChrPoint(){
	data_ = new Data();
}

ChrPoint::ChrPoint(const ChrPoint& point)
:data_(point.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

ChrPoint& ChrPoint::operator =(const ChrPoint& point){
	if(point.data_!=NULL){
		point.data_->AddRef();
	}
	if(data_!=NULL){
		data_->Release();
	}

	data_ = point.data_;
	return (*this);
}

}



#endif /* PAY_BASIC_INFO_CC_ */
