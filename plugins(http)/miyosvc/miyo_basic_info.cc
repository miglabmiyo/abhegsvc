/*
 * miyo_basic_info.cc
 *
 *  Created on: 2015年5月8日
 *      Author: pro
 */
#include "miyo_basic_info.h"
#include "logic/base_values.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"


namespace miyosvc_logic{

UserInfo::UserInfo(){
	data_ = new Data();
}

UserInfo::UserInfo(const UserInfo& userinfo)
:data_(userinfo.data_){
	//base_logic::UserInfo(userinfo.UserInfo);
	//if(data_!=NULL){
		//data_->AddRef();
	//}
	(*this) =userinfo;
	//LOG_DEBUG("UserInfo::UserInfo(const UserInfo& userinfo)");

}

UserInfo& UserInfo::operator =(const UserInfo& userinfo){
	base_logic::UserInfo::operator =(userinfo);

	if(userinfo.data_!=NULL){
		userinfo.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = userinfo.data_;
	//LOG_DEBUG("UserInfo& UserInfo::operator =(const UserInfo& userinfo)");
	return (*this);
}

bool UserInfo::JsonSerialization(std::string& json){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(base_logic::UserInfo::uid()!=0)
		dict->SetBigInteger(L"uid",base_logic::UserInfo::uid());
	if(base_logic::UserInfo::sex()!=0)
		dict->SetBigInteger(L"sex",base_logic::UserInfo::sex());
	if(base_logic::UserInfo::machine()!=0)
		dict->SetBigInteger(L"machine",base_logic::UserInfo::machine());
	if(base_logic::UserInfo::logintime()!=0)
		dict->SetBigInteger(L"logintime",base_logic::UserInfo::logintime());
	if(base_logic::UserInfo::type()!=0)
		dict->SetBigInteger(L"type",base_logic::UserInfo::type());
	if(!base_logic::UserInfo::session().empty())
		dict->SetString(L"session",base_logic::UserInfo::session());

	if(!base_logic::UserInfo::imei().empty())
		dict->SetString(L"imei",base_logic::UserInfo::imei());

	if(!base_logic::UserInfo::nickname().empty())
		dict->SetString(L"nickname",base_logic::UserInfo::nickname());

	if(!base_logic::UserInfo::city().empty())
		dict->SetString(L"city",base_logic::UserInfo::city());

	if(!base_logic::UserInfo::head().empty())
		dict->SetString(L"head",base_logic::UserInfo::head());

	if(!data_->token_.empty())
		dict->SetString(L"token",data_->token_);

	if(data_->miyo_id_!=0)
		dict->SetBigInteger(L"miyo_id",data_->miyo_id_);

	if(data_->latest_time_!=0)
		dict->SetBigInteger(L"lasttime",data_->latest_time_);

	 base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&json);
	 base_logic::Value* value = (base_logic::Value*)dict.release();
	 return engine->Serialize(*value);
	return true;
}

}



