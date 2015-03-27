/*
 * comm_impl.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */

#include "user_comm_head.h"

namespace netcomm_recv{

bool GetNumberAndString(base_logic::Value* value,std::string& result){
	bool r = false;
	if(value->GetType()==base_logic::Value::TYPE_BIG_INTEGER){
		int64 bigint_value;
		r = value->GetAsBigInteger(&bigint_value);
		std::stringstream os;
		os<<bigint_value;
		result = os.str();
		}else{
		r = value->GetAsString(&result);
	}
	return result.empty()?false:true;
}
void QucikLogin::Init(){
	bool r = false;
	//imei 有些是数字 有些是字符串
	base_logic::Value* value;
	r = m_->Get(L"imei",&value);
	if(value->GetType()==base_logic::Value::TYPE_BIG_INTEGER){
		int64 bigint_imei;
		value->GetAsBigInteger(&bigint_imei);
		std::stringstream os;
		os<<bigint_imei;
		imei_ = os.str();
	}else{
		value->GetAsString(&imei_);
	}
	if(!r) error_code_ = IMEI_LACK;
	GETBIGINTTOINT(L"machine",machine_);
	if(!r) error_code_ = MACHINE_LACK;
}

}

namespace netcomm_send{

void HeadPacket::GetJsonSerialize(std::string* json){
	 base_logic::ValueSerializer* engine = base_logic::ValueSerializer::Create(0,json);
	 base_logic::Value* value = (base_logic::Value*)this->release();
	 engine->Serialize(*value);
}

}


