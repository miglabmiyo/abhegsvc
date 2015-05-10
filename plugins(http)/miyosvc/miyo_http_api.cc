/*
 * miyo_http_api.cc

 *
 *  Created on: 2015年5月9日
 *      Author: pro
 */

#include "miyo_http_api.h"
#include "logic/http_macro.h"

namespace miyosvc_logic{


bool MiyoHttpAPI::ThirdLogin(base_logic::DictionaryValue* value,miyosvc_logic::UserInfo& userinfo){
	bool r = false;
	std::string url;
	std::string result;
	base_logic::DictionaryValue* dict_result;
	base_logic::DictionaryValue* usr;
	url = std::string(MIYO_HOST)+std::string(MIYO_THIRD_LOGIN);
	base_http::HttpAPI::RequestPostMethod(url,value,result);
	if(result.empty())
		return false;
	//解析json
	dict_result = ResolveMiyoJson(result);
	if(dict_result==NULL)
		return false;
	r = dict_result->GetDictionary(L"userinfo",&usr);
	if(!r)
		return false;

	int64        type;
	int64        uid;
	int64        sex;
	int64        machine;
	std::string  birthday;
	std::string  city;
	std::string  head;
	std::string  nickname;
	std::string  session;
	std::string  token;
	if(usr->GetBigInteger(L"type",&type))
		userinfo.set_type(type);
	if(usr->GetBigInteger(L"uid",&uid)){
		userinfo.set_uid(uid);
		userinfo.set_miyo_id(uid);
	}
	if(usr->GetBigInteger(L"sex",&sex))
		userinfo.set_sex(sex);
	if(usr->GetBigInteger(L"machine",&machine))
		userinfo.set_machine(machine);
	if(usr->GetString(L"birthday",&birthday))
		userinfo.set_birthday(birthday);
	if(usr->GetString(L"city",&city))
		userinfo.set_city(city);
	if(usr->GetString(L"head",&head))
		userinfo.set_head(head);
	if(usr->GetString(L"nickname",&nickname))
		userinfo.set_nickname(nickname);
	if(usr->GetString(L"session",&session))
		userinfo.set_session(session);
	if(usr->GetString(L"token",&token))
		userinfo.set_token(token);
	userinfo.set_lastest_time();
	return true;
}

bool MiyoHttpAPI::GainCollectMusicList(base_logic::DictionaryValue* value,std::string& content){
	std::string url;
	url = std::string(MIYO_HOST)+std::string(MIYO_GAIN_COLLECT);
	base_http::HttpAPI::RequestPostMethod(url,value,content);
	if(content.empty())
		return false;
	return true;
}
bool MiyoHttpAPI::GainDimensionMusicList(base_logic::DictionaryValue* value,std::string& content){
	std::string url;
	url = std::string(MIYO_HOST)+std::string(MIYO_GAIN_DIMENSION);
	base_http::HttpAPI::RequestPostMethod(url,value,content);
	if(content.empty())
		return false;
	return true;
}

bool MiyoHttpAPI::SetCollectMusic(base_logic::DictionaryValue* value,std::string& content){
	std::string url;
	url = std::string(MIYO_HOST)+std::string(MIYO_SET_COLLECT);
	base_http::HttpAPI::RequestPostMethod(url,value,content);
	if(content.empty())
		return false;
	return true;
}

bool MiyoHttpAPI::DelCollectMusic(base_logic::DictionaryValue* value,std::string& content){
	std::string url;
	url = std::string(MIYO_HOST)+std::string(MIYO_DEL_COLLECT);
	base_http::HttpAPI::RequestPostMethod(url,value,content);
	if(content.empty())
		return false;
	return true;
}

bool MiyoHttpAPI::SetHateMusic(base_logic::DictionaryValue* value,std::string& content){
	std::string url;
	url = std::string(MIYO_HOST)+std::string(MIYO_DEL_HATE);
	base_http::HttpAPI::RequestPostMethod(url,value,content);
	if(content.empty())
		return false;
	return true;
}

base_logic::DictionaryValue*  MiyoHttpAPI::ResolveMiyoJson(std::string& response){
	bool r =false;
	base_logic::DictionaryValue* dict;
	base_logic::DictionaryValue* result;
	int64 status = -1;
	dict = (base_logic::DictionaryValue*)(base_http::HttpAPI::ResponseJsonSerialization(&response));
	if(dict==NULL)
		return NULL;
	r = dict->GetBigInteger(L"status",&status);
	if(status==-1)
		return NULL;
	r = dict->GetDictionary(L"result",&result);
	return result;
}



}




