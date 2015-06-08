/*
 * gamebox_comm_head.h
 *
 *  Created on: 2015年6月1日
 *      Author: Administrator
 */

#ifndef PUB_NET_GAMEBOX_COMM_HEAD_H_
#define PUB_NET_GAMEBOX_COMM_HEAD_H_


#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

class CheckGame:public LoginHeadPacket{
public:
	CheckGame(NetBase* m)
	:LoginHeadPacket(m){
		bool r = false;
		r = m_->GetString(L"content",&content);
		if(!r) error_code_ = NULL_DATA;
	}

	const std::string& content() const {return this->content_;}
private:
	std::string content_;
};

}
#endif /* PUB_NET_GAMEBOX_COMM_HEAD_H_ */
