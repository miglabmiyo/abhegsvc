/*
 * rebot_basic_info.h
 *
 *  Created on: 2014年12月17日
 *      Author: kerry
 */

#ifndef REBOT_BASIC_INFO_H_
#define REBOT_BASIC_INFO_H_

#include "logic/base_values.h"
#include "basic/basictypes.h"
#include <string>
#include <list>
namespace robotsvc_logic{

class BookInfo{
public:
	explicit BookInfo();
	BookInfo(const BookInfo& bookinfo);
	BookInfo& operator = (const BookInfo& bookinfo);

	BookInfo(base_logic::DictionaryValue* value);

	const int32 type() const {return data_->type_;}
	const int32 isadd() const {return data_->isadd_;}
	const std::string book_name() const {return data_->book_name_;}
	const std::string book_hash_name() const {return data_->book_hash_name_;}
	const std::string book_intro() const {return data_->book_intro_;}
	const std::string book_pubtime() const {return data_->book_pubtime_;}
	const std::string book_author() const {return data_->book_author_;}
	const std::string book_cover() const {return data_->book_cover_;}

	void set_type(const int32 type){data_->type_ = type;}
	void set_book_name(const std::string& book_name){data_->book_name_ = book_name;}
	void set_book_hash_name(const std::string& book_hash_name){data_->book_hash_name_ = book_hash_name;}
	void set_intro(const std::string& intro){data_->book_intro_ = intro;}
	void set_pubtime(const std::string& pubtime){data_->book_pubtime_ = pubtime;}
	void set_author(const std::string& author){data_->book_author_ = author;}
	void set_book_cover(const std::string& cover){data_->book_cover_ = cover;}

private:
	class Data{
	public:
		Data()
		:refcount_(0)
		,type_(0)
		,isadd_(0){}
	public:
		int32       type_;
		int32       isadd_;
		std::string book_name_;
		std::string book_hash_name_;
		std::string book_intro_;
		std::string book_pubtime_;
		std::string book_author_;
		std::string book_cover_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};
	Data*         data_;
};

class BookChapterCollection{
public:
	explicit BookChapterCollection();
	BookChapterCollection(const BookChapterCollection& book_chapter);
	BookChapterCollection& operator = (const BookChapterCollection& book_chapter);

	BookChapterCollection(base_logic::DictionaryValue* value);

	const int64 book_id() const {return data_->book_id_;}
	const int32 isadd() const {return data_->isadd_;}
	const std::string& chapter_name() const {return data_->chapter_name_;}
	const std::string& hash_book_name() const {return data_->hash_book_name_;}
	const std::string& hash_chapter_name() const {return data_->hash_chapter_name_;}
	const std::string& chapter_address() const {return data_->chapter_address_;}
	const std::string& book_name() const {return data_->book_name_;}

	void set_book_id(const int64 book_id){data_->book_id_ = book_id;}
	void set_book_name(const std::string& book_name){data_->book_name_ = book_name;}
	void set_chapter_name(const std::string& chapter_name) {data_->chapter_name_ = chapter_name;}
	void set_hash_book_name(const std::string& hash_book_name) {data_->hash_book_name_ = hash_book_name;}
	void set_hash_chapter_name(const std::string& hash_chapter_name) {data_->hash_chapter_name_ = hash_chapter_name;}
	void set_chapter_address(const std::string& chapter_address) {data_->chapter_address_ = chapter_address;}
private:
	class Data{
	public:
		Data()
		:refcount_(0)
		,book_id_(0)
		,isadd_(0){}
	public:
		int64       book_id_;
		int32       isadd_;
		std::string book_name_;
		std::string chapter_name_;
		std::string hash_book_name_;
		std::string hash_chapter_name_;
		std::string chapter_address_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};
	Data*         data_;
};
}


#endif /* REBOT_BASIC_INFO_H_ */
