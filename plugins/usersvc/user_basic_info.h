/*
 * user_basic_info.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */

#ifndef USER_BASIC_INFO_H_
#define USER_BASIC_INFO_H_
#include "basic/basictypes.h"
#include <string>
#include <list>
namespace usersvc_logic{


class UserInfo{
public:
	explicit UserInfo();

	UserInfo(const UserInfo& userinfo);
	UserInfo& operator = (const UserInfo& userinfo);

	void set_uid(const int64 uid){data_->uid_ = uid;}
	void set_sex(const int32 sex){data_->sex_ = sex;}
	void set_machine(const int32 machine){data_->machine_ = machine;}
	void set_logintime(const int64 logintime) {data_->logintime_ = logintime;}
	void set_type(const int32 type) {data_->type_ = type;}
	void set_imei(const std::string& imei){data_->imei_ = imei;}
	void set_nickname(const std::string& nickname) {data_->nickname_ = nickname;}
	void set_city(const std::string& city) {data_->city_ = city;}
	void set_head(const std::string& head) {data_->head_ = head;}
	void set_session(const std::string& session) {data_->session_ = session;}
	void set_birthday(const std::string& birthday){data_->birthday_ = birthday;}
	const int64 uid() {return data_->uid_;}
	const int32 sex() {return data_->sex_;}
	const int32 machine() {return data_->machine_;}
	const int64 logintime() {return data_->logintime_;}
	const int32 type() {return data_->type_;}
	const std::string& imei() {return data_->imei_;}
	const std::string& nickname() {return data_->nickname_;}
	const std::string& city() {return data_->city_;}
	const std::string& head() {return data_->head_;}
	const std::string& session(){return data_->session_;}
	const std::string& birthday(){return data_->birthday_;}


private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,uid_(0)
			,sex_(0)
			,machine_(0)
			,logintime_(0)
			,type_(0){}
	public:
		int64 uid_;
		int32 sex_;
		int32 machine_;
		int64 logintime_;
		int32 type_;
		std::string session_;
		std::string imei_;
		std::string nickname_;
		std::string city_;
		std::string head_;
		std::string birthday_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};
	Data*       data_;

};
}



#endif /* USER_BASIC_INFO_CC_ */



