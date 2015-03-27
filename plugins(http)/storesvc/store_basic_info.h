/*
 * stroe_basic_info.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */

#ifndef STORE_BASIC_INFO_H_
#define STORE_BASIC_INFO_H_
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/basictypes.h"
#include <string>
#include <list>
namespace storesvc_logic{


class GameStrategy{
public:
	explicit GameStrategy();
	GameStrategy(const GameStrategy& strategy);

	GameStrategy& operator = (const GameStrategy& strategy);

	base_logic::DictionaryValue* Release();

	const int64 id() const {return data_->id_;}
	const int64 gameid() const {return data_->gameid_;}
	const std::string& name() const {return data_->name_;}
	const std::string& details() const {return data_->details_;}
	const std::string& address() const {return data_->address_;}

	void set_id(const int64 id){data_->id_ = id;}
	void set_gameid(const int64 gameid){data_->gameid_ = gameid;}
	void set_name(const std::string& name) {data_->name_ = name;}
	void set_details(const std::string& details) {data_->details_ = details;}
	void set_address(const std::string& address) {data_->address_ = address;}

private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,id_(0)
			,gameid_(0){}
	public:
		int64           id_;
		int64           gameid_;
		std::string     name_;
		std::string     address_;
		std::string     details_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_) delete this;}
	private:
		int refcount_;
	};
	Data*       data_;
};


/*
class AppSummaryInfo:public base_logic::AppInfos{
public:
	explicit AppSummaryInfo();
	AppSummaryInfo(const AppSummaryInfo& appsummary);

	AppSummaryInfo& operator = (const AppSummaryInfo& appsummary);

	base_logic::DictionaryValue* Release();

};
*/

}



#endif /* STORE_BASIC_INFO_H_ */



