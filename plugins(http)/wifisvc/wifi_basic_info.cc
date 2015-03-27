/*
 * wifi_basic_info.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#include "wifi_basic_info.h"
namespace wifisvc_logic{

ShareUser::ShareUser(){
	data_ = new Data();
}

ShareUser::ShareUser(const ShareUser& share)
:data_(share.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

ShareUser& ShareUser::operator =(const ShareUser& share){
	if(share.data_!=NULL){
		share.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = share.data_;
	return (*this);
}

base_logic::DictionaryValue* ShareUser::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->uid_!=0)
		dict->SetBigInteger(L"uid",data_->uid_);
	if(!data_->nickname_.empty())
		dict->SetString(L"nickname",data_->nickname_);
	if(!data_->head_.empty())
		dict->SetString(L"head",data_->head_);
	if(!data_->share_time_.empty())
		dict->SetString(L"share_time",data_->share_time_);

	return dict.release();
}


WifiInfo::WifiInfo(){
	data_ = new Data();
}

WifiInfo::WifiInfo(const WifiInfo& wifi)
:data_(wifi.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}


WifiInfo& WifiInfo::operator =(const WifiInfo& wifi){
	if(wifi.data_!=NULL){
		wifi.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = wifi.data_;
	return (*this);
}


base_logic::DictionaryValue* WifiInfo::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=0)
		dict->SetBigInteger(L"id",data_->id_);
	if(data_->type_!=0)
		dict->SetInteger(L"type",data_->type_);
	if(data_->latitude_!=0.0 && data_->longitude_!=0.0){
		dict->SetReal(L"latitude",data_->latitude_);
		dict->SetReal(L"longitude",data_->longitude_);
		dict->SetReal(L"distance",data_->distance_);
	}
	if(!data_->ssid_.empty())
		dict->SetString(L"ssid",data_->ssid_);
	if(!data_->pwd_.empty())
		dict->SetString(L"pwd",data_->pwd_);
	if(!data_->apid_.empty())
		dict->SetString(L"apid",data_->apid_);

	return dict.release();
}

}
