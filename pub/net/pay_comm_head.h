/*
 * pay_comm_head.h
 *
 *  Created on: 2015年03月03日
 *      Author: kerry
 */

#ifndef _NET_PAY_COMM_HEAD_H_
#define _NET_PAY_COMM_HEAD_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

class PhoneRegister:public HeadPacket{
public:
	PhoneRegister(NetBase* m)
	:HeadPacket(m)
	,phone_number_(0)
	,platform_(0){
		Init();
	}

	inline void Init(){
		bool r = false;
		//imei 有些是数字 有些是字符串
		base_logic::Value* value;
		r = m_->Get(L"imei",&value);
		GetNumberAndString(value,imei_);
		if(!r) error_code_ =IMEI_LACK;

		//sim 有些是数字 有些是字符串
		r = m_->Get(L"sim",&value);
		GetNumberAndString(value,sim_);
		if(!r) sim_ = "0";
		//获取号码
		GETBIGINTTOINT(L"phone",phone_number_);
		if(!r) error_code_ =PHONE_LACK;
		//获取包名
		r = m_->GetString(L"pkg_name",&pkg_name_);
		if(!r) error_code_ = PKG_NAME_LACK;

	}

	const int64 phone_number() const {return phone_number_;}
	const int64 platform() const {return this->platform_;}
	const std::string& imei() const {return imei_;}
	const std::string& sim() const {return sim_;}
	const std::string& pkg_name() const {return this->pkg_name_;}

private:
	int64       platform_;
	int64       phone_number_;
	std::string imei_;
	std::string sim_;
	std::string pkg_name_;
};


//因三网融合计费点无回调机制故暂使用HTTP协议
//支付用户登录
class PayUserLogin:public HeadPacket{
public:
	PayUserLogin(NetBase* m)
	:HeadPacket(m){
		Init();
	}

	inline void Init(){
			bool r = false;
			//imei 有些是数字 有些是字符串
			base_logic::Value* value;
			r = m_->Get(L"imei",&value);
			GetNumberAndString(value,imei_);
			if(!r) error_code_ =IMEI_LACK;

			//sim 有些是数字 有些是字符串
			r = m_->Get(L"sim",&value);
			GetNumberAndString(value,sim_);
			if(!r) error_code_ =SIM_LACK;

			r = m_->GetBigInteger(L"platform",&platform_);
			if(!r) error_code_ = PLATFORM_LACK;

		}

		const int64 platform() const {return this->platform_;}
		const std::string& imei() const {return this->imei_;}
		const std::string& sim() const {return this->sim_;}

private:
	int64          platform_;
	std::string    imei_;
	std::string    sim_;
};

class PayGetSMSChrPoint:public LoginSignHeadPacket{
public:
	PayGetSMSChrPoint(NetBase* m)
	:LoginSignHeadPacket(m){
		Init();
	}

	inline void Init(){
		LoginSignHeadPacket::Init();
		bool r = false;
		r = m_->GetBigInteger(L"platform",&platform_);
		if(!r) error_code_ = PLATFORM_LACK;

		r = m_->GetBigInteger(L"paynumber",&paynumber_);
		if(!r) paynumber_ = 1;
	}

	const int64 platform() const {return this->platform_;}
	const int64 paynumber() const {return this->paynumber_;}
private:
	int64 platform_;
	int64 paynumber_;
};

class PayUpdateSerialState:public LoginSignHeadPacket{
public:
	PayUpdateSerialState(NetBase* m)
	:LoginSignHeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
		r = m_->GetBigInteger(L"state",&state_);
		if(!r) error_code_ = STATE_LACK;

		//流水号可能超过INT64 故使用字符串
		base_logic::Value* value;
		r = m_->Get(L"serial_number",&value);
		if(r)
			GetNumberAndString(value,serial_number_);
		//运营商流水号有可能是纯数字也有可能是字符串
		r = m_->Get(L"opertor_serial",&value);
		if(r)
			GetNumberAndString(value,opertor_serial_);
		if(!r) opertor_serial_ = "0";
	}

	const int64 state() const {return this->state_;}
	const std::string& serial_number() const {return this->serial_number_;}
	const std::string& opertor_serial() const {return this->opertor_serial_;}
private:
	int64           state_;
	std::string     serial_number_;
	std::string     opertor_serial_;
};
}


namespace netcomm_send{

class PayUserLogin:public HeadPacket{
public:
	PayUserLogin(){
		base_.reset(new netcomm_send::NetBase());
	}

	netcomm_send::NetBase* release(){
		if(token_.get()!=NULL)
			this->base_->Set(L"token",token_.release());
		if(login_time_.get()!=NULL)
			this->base_->Set(L"login_time",login_time_.release());
		if(uid_.get()!=NULL)
			this->base_->Set(L"uid",uid_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_token(const std::string& token){
		token_.reset(new base_logic::StringValue(token));
	}

	inline void set_login_time(const int64 login_time){
		login_time_.reset(new base_logic::FundamentalValue(login_time));
	}

	inline void set_uid(const int64 uid){
		uid_.reset(new base_logic::FundamentalValue(uid));
	}

private:
	scoped_ptr<netcomm_send::NetBase>               base_;
	scoped_ptr<base_logic::StringValue>             token_;
	scoped_ptr<base_logic::FundamentalValue>        login_time_;
	scoped_ptr<base_logic::FundamentalValue>        uid_;
};

class PayGetSMSChrPoint:public HeadPacket{
public:
	PayGetSMSChrPoint(){
		base_.reset(new netcomm_send::NetBase());
	}

	netcomm_send::NetBase* release(){
		if(charging_channel_.get()!=NULL)
			this->base_->Set(L"charging_channel",charging_channel_.release());
		if(tagrget_number_.get()!=NULL)
			this->base_->Set(L"tagrget_number",tagrget_number_.release());
		if(target_content_.get()!=NULL)
			this->base_->Set(L"target_content",target_content_.release());
		if(serial_number_.get()!=NULL)
			this->base_->Set(L"serial_number",serial_number_.release());
		if(remark_.get()!=NULL)
			this->base_->Set(L"remark",remark_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

public:
	inline void set_charging_channel(const int64 charging_channel){
		charging_channel_.reset(new base_logic::FundamentalValue(charging_channel));
	}

	inline void set_tagrget_number(const std::string& tagrget_number){
		tagrget_number_.reset(new base_logic::StringValue(tagrget_number));
	}

	inline void set_target_content(const std::string& target_content){
		target_content_.reset(new base_logic::StringValue(target_content));
	}

	inline void set_serial_number(const std::string& serial_number){
		serial_number_.reset(new base_logic::StringValue(serial_number));
	}

	inline void set_remark(const std::string& remark){
		remark_.reset(new base_logic::StringValue(remark));
	}
private:
	scoped_ptr<netcomm_send::NetBase>               base_;
	scoped_ptr<base_logic::FundamentalValue>        charging_channel_;
	scoped_ptr<base_logic::StringValue>             tagrget_number_;
	scoped_ptr<base_logic::StringValue>             target_content_;
	scoped_ptr<base_logic::StringValue>             serial_number_;
	scoped_ptr<base_logic::StringValue>             remark_;
};
}
#endif /* _NET_USER_COMM_HEAD_H_ */
