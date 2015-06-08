/*
 * gamebox_comm_head.h
 *
 *  Created on: 2015年6月1日
 *      Author: Administrator
 */

#ifndef PUB_NET_GAMEBOX_COMM_HEAD_H_
#define PUB_NET_GAMEBOX_COMM_HEAD_H_


#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include "basic/basic_util.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

class CheckGame:public LoginHeadPacket{
public:
	CheckGame(NetBase* m)
	:LoginHeadPacket(m){
		bool r = false;
		std::string content;
		r = m_->GetString(L"content",&content);
		if(!r) error_code_ = NULL_DATA;
		r = base::BasicUtil::UrlDecode(content,content_);
		if(!r) content_ = content;
	}

	const std::string& content() const {return this->content_;}
private:
	std::string content_;
};

}



namespace netcomm_send{
class CheckGame:public HeadPacket{
public:
	CheckGame(){
		base_.reset(new netcomm_send::NetBase());
		own_app_.reset(new base_logic::ListValue());
		recomm_app_.reset(new base_logic::ListValue());
	}

	inline void set_own_app(base_logic::DictionaryValue* app){
		own_app_->Append(app);
	}

	inline void set_recomm_app(base_logic::DictionaryValue* app){
		recomm_app_->Append(app);

	}

	netcomm_send::NetBase* release(){

		if(!own_app_->empty())
			this->base_->Set(L"own",own_app_.release());
		if(!recomm_app_->empty())
			this->base_->Set(L"recomm",recomm_app_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             own_app_;
	scoped_ptr<base_logic::ListValue>             recomm_app_;
};

class SharkGame:public HeadPacket{
public:
	SharkGame(){
		base_.reset(new netcomm_send::NetBase());
		list_.reset(new base_logic::ListValue());
	}

	inline void set_app(base_logic::DictionaryValue* app){
		list_->Append(app);
	}

	netcomm_send::NetBase* release(){

		if(!list_->empty())
			this->base_->Set(L"list",list_.release());


		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             list_;
};

}
#endif /* PUB_NET_GAMEBOX_COMM_HEAD_H_ */
