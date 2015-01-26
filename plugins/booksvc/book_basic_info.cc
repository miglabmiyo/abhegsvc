/*
 * user_basic_info.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#include "book_basic_info.h"
namespace booksvc_logic{

ChapterInfo::ChapterInfo(){
	data_ = new Data();
}


ChapterInfo::ChapterInfo(const ChapterInfo& chapter)
:data_(chapter.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

ChapterInfo& ChapterInfo::operator =(const ChapterInfo& chapter){
	if(chapter.data_!=NULL){
		chapter.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = chapter.data_;
	return (*this);
}

base_logic::DictionaryValue* ChapterInfo::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=0)
		dict->SetBigInteger(L"id",data_->id_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(data_->bid_!=0)
		dict->SetInteger(L"bid",data_->bid_);
	if(!data_->url_.empty())
		dict->SetString(L"url",data_->url_);
	return dict.release();
}

}
