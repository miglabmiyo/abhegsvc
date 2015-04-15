/*
 * user_basic_info.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */

#ifndef BOOK_BASIC_INFO_H_
#define BOOK_BASIC_INFO_H_
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/basictypes.h"
#include <string>
#include <list>
namespace booksvc_logic{

class HotWord{
public:
	explicit HotWord();

	HotWord(const HotWord& hotword);
	HotWord& operator = (const HotWord& hotword);

	base_logic::DictionaryValue* Release();

	const void set_id(const int64 id){data_->id_ = id;}
	const void set_count(const int64 count) {data_->count_ = count;}
	const void set_weight(const int32 weight) {data_->weight_ = weight;}
	const void set_type(const int32 type) {data_->type_ = type;}
	const void set_name(const std::string& name) {data_->name_ = name;}

	const int64 id() const {return data_->id_;}
	const int64 count() const {return data_->count_;}
	const int32 weight() const {return data_->weight_;}
	const int32 type() const {return data_->type_;}
	const std::string& name() const {return data_->name_;}

private:
	class Data{
	public:
		Data()
		:refcount_(1)
		,id_(0)
		,count_(0)
		,weight_(0)
		,type_(-1){}

	public:
		int64          id_;
		int64          count_;
		int32          weight_;
		int32          type_;//0 系统推荐， 1，人工推荐
		std::string    name_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};
	Data*    data_;
};
class ChapterInfo{
public:
	explicit ChapterInfo();

	ChapterInfo(const ChapterInfo& chapter);
	ChapterInfo& operator = (const ChapterInfo& chapter);

	base_logic::DictionaryValue* Release();

	void set_id(const int64 id){data_->id_ = id;}
	void set_bid(const int64 bid){data_->bid_ = bid;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_url(const std::string& url){data_->url_ = url;}

	const int64 id() const {return data_->id_;}
	const int64 bid() const {return data_->bid_;}
	const std::string& name() const {return data_->name_;}
	const std::string& url() const {return data_->url_;}


private:
	class Data{
	public:
		Data()
			:refcount_(1)
			,id_(0)
			,bid_(0){}
	public:
		int64 id_;
		int32 bid_;
		std::string name_;
		std::string url_;
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};
	Data*       data_;

};
}



#endif /* USER_BASIC_INFO_CC_ */



