/*
 * beacon_comm_head.h
 *
 *  Created on: 2015年4月22日
 *      Author: pro
 */

#ifndef BEACON_COMM_HEAD_H_
#define BEACON_COMM_HEAD_H_


#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

class SharkBeacon:public LoginHeadPacket{
public:
	SharkBeacon(NetBase* m)
	:LoginHeadPacket(m){
		bool r = false;
		r = m_->GetString(L"uuid",&uuid_);
		if(!r) error_code_ = BEACON_UUID_LACK;
		r = m_->GetString(L"mac",&mac_);
		if(!r) error_code_ = BEACON_MAC_LACK;
	}

	const std::string& uuid() const {return this->uuid_;}
	const std::string& mac() const {return this->mac_;}

private:
	std::string  uuid_;
	std::string  mac_;
};
}

namespace netcomm_send{
//摇一摇
class SharkBeacon:public HeadPacket{
public:
	SharkBeacon(){
		base_.reset(new netcomm_send::NetBase());
	}
	~SharkBeacon(){}

	inline void SetBeaconMerChant(base_logic::DictionaryValue* info){
		this->info_.reset(info);
	}

	netcomm_send::NetBase* release(){
		if(!info_->empty())
			this->base_->Set(L"info",info_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       info_;
};

}


#endif /* BEACON_COMM_HEAD_H_ */
