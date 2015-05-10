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

bool UserInfo::JsonDeserialization(std::string& json){
	std::string error_str;
	int error_code = 0;
	bool r = false;
	base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&json);
	base_logic::DictionaryValue*  value = (base_logic::DictionaryValue*)(engine->Deserialize(&error_code,&error_str));
	if(value==NULL)
		return false;
	int64 uid = 0;
	int64 sex = 0;
	int64 machine = 0;
	int64 logintime = 0;
	int64 type = 0;
	int64 miyo_id =0;
	int64 last_time = 0;
	std::string session;
	std::string imei;
	std::string nickname;
	std::string city;
	std::string head;
	std::string token;

	r = value->GetBigInteger(L"uid",&uid);
	if(r)
		base_logic::UserInfo::set_uid(uid);

	r = value->GetBigInteger(L"sex",&sex);
	if(r)
		base_logic::UserInfo::set_sex(sex);

	r = value->GetBigInteger(L"machine",&machine);
	if(r)
		base_logic::UserInfo::set_machine(machine);

	r = value->GetBigInteger(L"logintime",&logintime);
	if(r)
		base_logic::UserInfo::set_logintime(logintime);

	r = value->GetBigInteger(L"type",&type);
	if(r)
		base_logic::UserInfo::set_type(type);

	r = value->GetBigInteger(L"miyo_id",&miyo_id);
	if(r)
		data_->miyo_id_ = miyo_id;

	r = value->GetBigInteger(L"last_time",&last_time);
	if(r)
		data_->latest_time_ = last_time;

	r = value->GetString(L"session",&session);
	if(r)
		base_logic::UserInfo::set_session(session);

	r = value->GetString(L"imei",&imei);
	if(r)
		base_logic::UserInfo::set_imei(imei);

	r = value->GetString(L"nickname",&nickname);
	if(r)
		base_logic::UserInfo::set_nickname(nickname);

	r = value->GetString(L"city",&city);
	if(r)
		base_logic::UserInfo::set_city(city);

	r = value->GetString(L"head",&head);
	if(r)
		base_logic::UserInfo::set_head(head);

	r = value->GetString(L"token",&token);
	if(r)
		data_->token_ = token;

	return true;
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



