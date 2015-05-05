/*
 * 360store_connector.cc

 *
 *  Created on: 2015年4月29日
 *      Author: pro
 *
 */

/*
 * ppstore_connector.cc

 *
 *  Created on: 2015年4月28日
 *      Author: pro
 */
#include "appstore_connector.h"
#include "qihoostore_connector.h"
#include "dic/base_dic_redis_auto.h"
#include "logic/logic_unit.h"

namespace hacksvc_logic{
QIHOOStoreImpl::QIHOOStoreImpl(){

}

QIHOOStoreImpl::~QIHOOStoreImpl(){

}

void QIHOOStoreImpl::Init(std::list<base::ConnAddr>& list){

}

void QIHOOStoreImpl::Release(){

}

void QIHOOStoreImpl::OnTimeCheck(){

}


bool QIHOOStoreImpl::OnRequestAppStoreInfo(const int32 type){
	bool r = false;
	switch(type){
	case IMPL_MAIN_RECOMMEND:
		OnMainRecommend();
		break;
	case IMPL_ADVERT:
		break;
	case IMPL_GAME_RECOMMEND:
		break;
	case IMPL_GAME_RANK:
		break;
	}

	return true;

}

bool  QIHOOStoreImpl::GetTestContent(std::string& content){
	content = content_;
	return true;
}

void QIHOOStoreImpl::StorageData(base_logic::Value* value){
	std::string content;
	bool r =false;
	std::string key_str="QIHOORECOMM";
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	serializer->Serialize(*value);

	base_dic::AutoDicCommEngine auto_engine;
	base_storage::DictionaryStorageEngine* redis_engine_  = auto_engine.GetDicEngine();
	LOG_DEBUG2("key:%s",key_str.c_str());
	r = redis_engine_->SetValue(key_str.c_str(),key_str.length(),content.c_str(),content.length());
	content_ = content;
}

base_logic::Value* QIHOOStoreImpl::ParserContent(std::string& content){
	std::string error_str;
	int jerror_code = 0;
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&content));
	base_logic::DictionaryValue*  value = (base_logic::DictionaryValue* )serializer->Deserialize(&jerror_code,&error_str);
	return (base_logic::Value*)(value);
}


void QIHOOStoreImpl::OnMainRecommend(){
	std::string content;
	bool r = false;
	r = OnRequestMainRecommend(content);
	if(!r)
		return ;
	base_logic::Value* value = ParserContent(content);
	if(value==NULL)
		return;
	r = OnReplaceMain(value);
	if(!r||value==NULL)
		return ;
	r = OnReplaceMain(value);
	if(!r||value==NULL)
		return ;
	StorageData(value);

}

bool QIHOOStoreImpl::OnReplaceMain(base_logic::Value* value){
	bool r = false;
	std::string name ="欢乐斗地主";
	std::string large_logo_category_url = "http://121.40.208.27/huanle/main.jpg";
	std::string image_url_704_244 = "http://121.40.208.27/huanle/main.jpg";
	std::string url = "http://121.40.208.27/huanle/index.html?webpg=qfnbebn";
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)(value);
	base_logic::DictionaryValue* data = NULL;
	base_logic::ListValue* category = NULL;
	r = dict->GetDictionary(L"data",&data);
	if(!r)
		return true;
	r = data->GetList(L"category",&category);
	if(!r||category==NULL)
		return true;
	int32 list_size = category->GetSize();

	//解析第一个进行替换
	base_logic::DictionaryValue*   first_value = NULL;
	r = category->GetDictionary(0,&first_value);
	if(!r)
		return true;
	first_value->SetString(L"name",name);
	first_value->SetString(L"soft_order","1");
	first_value->SetString(L"large_logo_category_url",large_logo_category_url);
	first_value->SetString(L"image_url_704_244",image_url_704_244);
	first_value->SetString(L"url",url);
	return true;

}


bool QIHOOStoreImpl::OnRequestMainRecommend(std::string& content){
	std::string url = "http://125.88.193.234/inew/getRecomendApps?iszip=1&logo_type=2&deflate_field=1&apiversion=2&os=19&model=MI+4LTE&sn=4.589389937671455&cu=qualcomm+msm8974pro-ac&bannertype=1&withext=1&vc=300030217&zjbb=1&datatype=adgame&page=1&fm=home&m=209d1dad5914d472ef5489678a740f29&m2=9e34ee6d91b9512f00411c5272c935b4&v=3.2.17&re=1&ch=490981&ppi=1080x1920&startCount=10&snt=-1";
	bool r = false;
	r = base_logic::LogicUnit::RequestGetMethod(url,content);
	return r;
}


}




