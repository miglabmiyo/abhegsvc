/*
 * beacon_basic_info.h
 *
 *  Created on: 2015年4月22日
 *      Author: pro
 */

#ifndef BEACON_BASIC_INFO_H_
#define BEACON_BASIC_INFO_H_
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/basictypes.h"
#include <string>
#include <list>

namespace beaconsvc_logic{

class BeaconInfo{
public:
	explicit BeaconInfo();

	BeaconInfo(const BeaconInfo& beacon);
	BeaconInfo& operator = (const BeaconInfo& beacon);


	const void set_id(const int64 id){data_->id_ = id;}
	const void set_major(const int32 major){data_->major_ = major;}
	const void set_minor(const int32 minor){data_->minor_ = minor;}
	const void set_uuid(const std::string& uuid){data_->uuid_ = uuid;}
	const void set_name(const std::string& name){data_->name_ = name;}
	const void set_mac(const std::string& mac){data_->mac_ = mac;}


	const int64 id() const {return data_->id_;}
	const int32 major() const {return data_->major_;}
	const int32 minor() const {return data_->minor_;}
	const std::string& uuid() const {return data_->uuid_;}
	const std::string& name() const {return data_->name_;}
	const std::string& mac() const {return data_->mac_;}

private:
	class Data{
	public:
		Data()
		:refcount_(1)
		,major_(0)
		,minor_(0)
		,id_(0){}
	public:
		int64          id_;
		int32          major_;
		int32          minor_;
		std::string    uuid_;
		std::string    name_;
		std::string    mac_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int            refcount_;
	};

	Data*              data_;
};

class BeaconMerchant{
public:
	explicit BeaconMerchant();

	BeaconMerchant(const BeaconMerchant& merchant);
	BeaconMerchant& operator = (const BeaconMerchant& merchant);


	base_logic::DictionaryValue* Release();

	const void set_id(const int64 id){data_->id_ = id;}
	const void set_bid(const int64 bid){data_->bid_ = bid;}
	const void set_name(const std::string& name){data_->name_ = name;}
	const void set_intor(const std::string& intor){data_->intor_ = intor;}
	const void set_pic(const std::string& pic){data_->pic_ = pic;}
	const void set_url(const std::string& url){data_->url_ = url;}

	const int64 id() const {return data_->id_;}
	const int64 bid() const {return data_->bid_;}
	const std::string& name() const {return data_->name_;}
	const std::string& intor() const {return data_->intor_;}
	const std::string& pic() const {return data_->pic_;}
	const std::string& url() const {return data_->url_;}
private:
	class Data{
	public:
		Data()
		:refcount_(1)
		,id_(0)
		,bid_(0){

		}
	public:
		int64            id_;
		int64            bid_;
		std::string      name_;
		std::string      intor_;
		std::string      pic_;
		std::string      url_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int            refcount_;
	};

	Data*  data_;
};
}


#endif /* BEACON_BASIC_INFO_H_ */
