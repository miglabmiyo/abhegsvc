/*
 * wdjstore_impl.cc
 *
 *  Created on: 2015年5月11日
 *      Author: pro
 */
#include "wdj/wdjstore_impl.h"
#include "logic/logic_comm.h"
#include "logic/logic_infos.h"
#include "file/file_path.h"
#include "file/file_util.h"
#include "check/newmacro.h"
#include "definition.h"

namespace crawlersvc_logic{


WDJStoreImpl::WDJStoreImpl()
:count_(10)
,from_(-10){
	engine_.reset(crawlersvc_logic::CrawlerStoreEngine::Create(CRAWLER_ENGINE_WDJ));
	redis_engine_.reset(new crawlersvc_logic::RedisCrawlWDJStorage());
	mysql_engine_.reset(new crawlersvc_logic::MysqlCrawlWDJStorage());
	text_engine_.reset(new crawlersvc_logic::TestCrawlWDJStorage());
	parser_engine_.reset(new crawlersvc_logic::ParserWDJEngine());
}

WDJStoreImpl::~WDJStoreImpl(){

}

void WDJStoreImpl::Init(std::list<base::ConnAddr>& addrlist){

}

void WDJStoreImpl::Release(){

}


bool WDJStoreImpl::OnTasks(const int32 type){
	switch(type){
	case TASK_TEST:
		OnTest();
		break;
	case TASK_DB_READ:
		OnReadDBInfoCrawl();
	default:
		break;
	}
	return true;
}

void WDJStoreImpl::OnTimeCheck(){

}

bool WDJStoreImpl::OnReadDBInfoCrawl(void){
	//std::string test_url = "api.wandoujia.com/v1/apps/detailCards?f=phoenix2&itemNumPerLine=10&max=16&packageName=com.imib.cctv&net=WIFI&pos=null&timestamp=1431856823842&id=wandoujia_android&groupId=1&v=4.23.1&u=c67a5bdeabc74922b9928a88ba83f7d7e658275f&start=0&token=c5f637eb00cbbfc7478fb09a6502d9f2&vc=7930&ch=dao1_ad";
	scoped_ptr<base_logic::ListValue> list(new base_logic::ListValue);
	__sync_fetch_and_add(&from_,count_);
	//mysql_engine_->ReadWDJDetailInfo(from_,count_,(base_logic::Value*)(list.get()));
	//LOG_DEBUG2("list.size() %lld",list->GetSize());
	//爬取信息
	int i =10;
	while(/*list->GetSize()>0*/i>0){
		base_logic::Value* value = NULL;
		std::string url = "http://api.wandoujia.com/v1/apps/cn.yicha.mmi.online.apk103?id=wandoujia_android&f=phoenix2&v=4.24.1&u=9e0e2e27127a494eb1c32fbd57c9eba6ba1592d8&max=20&start=0&vc=7913&ch=meizu_market&net=WIFI&timestamp=1431796944747&token=85f73c7376a6df938cdef19b4f9cb22a";
		int64 id = 0;
		//list->Remove(0,&value);
		//base_logic::DictionaryValue* dict =(base_logic::DictionaryValue*)(value);
		//dict->GetString(L"url",&url);
		//dict->GetBigInteger(L"id",&id);
		LOG_DEBUG2("url %s",url.c_str());
		CrawlDetail(id,url);
		i--;
		/*if(dict!=NULL){
			delete dict;
			dict = NULL;
		}*/
	}

	return true;
}


bool WDJStoreImpl::CrawlDetail(const int64 id,const std::string& url){
	std::string name;
	scoped_ptr<base_logic::DictionaryValue>dict(ParserUrl(url));
	if(dict==NULL)
		return false;
	bool r = dict->GetString(L"identifier",&name);
	if(name=="app"||name=="importantApps") //app 墙纸
		return false;
	//base_logic::DictionaryValue* response =(base_logic::DictionaryValue*)(engine_->OnCrawlInfo(IMPL_APP_DETAILS,(base_logic::Value*)(dict.get())));
	scoped_ptr<base_logic::DictionaryValue> response((base_logic::DictionaryValue*)(engine_->OnCrawlInfo(IMPL_APP_DETAILS,(base_logic::Value*)(dict.get()))));
	if(response==NULL){
		//mysql_engine_->UpdateCrawlerURLState(id,-1);
		return false;
	}

	//mysql_engine_->CreaeAppDetailInfo((base_logic::Value*)(response.get()));

	//text_engine_->WriteAppDetailComplete(name,(base_logic::Value*)(response.get()));
	/*std::string app_type = "GAME";
	//解析
	response->GetString(L"appType",&app_type);
	scoped_ptr<base_logic::DictionaryValue> dit(new base_logic::DictionaryValue());
	dit->SetString(L"type",app_type);
	//解析存储

	//存储
	//redis_engine_->WriteAppDetailType(name,dit.get());
	text_engine_->WriteAppDetailType(name,dit.get());
	//更新状态
	mysql_engine_->UpdateCrawlerURLState(id,1);*/
	return true;
}


base_logic::DictionaryValue* WDJStoreImpl::ParserUrl(const std::string& url){
	std::string query;
	std::string name;
	std::string sub_str;
	std::string error_str;
	bool r = false;
	int error_code = 0;
	size_t pos = url.find("?");
	query = url.substr(pos+1,url.length());

	//LOG_DEBUG2("query %s",query.c_str());
	sub_str =  url.substr(0,pos);
	name = sub_str.substr(sub_str.rfind("/")+1,sub_str.length());
	query.append("\n");

	//解析query
	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP,&query));
	base_logic::DictionaryValue*  value = (base_logic::DictionaryValue*)(serializer.get()->Deserialize(&error_code,&error_str));
	if(value==NULL)
		return NULL;
	if(name=="detailCards"){//豌豆荚老接口
		r = value->GetString(L"packageName",&name);
		if(!r)
			return NULL;
	}
	value->SetString(L"identifier",name);
	return value;
}

bool WDJStoreImpl::OnTest(){

	//单元测试
	/*std::string name = "com.fingersoft.hillclimb";
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	dict->SetString(L"identifier",name);
	dict->SetBigInteger(L"timestamp",1428992136630);
	dict->SetString(L"id","wandoujia_android");
	dict->SetString(L"token","f0ca1ccc1a60ef3e0ce6105b353ab762");
	base_logic::DictionaryValue* response =(base_logic::DictionaryValue*)(engine_->OnCrawlInfo(IMPL_APP_DETAILS,(base_logic::Value*)(dict.get())));
	std::string app_type;
	//解析
	response->GetString(L"appType",&app_type);
	scoped_ptr<base_logic::DictionaryValue> dit(new base_logic::DictionaryValue());
	dit->SetString(L"type",app_type);
	//存储
	redis_engine_->WriteAppDetailType(name,dit.get());*/
	std::string url = "http://api.wandoujia.com/v1/apps/com.tencent.mm?identifier=com.tencent.mm&timestamp=1428992136630&id=wandoujia_android&f=phoenix2&v=4.25.1&u=5b1fff6e5dac4e49a9bf2b7faef2616a117ddaa0&max=20&start=0&token=f0ca1ccc1a60ef3e0ce6105b353ab762&vc=7955&ch=wandoujia_wap&net=WIFI&pos=m/games/index/section/0:198412830";
	int64 id = 0;
	CrawlDetail(id,url);

	return true;
}





}



