/*
 * user_comm_head.h
 *
 *  Created on: 2014年11月17日
 *      Author: kerry
 */

#ifndef _NET_USER_COMM_HEAD_H_
#define _NET_USER_COMM_HEAD_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{


//快速登錄
class QucikLogin:public HeadPacket{
public:
	QucikLogin(NetBase* m)
	:HeadPacket(m)
	,machine_(0){
		Init();
	}

	void  Init();

	inline void Reset(){
		HeadPacket::Reset();
		Init();
	}

	const std::string& imei() const {return this->imei_;}
	const int32 machine() const {return this->machine_;}
	const double latitude() const {return this->latitude_;}
	const double longitude() const {return this->longitude_;}


private:
	std::string imei_;
	int32       machine_;
};

//第三方登錄
class ThirdLogin:public HeadPacket{
public:
	ThirdLogin(NetBase* m)
		:HeadPacket(m)
		,machine_(0)
		,source_(0)
		,sex_(0){
		Init();
	}
	~ThirdLogin(){
		if(source_==PLAT_WX)
			if(qq_session_){delete qq_session_; qq_session_ = NULL;}
		if(source_==PLAT_QQ)
			if(wx_session_){delete wx_session_; wx_session_ = NULL;}
	}

	inline void Reset(){
		Init();
		HeadPacket::Reset();
	}

	inline void Init(){
		bool r = false;
		GETBIGINTTOINT(L"machine",machine_);
		if(!r) error_code_ = MACHINE_LACK;
		GETBIGINTTOINT(L"source",source_);
		if(!r) error_code_ = SOUCE_LACK;

		//昵称为数字
		int64 inickname = 0;
		std::string nickname;
		r = m_->GetBigInteger(L"nickname",&inickname);
		if(r){ //昵称为纯数字
			nickname_ = base::BasicUtil::StringUtil::Int64ToString(inickname);
		}else{//昵称不为纯数字
			r = m_->GetString(L"nickname",&nickname);
			if(!r) error_code_ = NICKNAME_LACK;
			//URLCODE 解码
			base::BasicUtil::UrlDecode(nickname,nickname_);
			GETBIGINTTOINT(L"sex",sex_);
		}



		//if(!r) error_code_ = SEX_LACK;

		if(source_==PLAT_WB){
			GETBIGINTTOINT(L"session",wb_session_);
			std::stringstream os;
			os<<wb_session_;
			this->session_ = os.str();
		}else if(source_==PLAT_WX){
			GETSTRINGPTR(L"session",wx_session_);
			this->session_ =  *(this->wx_session_);
		}else if(source_==PLAT_QQ){
			GETSTRINGPTR(L"session",qq_session_);
			this->session_ =  *(this->qq_session_);
		}
		if(!r) error_code_ = SESSION_LACK;

		r = m_->GetString(L"birthday",&birthday_);
		r = m_->GetString(L"location",&location_);
		//URLCODE 解码
		std::string head;
		r = m_->GetString(L"head",&head);
		if(r)
			base::BasicUtil::UrlDecode(head,head_);
		else
			head_ = head;

		r = m_->GetReal(L"latitude",&latitude_);
		r = m_->GetReal(L"longitude",&longitude_);
		r = m_->GetString(L"imei",&imei_);
	}

	const inline int32 machine() const {return this->machine_;}
	const inline std::string&  nickanme() const {return this->nickname_;}
	const inline int32 source() const {return this->source_;}
	const inline int32 sex() const {return this->sex_;}
	const inline int64 wb_seesion() const {return this->wb_session_;}
	const inline std::string& qq_session() const {return *(this->qq_session_);}
	const inline std::string& wx_session() const {return *(this->wx_session_);}
	const inline std::string& birthday() const {return this->birthday_;}
	const inline std::string& location() const {return this->location_;}
	const inline std::string& head() const {return this->head_;}
	const inline double& latitude() const {return this->latitude_;}
	const inline double& logtitude() const {return this->longitude_;}
	const inline std::string& imei() const {return this->imei_;}
	const inline std::string& session() const {return this->session_;}


private:
	int32 machine_;
	std::string nickname_;
	int32 source_;
	int32 sex_;
	union{
		int64        wb_session_;
		std::string* qq_session_;
		std::string* wx_session_;
	};
	std::string session_;
	std::string birthday_;
	std::string location_;
	std::string head_;
	std::string imei_;

};

