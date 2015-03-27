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

}

namespace netcomm_send{
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
