/*
 * comm_head.h
 *
 *  Created on: 2014年11月17日
 *      Author: kerry
 */

#ifndef _NET_COMM_HEAD_H_
#define _NET_COMM_HEAD_H_

#include "net/operator_code.h"
#include "net/error_comm.h"
#include "basic/basictypes.h"
#include "basic/basic_util.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
enum platcode{
	PLAT_WB = 1,
	PLAT_WX = 2,
	PLAT_QQ = 3,
};

#define GETBIGINTTOINT(TYPE,VALUE) \
	int64 VALUE##value;\
	r = m_->GetBigInteger(TYPE,&VALUE##value);\
	VALUE = VALUE##value;\

#define GETSTRINGPTR(TYPE,VALUE)\
	VALUE = new std::string();\
	r = m_->GetString(TYPE,VALUE);\


/*******接收相关************/
namespace netcomm_recv{

class NetBase:public base_logic::DictionaryValue{
public:
	//virtual bool Deserialize(const std::string& rest_str);
};

class HeadPacket{
public:
	HeadPacket(NetBase* m)
		:m_(m)
		,type_(0)
		,error_code_(0)
		,latitude_(0)
		,longitude_(0){
		Reset();
	}

	const inline int32 GetType() const {return this->type_;}

	const inline std::string& remote_addr() const {return this->remote_addr_;}

	const inline int32  GetResult() const {return this->error_code_;}



	const inline double latitude() const {return this->latitude_;}

	const inline double longitude() const {return this->longitude_;}

	void set_latitude(double latitude){m_->SetReal("latitude",latitude);}

	void set_longitude(double longitude){m_->SetReal("longitude",longitude);}



	/*inline void Init(){

	}*/

	inline  void Reset() {
		bool r = false;
		GETBIGINTTOINT(L"type",type_);
		if(!r)
			error_code_ = LOGIN_TYPE_LACK;
		r = m_->GetString(L"remote_addr",&remote_addr_);
		r = m_->GetReal(L"latitude",&latitude_);
		r = m_->GetReal(L"longitude",&longitude_);
	}

public:
	int32  type_;
	std::string remote_addr_;
public:
	NetBase* m_;
	int32       error_code_;
	double      latitude_;
	double      longitude_;
};

class LoginHeadPacket:public HeadPacket{
public:
	LoginHeadPacket(NetBase* m)
	 :HeadPacket(m)
	 ,uid_(0){
		Init();
	}

	inline void Init(){
		bool r = false;
		GETBIGINTTOINT(L"uid",uid_);
		if(!r) error_code_ = UID_LACK;
		r = m_->GetString(L"token",&token_);
		if(!r) error_code_ = TOKEN_LACK;
	}

	inline void Reset(){
		HeadPacket::Reset();
		Init();
	}

	const std::string& token() const {return this->token_;}
	const int64 uid() const {return this->uid_;}
public:
	int64 uid_;
	std::string token_;
};


}
/*******发送相关************/
namespace netcomm_send{

class NetBase:public base_logic::DictionaryValue{
public:
	//virtual bool Deserialize(const std::string& rest_str);
};

class HeadPacket{
public:
	HeadPacket(){head_.reset(new netcomm_send::NetBase());}
public:
	void set_msg(const std::string& msg){head_->SetString("msg",msg);}
	void set_flag(const int32 flag) {head_->SetInteger("flag",flag);}
	void set_status(const int32 status) {head_->SetInteger("status",status);}
public:
	virtual void GetJsonSerialize(std::string* json);
	virtual inline netcomm_send::NetBase* release(){head_.release();};
public:
	scoped_ptr<netcomm_send::NetBase> head_;
};

}



#endif /* COMM_HEAD_H_ */
