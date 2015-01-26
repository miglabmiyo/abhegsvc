/*
 * book_comm_head.h
 *
 *  Created on: 2015年1月25日
 *      Author: kerry
 */

#ifndef BOOK_COMM_HEAD_H_
#define BOOK_COMM_HEAD_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

//获取详细章节
class ChapterList:public LoginHeadPacket{
public:
	ChapterList(NetBase* m)
	:LoginHeadPacket(m){
		bool r = false;
		from_ = 0;
		count_ = 0;
		GETBIGINTTOINT(L"bookid",bookid_);
		if(!r) error_code_ = BOOK_ID_LACK;
		r = m_->GetString(L"booktoken",&booktoken_);
		if(!r) error_code_ = BOOK_TOKEN_LACK;
		if(!m_->GetBigInteger(L"from",&from_)) from_ = 0;
		if(!m_->GetBigInteger(L"count",&count_)) count_ = 0;
	}

	const int64 bookid() const {return this->bookid_;}
	const int64 from() const {return this->from_;}
	const int64 count() const {return this->count_==0?10:this->count_;}
	const std::string& booktoken() const {return this->booktoken_;}

private:
	int64       bookid_;
	int64       from_;
	int64       count_;
	std::string booktoken_;
};

////提交已购买书籍
class WantBook:public LoginHeadPacket{
public:
	WantBook(NetBase* m)
	:LoginHeadPacket(m){
		bool r = false;
		GETBIGINTTOINT(L"bookid",bookid_);
		if(!r) error_code_ = BOOK_ID_LACK;
	}
	const int64 bookid() {return this->bookid_;}
private:
	int64 bookid_;
};


//类别搜索
class SearchType:public LoginHeadPacket{
public:
	SearchType(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"btype",btype_);
		if(!r) error_code_ = BOOK_BTYPE_LACK;
		GETBIGINTTOINT(L"class",class_);
		if(!r) class_ = 0;
		GETBIGINTTOINT(L"from",from_);
		if(!r) from_ = 0;
		GETBIGINTTOINT(L"count",count_);
		if(!r) count_ = 10;
	}

	const int64 btype() const {return this->btype_;}

private:
	int32     btype_;
	int32     class_;
	int32     from_;
	int32     count_;

};

//获取用户书单
class BookList:public LoginHeadPacket{
public:
	BookList(NetBase* m)
	:LoginHeadPacket(m){
	}
};

class BookTopics:public LoginHeadPacket{
public:
	BookTopics(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void  Init(){
		bool r =  false;
		GETBIGINTTOINT(L"tid",topics_);
		if(!r) error_code_ = APPID_LACK;
	}

	const int64 topics() const {return this->topics_;}

private:
	int64       topics_;
};

//书籍详情
class BookSummary: public LoginHeadPacket{
public:
	BookSummary(NetBase* m)
	:LoginHeadPacket(m){
		bool r = false;
		GETBIGINTTOINT(L"bookid",bookid_);
		if(!r) error_code_ = BOOK_ID_LACK;
	}

	const int64 bookid() {return this->bookid_;}
private:
	int64 bookid_;
};
}

namespace netcomm_send{

//类别搜索
class SearchType:public HeadPacket{
public:
	SearchType(){
		base_.reset(new netcomm_send::NetBase());
		hot_book_.reset(new base_logic::ListValue());
		new_book_.reset(new base_logic::ListValue());
	}

	inline void SetHotBookInfo(base_logic::DictionaryValue* build){
		hot_book_->Append(build);
	}

	inline void SetNewBookInfo(base_logic::DictionaryValue* build){
		new_book_->Append(build);
	}


	netcomm_send::NetBase* release(){
		if(!hot_book_->empty())
			this->base_->Set(L"hot",hot_book_.release());
		if(!new_book_->empty())
			this->base_->Set(L"new",new_book_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             hot_book_;
	scoped_ptr<base_logic::ListValue>             new_book_;
};


class BookTopics:public HeadPacket{
public:
	BookTopics(){
		base_.reset(new netcomm_send::NetBase());
		topics_.reset(new base_logic::ListValue());
		follow_.reset(new base_logic::FundamentalValue(0));
	}

	netcomm_send::NetBase* release(){
		if(!topics_->empty())
			this->base_->Set(L"topics",topics_.release());

		this->base_->Set(L"follow",follow_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}


	inline void set_topics(base_logic::DictionaryValue* book){
		topics_->Append(book);
	}

	inline void set_follow(const int64 follow){
		follow_.reset(new base_logic::FundamentalValue(follow));
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             topics_;
	scoped_ptr<base_logic::FundamentalValue>      follow_;
};

//书籍详情
class BookSummary:public HeadPacket{
public:
	BookSummary(){
		base_.reset(new netcomm_send::NetBase());
		summary_.reset(new base_logic::DictionaryValue());
		user_.reset(new base_logic::DictionaryValue());
		label_.reset(new base_logic::ListValue());
	}

	virtual ~BookSummary(){

	}

	netcomm_send::NetBase* release(){
		if(summary_->size()!=0)
			this->base_->Set(L"summary",summary_.release());
		if(user_->size()!=0)
			this->base_->Set(L"user",user_.release());
		if(!label_->empty())
			this->base_->Set(L"label",label_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();

	}


	void set_summary(base_logic::DictionaryValue* book){
		summary_.reset(book);
	}

	void set_user(const int32 issave){
		user_->SetInteger(L"issave",issave);
	}

	void set_label(const std::string& label){
		label_->Append(base_logic::Value::CreateStringValue(label));
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       summary_;
	scoped_ptr<base_logic::DictionaryValue>       user_;
	scoped_ptr<base_logic::ListValue>             label_;
};



//提交
class WantBook:public HeadPacket{
public:
	WantBook(){
		base_.reset(new netcomm_send::NetBase());
	}
	~WantBook(){}

	inline void SetBookToken(const std::string& token){
		this->base_->SetString(L"book_token",token);
	}
	netcomm_send::NetBase* release(){
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
};



//书单
class BookList:public HeadPacket{
public:
	BookList(){
		base_.reset(new netcomm_send::NetBase());
		book_list_.reset(new base_logic::ListValue());
	}
	inline void SetBookList(base_logic::DictionaryValue* build){
		book_list_->Append(build);
	}

	netcomm_send::NetBase* release(){
		if(!book_list_->empty())
			this->base_->Set(L"list",book_list_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             book_list_;
};


//获取章节详情
class ChapterList:public HeadPacket{
public:
	ChapterList(){
		base_.reset(new netcomm_send::NetBase());
		chapter_list_.reset(new base_logic::ListValue());
	}
	inline void SetBookList(base_logic::DictionaryValue* build){
		chapter_list_->Append(build);
	}
	netcomm_send::NetBase* release(){
		if(!chapter_list_->empty())
			this->base_->Set(L"list",chapter_list_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             chapter_list_;
};

}



#endif /* BOOK_COMM_HEAD_H_ */
