/*
 * movie_comm_head.h
 *
 *  Created on: 2015年3月27日
 *      Author: pro
 */

#ifndef ABHEG_MOVIE_COMM_HEAD_H_
#define ABHEG_MOVIE_COMM_HEAD_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{
//获取视频详情
class MovieSummary: public LoginHeadPacket{
public:
	MovieSummary(NetBase* m)
	 :LoginHeadPacket(m){
		Init();
	}

	void Init(){
		bool r = false;
		GETBIGINTTOINT(L"id",movie_id_);
		if(!r) error_code_ = MOVIE_ID_LACK;
		GETBIGINTTOINT(L"machine",machine_);
		if(!r) machine_ = 1;

	}

	const int64 id() const {return this->movie_id_;}
	const int32 machine() const {return this->machine_;}

private:
	int64 movie_id_;
	int32 machine_;
};

typedef MovieSummary MovieType;

class MovieSearchType: public LoginHeadPacket{
public:
	MovieSearchType(NetBase* m)
	 :LoginHeadPacket(m){
		Init();
	}

	void Init(){
		bool r = false;
		GETBIGINTTOINT(L"tid",type_id_);
		if(!r) error_code_ = MOVIE_BTYPE_LACK;

	}
	const int64 tid() const {return this->type_id_;}

private:
	int64 type_id_;
};
}

namespace netcomm_send{

class MovieSummary: public HeadPacket{
public:
	MovieSummary(){
		base_.reset(new netcomm_send::NetBase());
		summary_.reset(new base_logic::DictionaryValue());
		about_movie_.reset(new base_logic::ListValue());
		advert_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!summary_->empty())
			this->base_->Set(L"summary",summary_.release());
		if(!about_movie_->empty())
			this->base_->Set(L"about",about_movie_.release());
		if(!advert_->empty())
			this->base_->Set(L"advert",advert_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	//
	inline void set_content(const std::string& content){
		this->summary_->SetString(L"content",content);
	}

	inline void set_star(const double star){
		this->summary_->SetReal(L"star",star);
	}

	inline void set_like(const int32 like){
		this->summary_->SetInteger(L"like",like);
	}

	inline void set_url(const std::string& url){
		this->summary_->SetString(L"url",url);
	}
	inline void set_name(const std::string& name){
		this->summary_->SetString(L"name",name);
	}

	inline void set_movie(base_logic::DictionaryValue* movie){
		this->about_movie_->Append(movie);
	}

	inline void set_advert(base_logic::DictionaryValue* advert){
		this->advert_->Append(advert);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       summary_;
	scoped_ptr<base_logic::ListValue>             about_movie_;
	scoped_ptr<base_logic::ListValue>             advert_;

};

class MovieSearch: public HeadPacket{
public:
	MovieSearch(){
		base_.reset(new netcomm_send::NetBase());
		new_.reset(new base_logic::ListValue());;
		hot_.reset(new base_logic::ListValue());;
	}

	netcomm_send::NetBase* release(){
		if(!new_->empty())
			this->base_->Set(L"new",new_.release());

		if(!hot_->empty())
			this->base_->Set(L"hot",hot_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}



	inline void set_new(base_logic::DictionaryValue* movie){
		this->new_->Append(movie);
	}

	inline void set_hot(base_logic::DictionaryValue* hot){
		this->hot_->Append(hot);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             new_;
	scoped_ptr<base_logic::ListValue>             hot_;

};
}



#endif /* MOVIE_COMM_HEAD_H_ */
