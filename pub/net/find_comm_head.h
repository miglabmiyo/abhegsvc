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

//个人推荐
class FindPersonal:public LoginHeadPacket{
public:
	FindPersonal(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
		r = m_->GetBigInteger(L"category",&category_);
		if(!r) error_code_ = STORE_SEACH_BTYPE_LACK;
		r = m_->GetReal(L"latitude",&latitude_);
		if(!r) latitude_ = 0.0;
		r = m_->GetReal(L"longitude",&longitude_);
		if(!r) longitude_ = 0.0;
	}

	const int64 category() const {return this->category_;}
	const double latitude() const {return this->latitude_;}
	const double longitude() const {return this->longitude_;}
private:
	int64      category_;
	double     latitude_;
	double     longitude_;
};

//影视排行榜
class MovieRank:public LoginHeadPacket{
public:
	MovieRank(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
		r = m_->GetBigInteger(L"category",&category_);
		if(!r) category_ = 0;
	}
	const int64 category() const {return this->category_;}
private:
	int64      category_;
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
		pic_.reset(new base_logic::ListValue());
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

	inline void set_pic(const std::string& pic){
		pic_->Append(base_logic::Value::CreateStringValue(pic));
	}

	netcomm_send::NetBase* release(){
		if(!pic_->empty())
			this->emblem_->Set(L"pic",pic_.release());
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
	scoped_ptr<base_logic::ListValue>             pic_;
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


class FindMain:public HeadPacket{

public:
	FindMain(){
		base_.reset(new netcomm_send::NetBase());
		advert_.reset(new base_logic::ListValue());
		app_list_.reset(new base_logic::ListValue());
		game_list_.reset(new base_logic::ListValue());
		book_list_.reset(new base_logic::ListValue());
		music_list_.reset(new base_logic::ListValue());
		movie_list_.reset(new base_logic::ListValue());
	}




	netcomm_send::NetBase* release(){
		if(!advert_->empty())
			this->base_->Set(L"advert",advert_.release());
		if(!app_list_->empty())
			this->base_->Set(L"app",app_list_.release());
		if(!game_list_->empty())
			this->base_->Set(L"game",game_list_.release());
		if(!book_list_->empty())
			this->base_->Set(L"book",book_list_.release());
		if(!music_list_->empty())
			this->base_->Set(L"music",music_list_.release());
		if(!movie_list_->empty())
			this->base_->Set(L"movie",movie_list_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_advert(base_logic::DictionaryValue* app){
		advert_->Append(app);
	}

	inline void set_app(base_logic::DictionaryValue* app){
		app_list_->Append(app);
	}

	inline void set_game(base_logic::DictionaryValue* app){
		game_list_->Append(app);

	}

	inline void set_book(base_logic::DictionaryValue* app){
		book_list_->Append(app);

	}

	inline void set_music(base_logic::DictionaryValue* app){
		music_list_->Append(app);
	}

	inline void set_movie(base_logic::DictionaryValue* app){
		movie_list_->Append(app);
	}


private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             advert_;
	scoped_ptr<base_logic::ListValue>             app_list_;
	scoped_ptr<base_logic::ListValue>             game_list_;
	scoped_ptr<base_logic::ListValue>             book_list_;
	scoped_ptr<base_logic::ListValue>             music_list_;
	scoped_ptr<base_logic::ListValue>             movie_list_;
};


class FindGameRank:public HeadPacket{
public:
	FindGameRank(){
		base_.reset(new netcomm_send::NetBase());
		game_list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!game_list_->empty())
			this->base_->Set(L"list",game_list_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_game(base_logic::DictionaryValue* app){
		game_list_->Append(app);
	}
private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             game_list_;
};


typedef FindGameRank FindAppRank;

class FindGameStoreV2:public HeadPacket{
public:
	FindGameStoreV2(){
		base_.reset(new netcomm_send::NetBase());
		advert_.reset(new base_logic::ListValue());
		emblem_.reset(new base_logic::DictionaryValue());
		important_.reset(new base_logic::ListValue());
		popularity_.reset(new base_logic::ListValue());
		pic_.reset(new base_logic::ListValue());
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

	inline void set_emblem(base_logic::DictionaryValue* app){
		emblem_.reset(app);
	}

	inline void set_pic(const std::string& pic){
		pic_->Append(base_logic::Value::CreateStringValue(pic));
	}

	netcomm_send::NetBase* release(){
		if(!advert_->empty())
			this->base_->Set(L"advert",advert_.release());
		if(!pic_->empty())
			this->emblem_->Set(L"pic",pic_.release());
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
	scoped_ptr<base_logic::ListValue>             advert_; //广告推荐位
	scoped_ptr<base_logic::DictionaryValue>       emblem_;//首推位
	scoped_ptr<base_logic::ListValue>             important_;//精品推荐
	scoped_ptr<base_logic::ListValue>             popularity_;//人气推荐
	scoped_ptr<base_logic::ListValue>             pic_;//首推位图片
};

class FindMovies:public HeadPacket{
public:
	FindMovies(){
		base_.reset(new netcomm_send::NetBase());
		advert_.reset(new base_logic::ListValue());
		emblem_.reset(new base_logic::ListValue());
		popularity_.reset(new base_logic::ListValue());
		like_.reset(new base_logic::ListValue());
		person_.reset(new base_logic::ListValue());
	}


	netcomm_send::NetBase* release(){
		if(!advert_->empty())
			this->base_->Set(L"advert",advert_.release());
		if(!popularity_->empty())
			this->base_->Set(L"popularity",popularity_.release());
		if(!like_->empty())
			this->base_->Set(L"like",like_.release());
		if(!emblem_->empty())
			this->base_->Set(L"emblem",emblem_.release());
		if(!person_->empty())
			this->base_->Set(L"person",person_.release());

		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}


	void set_advert(base_logic::DictionaryValue* movies){
		advert_->Append(movies);
	}

	void set_emblem(base_logic::DictionaryValue* movies){
		emblem_->Append(movies);
	}

	void set_popularity(base_logic::DictionaryValue* movies){
		popularity_->Append(movies);
	}

	void set_like(base_logic::DictionaryValue* movies){
		like_->Append(movies);
	}

	void set_person(base_logic::DictionaryValue* movies){
		person_->Append(movies);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             advert_; //广告位视频
	scoped_ptr<base_logic::ListValue>             emblem_;//推荐视频
	scoped_ptr<base_logic::ListValue>             popularity_;//人气视频
	scoped_ptr<base_logic::ListValue>             like_;//好评最高
	scoped_ptr<base_logic::ListValue>             person_;//个人推荐


};

class MovieRank:public HeadPacket{
public:
	MovieRank(){
		base_.reset(new netcomm_send::NetBase());
		movie_list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!movie_list_->empty())
			this->base_->Set(L"movie",movie_list_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	void set_movie_list(base_logic::DictionaryValue* movie){
		movie_list_->Append(movie);
	}

private:
	scoped_ptr<netcomm_send::NetBase>              base_;
	scoped_ptr<base_logic::ListValue>              movie_list_;//电影
};

class FindPersonal:public HeadPacket{
public:
	FindPersonal(){
		base_.reset(new netcomm_send::NetBase());
		app_list_.reset(new base_logic::ListValue());
		game_list_.reset(new base_logic::ListValue());
		book_list_.reset(new base_logic::ListValue());
		movie_list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!app_list_->empty())
			this->base_->Set(L"app",app_list_.release());
		if(!game_list_->empty())
			this->base_->Set(L"game",game_list_.release());
		if(!book_list_->empty())
			this->base_->Set(L"book",book_list_.release());
		if(!movie_list_->empty())
			this->base_->Set(L"movie",movie_list_.release());

		if(category_.get()!=NULL)
				this->base_->Set(L"category",category_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	void set_app_list(base_logic::DictionaryValue* app){
		app_list_->Append(app);
	}

	void set_game_list(base_logic::DictionaryValue* game){
		game_list_->Append(game);
	}

	void set_book_list(base_logic::DictionaryValue* book){
		book_list_->Append(book);
	}

	void set_movie_list(base_logic::DictionaryValue* movie){
		movie_list_->Append(movie);
	}

	void set_category(const int32 category){
		category_.reset(new base_logic::FundamentalValue(category));
	}
private:
	scoped_ptr<netcomm_send::NetBase>              base_;
	scoped_ptr<base_logic::FundamentalValue>       category_;
	scoped_ptr<base_logic::ListValue>              app_list_;//应用
	scoped_ptr<base_logic::ListValue>              game_list_;//游戏
	scoped_ptr<base_logic::ListValue>              book_list_;//书籍
	scoped_ptr<base_logic::ListValue>              movie_list_;//电影

};

}
#endif /* _NET_USER_COMM_HEAD_H_ */
