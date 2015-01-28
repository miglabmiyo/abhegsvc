/*
 * store_cmm_head.h
 *
 *  Created on: 2015年1月25日
 *      Author: kerry
 */

#ifndef _NET_STORE_CMM_HEAD_H_
#define _NET_STORE_CMM_HEAD_H_


#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

//用于商场 游戏 书城 详情
class AppSummary:public LoginHeadPacket{
public:
	AppSummary(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"appid",appid_);
		if(!r) error_code_ = APPID_LACK;
	}

	const int64 appid() const {return this->appid_;}
private:
	int64       appid_;
};

typedef AppSummary  LikePraise;

//获取地址
class WantAppUrl:public LoginHeadPacket{
public:
	WantAppUrl(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"appid",appid_);
		if(!r) error_code_ = APPID_LACK;
		GETBIGINTTOINT(L"machine",machine_);
		if(!r)machine_ = 0;
	}

	const int64 appid() const {return this->appid_;}

	const int32 machine() const {return this->machine_;}
private:
	int64       appid_;
	int32       machine_;
};
}

namespace netcomm_send{

class AppSummary:public HeadPacket{
public:
	AppSummary(){
		base_.reset(new netcomm_send::NetBase());
		pic_.reset(new base_logic::ListValue());
		like_.reset(new base_logic::ListValue());
		intro_.reset(new base_logic::DictionaryValue());
		islike_.reset(new base_logic::FundamentalValue(0));
	}

	netcomm_send::NetBase* release(){
		if(!pic_->empty())
			this->intro_->Set(L"pic",pic_.release());
		if(!like_->empty())
			this->base_->Set(L"like",like_.release());
		if(!intro_->empty())
			this->base_->Set(L"intro",intro_.release());
		this->base_->Set(L"islike",islike_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}


	inline void set_intro(base_logic::DictionaryValue* app){
		intro_.reset(app);
	}

	inline void set_like(base_logic::DictionaryValue* app){
		like_->Append(app);
	}

	inline void set_islike(const int32 islike){
		islike_.reset(new base_logic::FundamentalValue(islike));
	}

	inline void set_pic(const std::string& pic){
		pic_->Append(base_logic::Value::CreateStringValue(pic));
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       intro_;
	scoped_ptr<base_logic::FundamentalValue>      islike_;
	scoped_ptr<base_logic::ListValue>             like_;
	scoped_ptr<base_logic::ListValue>             pic_;
};

//下载地址
class WantAppUrl:public HeadPacket{
public:
	WantAppUrl(){
		base_.reset(new netcomm_send::NetBase());
		basic_.reset(new base_logic::DictionaryValue());
	}

	netcomm_send::NetBase* release(){
		if(!basic_->empty())
			this->base_->Set(L"basic",basic_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_url(const std::string& url){
		basic_->SetString(L"url",url);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       basic_;
};

}


#endif /* STORE_CMM_HEAD_H_ */
