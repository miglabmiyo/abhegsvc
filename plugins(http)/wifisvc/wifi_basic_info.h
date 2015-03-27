/*
 * wifi_basic_info.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */

#ifndef WIFI_BASIC_INFO_H_
#define WIFI_BASIC_INFO_H_
#include "basic/basictypes.h"
#include <string>
#include <list>
namespace wifisvc_logic{

class ShareUser{
public:
	explicit ShareUser();

	ShareUser(const ShareUser& share);
	ShareUser& operator =(const ShareUser& share);

	base_logic::DictionaryValue* Release();

private:
	class Data{
	public:
		Data()
		:refcount_(1)
		,uid_(0){}
	public:
		int64             uid_;
		std::string       nickname_;
		std::string       head_;
	    std::string       share_time_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};

	Data*  data_;
};
class WifiInfo{
public:
	explicit WifiInfo();

	WifiInfo(const WifiInfo& wifi);
	WifiInfo& operator = (const WifiInfo& wifi);

	base_logic::DictionaryValue* Release();

	void set_id(const int64 id){ data_->id_ = id;}
	void set_type(const int32 type) { data_->type_ = type;}
	void set_distance(const double distance) {data_->distance_ = distance;}
	void set_latitude(const double latitude) {data_->latitude_ = latitude;}
	void set_longitude(const double longitude) {data_->longitude_ = longitude;}
	void set_ssid(const std::string& ssid) {data_->ssid_ = ssid;}
	void set_apid(const std::string& apid) {data_->apid_ = apid;}
	void set_pwd(const std::string& pwd) {data_->pwd_ = pwd;}

	const int64 id() const {return data_->id_;}
	const int32 type() const {return data_->type_;}
	const double distance() const {return data_->distance_;}
	const double latitude() const {return data_->latitude_;}
	const double longitude() const {return data_->longitude_;}
	const std::string& ssid() const {return data_->ssid_;}
	const std::string& apid() const {return data_->apid_;}
	const std::string& pwd() const {return data_->pwd_;}


private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,id_(0)
			,type_(0)
			,distance_(0.0)
			,latitude_(0.0)
			,longitude_(0.0){}

	public:
		int64          id_;
		int32          type_;
		double         distance_;
		double         latitude_;
		double         longitude_;
		std::string    ssid_;
		std::string    apid_;
		std::string    pwd_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};

	Data*              data_;
};



}



#endif /* USER_BASIC_INFO_CC_ */



