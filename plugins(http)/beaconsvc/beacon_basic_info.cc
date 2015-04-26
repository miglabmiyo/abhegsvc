/*
 * beacon_basic_info.cc
 *
 *  Created on: 2015年4月22日
 *      Author: pro
 */

#include "beacon_basic_info.h"
namespace beaconsvc_logic{


BeaconInfo::BeaconInfo(){
	data_ = new Data();
}

BeaconInfo::BeaconInfo(const BeaconInfo& beacon)
:data_(beacon.data_){

}

BeaconInfo& BeaconInfo::operator =(const BeaconInfo& beacon){
	if(beacon.data_!=NULL){
		beacon.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}

	data_ = beacon.data_;
	return (*this);
}


BeaconMerchant::BeaconMerchant(){
	data_ = new Data();
}

BeaconMerchant::BeaconMerchant(const BeaconMerchant& merchant)
:data_(merchant.data_){

}

BeaconMerchant& BeaconMerchant::operator =(const BeaconMerchant& merchant){
	if(merchant.data_!=NULL){
		merchant.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}

	data_ = merchant.data_;
	return (*this);
}

base_logic::DictionaryValue* BeaconMerchant::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=0)
		dict->SetBigInteger(L"id",data_->id_);
	if(data_->bid_!=0)
		dict->SetBigInteger(L"bid",data_->bid_);
	if(!data_->intor_.empty())
		dict->SetString(L"intor",data_->intor_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(!data_->pic_.empty())
		dict->SetString(L"pic",data_->pic_);
	if(!data_->url_.empty())
		dict->SetString(L"url",data_->url_);
	return dict.release();
}


}



