/*
 * txt_crawl_storage.cc
 *
 *  Created on: 2015年5月27日
 *      Author: Administrator
 */
#include "text_crawl_storage.h"
#include "db/base_db_mysql_auto.h"
#include "file/file_path.h"
#include "file/file_util.h"
#include "check/newmacro.h"


namespace crawlersvc_logic{

TextCrawlStorage::TextCrawlStorage(){

}

TextCrawlStorage::~TextCrawlStorage(){

}

void TextCrawlStorage::Init(std::list<base::ConnAddr>& addrlist){
}

void TextCrawlStorage::Release(){

}

bool TextCrawlStorage::WriteData(const int32 type,base_logic::Value* value){
	//写入文本
	//路径
	bool r = false;
	std::string path;
	std::string filename;
	base_logic::BinaryValue* binary;
	base_logic::DictionaryValue* dict = (base_logic::DictionaryValue*)(value);
	r = dict->GetString(L"crawl_path",&path);
	if(!r)
		return false;
	r = dict->GetString(L"crawl_file",&filename);
	if(!r)
		return false;
	r = dict->GetBinary(L"crawl_binary",&binary);
	if(!r)
		return false;
	file::FilePath current_dir_path(path);
	if(!file::DirectoryExists(current_dir_path)){
		file::CreateDirectory(current_dir_path);
	}
	file::FilePath file_path(path+"/"+filename);
	file::WriteFile(file_path,binary->GetBuffer(),binary->GetSize());
	return true;
}

bool TextCrawlStorage::ReadData(const std::string& sql,base_logic::Value* value,
		void (*storage_get)(void*,base_logic::Value*)){
	return true;
}


}

