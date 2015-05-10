/*
 * miyo_info.h
 *
 *  Created on: 2015年5月7日
 *      Author: pro
 */

#ifndef MIYO_BASIC_INFO_H_
#define MIYO_BASIC_INFO_H_

#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/basictypes.h"
#include "logic/logic_infos.h"
#include <string>
#include <list>
namespace miyosvc_logic{

class UserInfo:public base_logic::UserInfo{
public:
	explicit UserInfo();
	UserInfo(const UserInfo& userinfo);
	UserInfo& operator = (const UserInfo& userinfo);

	void set_lastest_time(){data_->latest_time_ = time(NULL);}
	const time_t lastest_time() const {return data_->latest_time_;}

	void set_miyo_id(const int64 miyo_id){data_->miyo_id_ = miyo_id;}
	const int64 miyo_id() const {return data_->miyo_id_;}

	void set_token(const std::string& token){data_->token_ = token;}
	const std::string& token() const {return data_->token_;}

	bool JsonSerialization(std::string& json);

private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,latest_time_(0)
			,miyo_id_(0){}

		void AddRef(){refcount_++;}
		void Release(){if(!--refcount_)delete this;}
	public:
		int64       miyo_id_;
		std::string  token_;
		time_t      latest_time_;
	private:
		int         refcount_;
	};
	Data*                 data_;
	//base_logic::UserInfo  userinfo_;
};

}

#endif /* MIYO_INFO_H_ */
