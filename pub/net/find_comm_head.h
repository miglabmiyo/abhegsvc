/*
 * find_comm_head.h
 *
 *  Created on: 2014年11月17日
 *      Author: kerry
 */

#ifndef _NET_FIND_COMM_HEAD_H_
#define _NET_FIND_COMM_HEAD_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{


//推荐
class FindType:public LoginHeadPacket{
public:
	FindType(NetBase* m)
	:LoginHeadPacket(m){

	}
};


}


namespace netcomm_send{

class AppElement:public base_logic::DictionaryValue{
public:
	AppElement(){
	}
	virtual ~AppElement(){}
public:
	inline void set_advert(const int64 id,const int32 type,const int32 order,const int64 down,
			const std::string& name,const std::string& pic){
		this->SetBigInteger(L"id",id);
		this->SetInteger(L"type",type);
		this->SetInteger(L"order",order);
		this->SetInteger(L"down",down);
		this->SetString(L"name",name);
		this->SetString(L"pic",pic);
	}

	inline void set_findapp_element(const int64 id,const int32 type,const int64 down,
			const int32 order,const std::string& logo,const std::string& name,
			const std::string& summary){
		this->SetBigInteger(L"id",id);
		this->SetInteger(L"type",type);
		this->SetInteger(L"order",order);
		this->SetInteger(L"down",down);
		this->SetString(L"logo",logo);
		this->SetString(L"name",name);
		this->SetString(L"summary",summary);
	}
};


class Topics:public base_logic::DictionaryValue{
public:
	Topics(){
	}
	virtual ~Topics(){}
public:
	inline void set_app_topics(const int64 id,const int64 order,
		const std::string& name,const std::string& pic){
		this->SetBigInteger(L"id",id);
		this->SetInteger(L"order",order);
		this->SetString(L"pic",pic);
		this->SetString(L"name",name);
	}
};



class FindGameStore:public HeadPacket{
public:
	FindGameStore(){
		base_.reset(new netcomm_send::NetBase());
		emblem_.reset(new base_logic::DictionaryValue());
		important_.reset(new base_logic::ListValue());
		popularity_.reset(new base_logic::ListValue());
	}

	inline void set_important(base_logic::DictionaryValue* app){
		important_->Append(app);
	}

	inline void set_popularity(base_logic::DictionaryValue* app){
		popularity_->Append(app);

	}

	inline void set_emblem(base_logic::DictionaryValue* app){
		emblem_.reset(app);
	}

	netcomm_send::NetBase* release(){
		if(!important_->empty())
			this->base_->Set(L"important",important_.release());
		if(!popularity_->empty())
			this->base_->Set(L"popularity",popularity_.release());
		if(!emblem_->empty())
			this->base_->Set(L"emblem",emblem_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::DictionaryValue>       emblem_;
	scoped_ptr<base_logic::ListValue>             important_;
	scoped_ptr<base_logic::ListValue>             popularity_;
};


class FindBookStore:public HeadPacket{
public:
	FindBookStore(){
		base_.reset(new netcomm_send::NetBase());
		advert_.reset(new base_logic::ListValue());
		boys_.reset(new base_logic::ListValue());
		girls_.reset(new base_logic::ListValue());
		hot_.reset(new base_logic::ListValue());
		topics_.reset(new base_logic::ListValue());
	}

	inline void set_advert(base_logic::DictionaryValue* app){
		advert_->Append(app);
	}

	inline void set_boys(base_logic::DictionaryValue* app){
		boys_->Append(app);
	}

	inline void set_girls(base_logic::DictionaryValue* app){
		girls_->Append(app);

	}

	inline void set_hot(base_logic::DictionaryValue* app){
		hot_->Append(app);

	}

	inline void set_topics(base_logic::DictionaryValue* app){
		topics_->Append(app);
	}

	netcomm_send::NetBase* release(){
		if(!advert_->empty())
			this->base_->Set(L"advert",advert_.release());
		if(!boys_->empty())
			this->base_->Set(L"boys",boys_.release());
		if(!girls_->empty())
			this->base_->Set(L"girls",girls_.release());
		if(!hot_->empty())
			this->base_->Set(L"hot",hot_.release());
		if(!topics_->empty())
			this->base_->Set(L"topices",topics_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             advert_;
	scoped_ptr<base_logic::ListValue>             boys_;
	scoped_ptr<base_logic::ListValue>             girls_;
	scoped_ptr<base_logic::ListValue>             hot_;
	scoped_ptr<base_logic::ListValue>             topics_;
};

class FindAppStore:public HeadPacket{

public:
	FindAppStore(){
		base_.reset(new netcomm_send::NetBase());
		advert_.reset(new base_logic::ListValue());
		important_.reset(new base_logic::ListValue());
		popularity_.reset(new base_logic::ListValue());
		hot_.reset(new base_logic::ListValue());
		topics_.reset(new base_logic::ListValue());
	}




	netcomm_send::NetBase* release(){
		if(!advert_->empty())
			this->base_->Set(L"advert",advert_.release());
		if(!important_->empty())
			this->base_->Set(L"important",important_.release());
		if(!popularity_->empty())
			this->base_->Set(L"popularity",popularity_.release());
		if(!hot_->empty())
			this->base_->Set(L"hot",hot_.release());
		if(!topics_->empty())
			this->base_->Set(L"specialtopics",topics_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_advert(base_logic::DictionaryValue* app){
		advert_->Append(app);
	}

	inline void set_important(base_logic::DictionaryValue* app){
		important_->Append(app);
	}

	inline void set_popularity(base_logic::DictionaryValue* app){
		popularity_->Append(app);

	}

	inline void set_hot(base_logic::DictionaryValue* app){
		hot_->Append(app);

	}

	inline void set_topics(base_logic::DictionaryValue* app){
		topics_->Append(app);
	}


private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             advert_;
	scoped_ptr<base_logic::ListValue>             important_;
	scoped_ptr<base_logic::ListValue>             popularity_;
	scoped_ptr<base_logic::ListValue>             hot_;
	scoped_ptr<base_logic::ListValue>             topics_;
};

}
#endif /* _NET_USER_COMM_HEAD_H_ */
