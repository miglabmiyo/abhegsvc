/*
 * news_snssdk_connector.cc
 *
 *  Created on: 2015年4月23日
 *      Author: pro
 */
#include "news_snssdk_connector.h"
#include "dic/base_dic_redis_auto.h"
#include "http/http_method.h"
#include "basic/basic_util.h"
#include "logic/logic_unit.h"
#include <sstream>

namespace hacksvc_logic{

NewsSnsSDKImpl::NewsSnsSDKImpl(){

}

NewsSnsSDKImpl::~NewsSnsSDKImpl(){
}

void NewsSnsSDKImpl::Init(std::list<base::ConnAddr>& addrlist){
	CreateAdValue();
	ReadContentData();
}

void NewsSnsSDKImpl::Release(){

}

void NewsSnsSDKImpl::CreateAdValue(){
	std::string app_name = "欢乐斗地主";
	std::string title = "欢乐斗地主";
	std::string img_url = "http://p2.pstatp.com/origin/2952/2448133154";
	std::string web_url = "http://121.40.208.27/huanle/index.html";
	std::string down_url = "http://apk.dl.tuyoo.com/down/ddz/cpa30.happy.2837.apk";
	std::string desc = "全新欢乐斗地主,头条吐血推荐，让你金币赚翻";
	std::string web_title = "欢乐斗地主";
	std::string packetname = "com.doudizhu.mainhuanle";

	ad_value_.reset(new base_logic::DictionaryValue());

	ad_value_->SetString(L"log_extra","{\"req_id\": \"8837e6e55707c17fb\"}");
	ad_value_->SetString(L"open_url","");
	ad_value_->SetString(L"app_name",app_name);
	ad_value_->SetInteger(L"rate",-1);
	ad_value_->SetString(L"web_url",web_url);
	ad_value_->SetString(L"alert_text","");
	ad_value_->SetBigInteger(L"id",4231801180);
	ad_value_->SetString(L"click_track_url","");
	ad_value_->SetInteger(L"cell_type",10);
	ad_value_->SetString(L"title",title);
	ad_value_->SetString(L"download_url",down_url);
	ad_value_->SetString(L"label","推广");
	ad_value_->SetString(L"version","3.372");
	ad_value_->SetString(L"type","app");
	ad_value_->SetString(L"track_url","");
	ad_value_->SetBigInteger(L"ad_id",4231801180);
	ad_value_->SetString(L"description",desc);
	ad_value_->SetString(L"web_title",web_title);
	ad_value_->SetInteger(L"display_type",2);
	ad_value_->SetString(L"package",packetname);
	ad_value_->SetBigInteger(L"behot_time",time(NULL));

	//image
	scoped_ptr<base_logic::DictionaryValue> image(new base_logic::DictionaryValue());
	image->SetInteger(L"width",580);
	image->SetString(L"uri","2952/2448133154");
	image->SetInteger(L"height",240);

	//URL_LIST
	scoped_ptr<base_logic::ListValue> img_list(new base_logic::ListValue());
	img_list->Append(base_logic::Value::CreateStringValue(img_url));

	image->Set(L"url_list",img_list.release());

	ad_value_->Set(L"image",image.release());
}


bool NewsSnsSDKImpl::OnRequestNews(const int32 type){
	bool r = false;
	switch(type){
	case TYPE_RECOMMEND:
		r = OnNewsRecommend();
		break;
	}

	return r;
}

void NewsSnsSDKImpl::OnTimeCheck(){
	bool r = false;
	base_logic::Value* value = ParserNewsContent(content_);
	if(value==NULL)
		return;
	r = OnReplaceRecommend(value,true);
	if(!r||value==NULL)
		return;
	//序列化 写入redis
	StorageData(value);
}

base_logic::Value* NewsSnsSDKImpl::ParserNewsContent(std::string& content){
	std::string error_str;
	int jerror_code = 0;
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	base_logic::DictionaryValue*  value = (base_logic::DictionaryValue* )serializer->Deserialize(&jerror_code,&error_str);
	return (base_logic::Value*)(value);
}

bool NewsSnsSDKImpl::GetTestContent(std::string& content){
	content = content_;
	return true;
}


void NewsSnsSDKImpl::ReadContentData(){
	bool r =false;
	char* value;
	size_t value_len = 0;
	std::string key_str="SNSSDK";
	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
	LOG_DEBUG2("key:%s",key_str.c_str());
	//r = redis_engine_->SetValue(key_str.c_str(),key_str.length(),content.c_str(),content.length());
	r = redis_engine_->GetValue(key_str.c_str(),key_str.length(),&value,&value_len);
	if(r){
		content_.assign(value,value_len);
		if(value){free(value);value=NULL;}
	}

}
void NewsSnsSDKImpl::StorageData(base_logic::Value* value){
	std::string content;
	bool r =false;
	std::string key_str="SNSSDK";
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	serializer->Serialize(*value);

	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
	LOG_DEBUG2("key:%s",key_str.c_str());
	r = redis_engine_->SetValue(key_str.c_str(),key_str.length(),content.c_str(),content.length());
	content_ = content;
}


bool NewsSnsSDKImpl::OnNewsRecommend(){
	std::string content;
	bool r =false;
	r = OnRequestNewsRecommend(content);
	if(!r)
		return false;
	base_logic::Value* value = ParserNewsContent(content);
	if(value==NULL)
		return false;
	r = OnReplaceRecommend(value);
	if(!r||value==NULL)
		return false;
	//序列化 写入redis
	StorageData(value);
}


bool NewsSnsSDKImpl::OnReplaceRecommend(base_logic::Value* value,const bool del_last){
	bool r = false;
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)(value);
	base_logic::ListValue* list = NULL;
	r = dict->GetList(L"data",&list);
	int list_size = 0;
	if(!r||list==NULL)
		return false;
	list_size = list->GetSize();
	LOG_DEBUG2("list size %d",list_size);
	if(list_size<=0)
		return false;
	//解析第一个id
	base_logic::DictionaryValue*   first_value = NULL;
	r = list->GetDictionary(0,&first_value);
	if(r){
		int64 id = 0;
		r = first_value->GetBigInteger(L"group_id",&id);

		ad_value_->SetBigInteger(L"ad_id",id+2);
		ad_value_->SetBigInteger(L"behot_time",time(NULL));
	}
	//是否删除最后一个
	if(del_last){
		base_logic::Value* last_value;
		list->Remove(list_size -1,&last_value);
		if(last_value){
			delete last_value;
			last_value = NULL;
		}
	}
	if(ad_value_!=NULL)
		list->Append((base_logic::Value*)ad_value_.get());
	return true;
}

bool NewsSnsSDKImpl::OnRequestNewsRecommend(std::string& content){
	std::string url = "http://ic.snssdk.com/2/article/v24/stream/?count=2&cid=100668194&iid=2672560555&device_id=3368697976&ac=wifi&aid=13&app_name=news_article&version_code=451&device_platform=android&os_api=19&os_version=4.4.4&uuid=866963027412875&openudid=748df03310b60ca6";
	bool r = false;
	base_logic::LogicUnit::RequestGetMethod(url,content);
	base_logic::Value* value = ParserNewsContent(content);
	if(value==NULL)
		return false;
	return true;
}


}



