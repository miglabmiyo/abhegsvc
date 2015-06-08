/*
 * text_crawl_wdj_storage.cc
 *
 *  Created on: 2015年5月27日
 *      Author: Administrator
 */
#include "text_crawl_wdj_storage.h"
#include "storage/text_crawl_storage.h"
#include "protocol/data_packet.h"
#include "logic/logic_comm.h"
#include "basic/basic_util.h"
#include "check/newmacro.h"
#include <unistd.h>

namespace crawlersvc_logic{

TestCrawlWDJStorage::TestCrawlWDJStorage(){
	text_engine_.reset(crawlersvc_logic::CrawlerStorageBaseEngine::Create(TEXT_TYPE));
	txt_indetfity_ = time(NULL);

}


TestCrawlWDJStorage::~TestCrawlWDJStorage(){

}

bool TestCrawlWDJStorage::WriteAppDetailType(const std::string& name,
		base_logic::Value* value){
	//二进制转码
	std::string app_type;
	bool r = false;
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)(value);
	r =dict->GetString(L"app_type",&app_type);
	//struct AppDetailType info;
	packet::DataOutPacket out(false,APPDETAILTYPE_SIZE);
	out.Write32(APPDETAILTYPE_SIZE);
	out.WriteData(name.c_str(),64);
	out.WriteData(app_type.c_str(),32);

	base_logic::BinaryValue* binary = base_logic::BinaryValue::Create((char*)(out.GetData()),APPDETAILTYPE_SIZE);
	std::string file_name = "crawler_detail_text"+std::string(base::BasicUtil::StringUtil::Int64ToString(getpid()))
		+std::string(base::BasicUtil::StringUtil::Int64ToString(txt_indetfity_))+".txt";

	scoped_ptr<base_logic::DictionaryValue> dit(new base_logic::DictionaryValue());
	dit->SetString(L"crawl_path","./log");
	dit->SetString(L"crawl_file",file_name);
	dit->SetWithoutPathExpansion(L"crawl_binary",(base_logic::Value*)(binary));

	text_engine_->WriteData(0,(base_logic::Value*)(dit.get()));

	return true;
}

bool TestCrawlWDJStorage::WriteAppDetailComplete(const std::string& name,base_logic::Value* value){
	//反序列化 再以二进制存储
	std::string json;
	bool r  = false;
	unsigned char* zip_data = NULL;

	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_JSON,&json));
	r =  serializer->Serialize(*value);
	if(!r)
		return false;
	//struct AppDetailComplete
	packet::DataOutPacket out(false,PACKET_LENGTH+json.length());
	out.Write32(PACKET_LENGTH+json.length());
	out.WriteData(name.c_str(),64);
	out.WriteData(json.c_str(),json.length());


	unsigned long zip_data_size = mzip_.ZipData((unsigned char*)json.c_str(),json.length(),&zip_data);

	base_logic::BinaryValue* binary = base_logic::BinaryValue::Create((char*)(zip_data),zip_data_size);
	scoped_ptr<base_logic::DictionaryValue> dit(new base_logic::DictionaryValue());
	std::string file_name = "crawler_detail_text"+std::string(base::BasicUtil::StringUtil::Int64ToString(getpid()))
		+std::string(base::BasicUtil::StringUtil::Int64ToString(txt_indetfity_))+".txt";
	dit->SetString(L"crawl_path","./log");
	dit->SetString(L"crawl_file",file_name);
	dit->SetWithoutPathExpansion(L"crawl_binary",(base_logic::Value*)(binary));
	text_engine_->WriteData(0,(base_logic::Value*)(dit.get()));
	return true;
}
}

