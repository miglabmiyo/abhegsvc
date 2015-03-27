/*
 * robot_basic_info.cc
 *
 *  Created on: 2014年12月17日
 *      Author: kerry
 */

#include "robot_basic_info.h"
namespace robotsvc_logic{
BookInfo::BookInfo(){
	data_ = new Data();
}

BookInfo::BookInfo(const BookInfo& bookinfo)
:data_(bookinfo.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

BookInfo& BookInfo::operator =(const BookInfo& bookinfo){
	if(bookinfo.data_!=NULL){
		bookinfo.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}

	data_ = bookinfo.data_;
	return (*this);
}

BookInfo::BookInfo(base_logic::DictionaryValue* value){
	data_ = new Data();
	bool  r = false;
	base_logic::DictionaryValue* dic =  value;
	r = dic->GetInteger(L"type",&data_->type_);
	if(!r)data_->type_ = 0;
	r = dic->GetString(L"book_name",&data_->book_name_);
	if(!r)data_->isadd_ = 1;
	r = dic->GetString(L"hash_book_name",&data_->book_hash_name_);
	if(!r)data_->isadd_ = 1;
	r = dic->GetString(L"intro",&data_->book_intro_);
	if(!r)data_->book_intro_ = "暂无介绍";
	dic->GetString(L"pubtime",&data_->book_pubtime_);
	if(!r)data_->book_pubtime_ = "未知";
	dic->GetString(L"author",&data_->book_author_);
	if(!r)data_->book_author_ = "佚名";
	dic->GetString(L"cover",&data_->book_cover_);
	if(!r)data_->book_cover_ = "http://pic.book.miglab.com/default.jpg";
}

BookChapterCollection::BookChapterCollection(){
	data_ = new Data();
}

BookChapterCollection::BookChapterCollection(const BookChapterCollection& book_chapter)
:data_(book_chapter.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

BookChapterCollection& BookChapterCollection::operator =(const BookChapterCollection& book_chapter){
	if(book_chapter.data_!=NULL){
		book_chapter.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}

	data_ = book_chapter.data_;
	return (*this);
}

BookChapterCollection::BookChapterCollection(base_logic::DictionaryValue* value){
	//
	data_ = new Data();
	base_logic::DictionaryValue* dic =  value;
	dic->GetBigInteger(L"id",&data_->book_id_);
	dic->GetString(L"chapter_name",&data_->chapter_name_);
	dic->GetString(L"hash_book_name",&data_->hash_book_name_);
	dic->GetString(L"hash_chapter_name",&data_->hash_chapter_name_);
	dic->GetString(L"chapter_address",&data_->chapter_address_);
	dic->GetString(L"book_name",&data_->book_name_);
}


}


