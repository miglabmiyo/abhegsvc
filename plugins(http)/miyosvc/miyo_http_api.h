/*
 * miyo_http_api.h
 *
 *  Created on: 2015年5月9日
 *      Author: pro
 */

#ifndef MIYO_HTTP_API_H_

#include "miyo_basic_info.h"
#include "http/http_api.h"

namespace miyosvc_logic{

class MiyoHttpAPI{
public:
	MiyoHttpAPI(){}
	virtual ~MiyoHttpAPI(){}
public:
	static bool ThirdLogin(base_logic::DictionaryValue* value,miyosvc_logic::UserInfo& userinfo);

private:
	static base_logic::DictionaryValue*  ResolveMiyoJson(std::string& response);
};


}





#endif /* MIYO_HTTP_API_H_ */
