/*
 * pay_basic_info.h
 *
 *  Created on: 2015年3月12日
 *      Author: pro
 */

#ifndef PAY_BASIC_INFO_H_
#define PAY_BASIC_INFO_H_
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/basictypes.h"
#include <string>
#include <list>

namespace paysvc_logic{

class PayUserInfo{
public:
	explicit PayUserInfo();
	PayUserInfo(const PayUserInfo& pay);

	PayUserInfo& operator = (const PayUserInfo& pay);

	const int64 uid() const {return data_->uid_;}
	const std::string& imei() const {return data_->imei_;}
	const std::string& sim() const {return data_->sim_;}

	void set_uid(const int64 uid){data_->uid_ = uid;}
	void set_imei(const std::string& imei){data_->imei_ = imei;}
	void set_sim(const std::string& sim) {data_->sim_ = sim;}
	void set_imei(const char* imei){data_->imei_ = imei;}
	void set_sim(const char* sim){data_->sim_ = sim;}

private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,uid_(0){}
	public:
		int64          uid_;
		std::string    imei_;
		std::string   sim_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_) delete this;}
	private:
		int refcount_;
	};
	Data*       data_;
};

class ChrPoint{
public:
	explicit ChrPoint();
	ChrPoint(const ChrPoint& point);

	ChrPoint& operator = (const ChrPoint& point);

	const int64 id() const {return data_->id_;}
	const int32 type() const {return data_->type_;}
	const int32 flag() const {return data_->flag_;}
	const int32 money() const {return data_->money_;}
	const std::string& phone() const {return data_->phone_;}
	const std::string& content() const {return data_->content_;}
	const std::string remark() const {return data_->remark_;}

	void set_id(const int64 id){data_->id_ = id;}
	void set_type(const int32 type){data_->type_ = type;}
	void set_flag(const int32 flag) {data_->flag_ = flag;}
	void set_money(const int32 money) {data_->money_ = money;}
	void set_phone(const std::string& phone){data_->phone_ = phone;}
	void set_content(const std::string& content){data_->content_ = content;}
	void set_remark(const std::string& remark){data_->remark_ = remark;}
private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,id_(0)
			,type_(0)
			,flag_(0)
			,money_(0){}
	public:
		int64          id_;
		int32          type_;
		int32          flag_;
		int32          money_;
		std::string    phone_;
		std::string    content_;
		std::string    remark_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_) delete this;}
	private:
		int refcount_;
	};
	Data*       data_;
};
}


#endif /* PAY_BASIC_INFO_H_ */