//百度推送綁定
class BDBindPush:public HeadPacket{
public:
	BDBindPush(NetBase* m)
	:HeadPacket(m)
	,platform_(0)
	,uid_(0)
	,channel_(0)
	,bduserid_(0)
	,machine_(0)
	,appid_(0)
	,requestid_(0){
		Init();
	}

	inline void  Init(){
		bool r = false;
		r = m_->GetBigInteger(L"platform",static_cast<int64*>(&platform_));
		if(!r) error_code_ = PLATFORM_LACK;
		r = m_->GetBigInteger(L"uid",static_cast<int64*>(&uid_));
		if(!r) error_code_ = UID_LACK;
		r = m_->GetString(L"token",&token_);
		if(!r) error_code_ = TOKEN_LACK;
		r = m_->GetBigInteger(L"channel",static_cast<int64*>(&channel_));
		if(!r) error_code_ = BD_CHANNEL_LACK;
		r = m_->GetBigInteger(L"userid",static_cast<int64*>(&bduserid_));
		if(!r) error_code_ = BD_USERID_LACK;
		r = m_->GetString(L"pkg_name",&pkg_name_);
		if(!r) error_code_ = PKG_NAME_LACK;
		r = m_->GetString(L"tag",&tag_);
		if(!r) error_code_ = TAG_LACK;
		GETBIGINTTOINT(L"machine",machine_);
		if(!r) error_code_ = MACHINE_LACK;
		GETBIGINTTOINT(L"appid",appid_);
		if(!r) error_code_ = APPID_LACK;
		GETBIGINTTOINT(L"requestid",requestid_);
		if(!r) error_code_ = REQUEST_LACK;
	}

	const inline int64 platform() const {return this->platform_;}
	const inline int64 uid() const {return this->uid_;}
	const inline std::string& token() const {return this->token_;}
	const inline int64 channel() const {return this->channel_;}
	const inline int64 bduserid() const {return this->bduserid_;}
	const inline std::string& pkg_name() const {return this->pkg_name_;}
	const inline std::string& tag() const {return this->tag_;}
	const inline int64 appid() const {return this->appid_;}
	const inline int64 request() const {return this->requestid_;}
	const inline int32 machine() const {return this->machine_;}

private:
	int64  platform_;
	int64  uid_;
	std::string  token_;
	int64 channel_;
	int64 bduserid_;
	std::string pkg_name_;
	std::string tag_;
	int32       machine_;
	int64       appid_;
	int64       requestid_;
};


}


namespace netcomm_send{



class Login:public HeadPacket{
public:
	Login(){
		login_.reset(new netcomm_send::NetBase());
		userinfo_login_.reset(new netcomm_send::NetBase());
	}

	netcomm_send::NetBase* release(){
		if(userinfo_login_->size()>0)
			login_->Set("userinfo",userinfo_login_.release());
		head_->Set("result",login_.release());
		this->set_flag(0);
		this->set_msg("");
		this->set_status(1);
		return head_.release();
	}

public:
	inline void set_userinfo_uid(const int64 uid){userinfo_login_->SetBigInteger("uid",uid);}
	inline void set_userinfo_token(const std::string& token){userinfo_login_->SetString("token",token);}
	inline void set_userinfo_address(const std::string& address) {userinfo_login_->SetString("address",address);}
	inline void set_userinfo_nickname(const std::string& nickname) {userinfo_login_->SetString("nickname",nickname);}
	inline void set_userinfo_source(const int32 source){userinfo_login_->SetInteger("source",source);}
	inline void set_useromfo_head(const std::string& head){userinfo_login_->SetString("head",head);}
private:
	scoped_ptr<netcomm_send::NetBase> login_;
	scoped_ptr<netcomm_send::NetBase> userinfo_login_;
};

}
#endif /* _NET_USER_COMM_HEAD_H_ */
