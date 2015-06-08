/*
 * parser_wdj_engine.cc
 *
 *  Created on: 2015年6月4日
 *      Author: pro
 */
#include"parser_wdj_engine.h"
#include "basic/basic_util.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{

ParserWDJEngine::ParserWDJEngine(){

}

ParserWDJEngine::~ParserWDJEngine(){

}

bool ParserWDJEngine::PaserCompleteAppInfo(base_logic::Value* value,base_logic::AppInfos& info){
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)(value);
	bool r = false;
	std::string title;
	std::string app_type;
	std::string logo;
	std::string introduction;
	std::string andorid_url;
	std::string developer_name;
	std::string decription;
	std::string packet_name;
	int64 down_count = 0;
	int64 like_count = 0;
	base_logic::ListValue* apks_list = NULL;
	base_logic::DictionaryValue* developer = NULL;
	base_logic::DictionaryValue* screen = NULL;
	r =  dict->GetString(L"title",&title);
	if(r)
		info.set_name(title);

	r = dict->GetString(L"appType",&app_type);
	if(r){
		if(app_type=="APP")
			info.set_type(1000);
		else
			info.set_type(2000);
	}
	base_logic::DictionaryValue* icons_dict = NULL;
	r = dict->GetDictionary(L"icons",&icons_dict);
	if(r){
		//取256
		r = icons_dict->GetString(L"px256",&logo);
		if(r)
			info.set_logo(logo);
	}
	r = dict->GetBigInteger(L"downloadCount",&down_count);
	if(r)
		info.set_down(down_count);

	r = dict->GetString(L"snippet",&introduction);
	if(r){
		ParserCompleteContent(introduction);
		info.set_introduction(introduction);
	}

	r = dict->GetBigInteger(L"likesCount",&like_count);
	if(r)
		info.set_like(like_count);

	r = dict->GetList(L"apks",&apks_list);
	if(r)
		ParserCompleteApkUrl(apks_list,info);

	r = dict->GetDictionary(L"developer",&developer);
	if(r){
		r = developer->GetString(L"name",&developer_name);
		if(r)
			info.set_developer_name(developer_name);
	}

	r = dict->GetString(L"description",&decription);
	if(r){
		ParserCompleteContent(decription);
		info.set_summary(decription);
	}
	r = dict->GetString(L"packageName",&packet_name);
	if(r)
		info.set_packetname(packet_name);
	//图片
	r = dict->GetDictionary(L"screenshots",&screen);
	if(r)
		ParserCompleteScreenshots(screen,info);
	return true;
}

bool ParserWDJEngine::ParserCompleteScreenshots(base_logic::DictionaryValue* screen,base_logic::AppInfos& info){
	base_logic::ListValue* normal = NULL;
	bool r = false;
	r = screen->GetList(L"normal",&normal);
	if(!r)
		return r;
	while(normal->GetSize()>0){
		base_logic::Value* value = NULL;
		r = normal->Remove(0,&value);
		if(!r)
			continue;
		std::string pic;
		r = value->GetAsString(&pic);
		if(!r)
			continue;
		info.set_summary_pic(pic);
	}

	return true;
}

bool ParserWDJEngine::ParserCompleteApkUrl(base_logic::ListValue* apks_list,base_logic::AppInfos& info){
	bool r = false;
	std::string android_url;
	std::string version_name;
	std::string sub_str;
	std::string error_str;
	int error_code = 0;
	int64 bytes = 0;
	do{
		if(apks_list->GetSize()>0){
			base_logic::Value* index_value = NULL;
			r = apks_list->Get(0,&index_value);
			if(!r)
				break;
			base_logic::DictionaryValue* dict_index_value = (base_logic::DictionaryValue*)(index_value);

			r = dict_index_value->GetBigInteger(L"bytes",&bytes);
			if(r){
				double base_byte = 1024.00;
				double app_bytes = bytes/(base_byte*base_byte);
				info.set_size(app_bytes);
			}
			r = dict_index_value->GetString(L"versionName",&version_name);
			if(r)
				info.set_version(version_name);
			//下载地址
			base_logic::ListValue* down_url_list = NULL;
			r = dict_index_value->GetList(L"downloadUrls",&down_url_list);
			if(!r)
				break;
			if(down_url_list->GetSize()>0){
				base_logic::DictionaryValue* down_unit = NULL;
				r = down_url_list->GetDictionary(0,&down_unit);
				if(!r)
					break;
				r = down_unit->GetString(L"url",&android_url);
				if(r){
					std::string real_android_url;
					std::string query;
					std::string decode_real_androd_url;
					size_t pos = android_url.find("?");
					query = android_url.substr(pos+1,android_url.length());
					scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP,&query));
					base_logic::DictionaryValue*  value = (base_logic::DictionaryValue*)(serializer.get()->Deserialize(&error_code,&error_str));
					if(value==NULL){
						info.set_android_url(android_url);
						break;
					}
					r = value->GetString(L"url",&real_android_url);
					if(!r){
						info.set_android_url(android_url);
						break;
					}

					r = base::BasicUtil::UrlDecode(real_android_url,decode_real_androd_url);
					if(!r)
						info.set_android_url(real_android_url);
					else
						info.set_android_url(decode_real_androd_url);
				}
			}

		}
	}while(0);
	return true;
}

bool ParserWDJEngine::ParserCompleteContent(std::string& content){
	std::string old_str = "<br />";
	std::string::size_type pos(0);
	do{
		if((pos=content.find(old_str))!=std::string::npos)
			content.replace(pos,old_str.length(),"\n");
		else
			break;
	}while(1);
	return true;
}
}
