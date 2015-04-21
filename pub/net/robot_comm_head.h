/*
 * robot_comm_head.h
 *
 *  Created on: 2015年2月23日
 *      Author: pro
 */

#ifndef ROBOT_COMM_HEAD_H_
#define ROBOT_COMM_HEAD_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>


namespace netcomm_recv{

class GetSpiderPhoneNumber:public HeadPacket{
public:
	GetSpiderPhoneNumber(NetBase* m)
	:HeadPacket(m){
	}
};

class GetMovieUnit:public HeadPacket{
public:
	GetMovieUnit(NetBase* m)
	:HeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;

		r = m_->GetBigInteger(L"from",&from_);
		if(!r) from_ = 0;
		r = m_->GetBigInteger(L"count",&count_);
		if(!r) count_ = 10;
	}

	const int64 from() const {return this->from_;}

	const int64 count() const {return this->count_;}

private:
	int64 from_;
	int64 count_;
};

class SumbitUnitMovie:public HeadPacket{
public:
	SumbitUnitMovie(NetBase* m)
	:HeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
		r = m_->GetString(L"unit",&unit_);
		if(!r) error_code_ = MOVIE_CONTENT_LACK;
	}

	const std::string& unit() const {return this->unit_;}
private:
	std::string unit_;
};

}

namespace netcomm_send{

class GetUnit:public HeadPacket{
public:
	GetUnit(){
		base_.reset(new netcomm_send::NetBase());
		list_.reset(new base_logic::ListValue());
	}

	inline void set_unit(base_logic::DictionaryValue* unit){
		list_->Append(unit);
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
class GetSpiderPhoneNumber:public HeadPacket{
public:
	GetSpiderPhoneNumber(){
		base_.reset(new netcomm_send::NetBase());
		phone_list_.reset(new base_logic::ListValue());
	}

	inline void set_phone(std::string& phone){
		phone_list_->Append(base_logic::Value::CreateStringValue(phone));
	}

	netcomm_send::NetBase* release(){
		if(!phone_list_->empty())
			this->base_->Set(L"list",phone_list_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             phone_list_;
};


}



#endif /* ROBOT_COMM_HEAD_H_ */
