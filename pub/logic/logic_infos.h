/*

 * logic_infos.h
 *
 *  Created on: 2014年12月2日
 *      Author: kerry
 */
#ifndef _ABHEG_LOGIC_INFOS_H__
#define _ABHEG_LOGIC_INFOS_H__
#include "logic/base_values.h"
#include "basic/scoped_ptr.h"
#include "basic/basictypes.h"
#include <string>
#include <list>

namespace base_logic{

//广告属性 //商城 书城 推荐
class AdvertInfos{
public:
	explicit AdvertInfos();
	AdvertInfos(const AdvertInfos& advertinfo);
	AdvertInfos& operator = (const AdvertInfos& advert);

	base_logic::DictionaryValue* Release();

	const int64 id() const {return data_->id_;}
	const int32 type() const {return data_->type_;}
#if defined(__OLD_VERSION__)
	const int32 subtype() const {return data_->subtype_;}
	const int64 follower() const {return data_->follower_;}
#else
	const int64 subid() const {return data_->subid_;}
	const int32 flag() const {return data_->flag_;}
	const int32 out() const {return data_->out_;}
	const std::string& url() const {return data_->url_;}
#endif
	const std::string& pic() const {return data_->pic_;}
	const std::string& name() const {return data_->name_;}
	const std::string& desc() const {return data_->desc_;}

	void set_id(const int64 id){data_->id_ = id;}
	void set_type(const int32 type){data_->type_ = type;}
#if defined(__OLD_VERSION__)
	void set_subtype(const int32 subtype){data_->subtype_ = subtype;}
	void set_follower(const int64 follower){data_->follower_ = follower;}
#else
	void set_subid(const int64 subid){data_->subid_ = subid;}
	void set_flag(const int32 flag) {data_->flag_ = flag;}
	void set_out(const int32 out){data_->out_ = out;}
	void set_url(const std::string& url){data_->url_ = url;}
#endif
	void set_pic(const std::string& pic){data_->pic_ = pic;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_desc(const std::string& desc){data_->desc_ = desc;}

private:
	class Data{
	public:
		Data():refcount_(1)
		,id_(0)
		,type_(-1)
#if defined(__OLD_VERSION__)
		,subtype_(-1)
		,follower_(-1)
#else
		,subid_(0)
		,flag_(0)
		,out_(0)
#endif
	{}
	public:
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	public:
		int64        id_;
		int32        type_;
#if defined(__OLD_VERSION__)
		int32        subtype_;
		int64        follower_;
#else
		int64        subid_;
		int32        flag_;
		int32        out_;
		std::string  url_;
#endif
		std::string  pic_;
		std::string  name_;
		std::string  desc_;
	private:
		int refcount_;
	};

	Data* data_;
};

//专题属性
class Topics{
public:
	explicit Topics();
	Topics(const Topics& topics);
	Topics& operator = (const Topics& topics);

	base_logic::DictionaryValue* Release();

	const int64 id() const {return data_->id_;}
	const int64 follower() const {return data_->follower_;}
	const std::string name() const {return data_->name_;}
	const std::string pic() const {return data_->pic_;}

	void set_id(const int64 id){data_->id_ = id;}
	void set_follower(const int64 follower){data_->follower_ = follower;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_pic(const std::string& pic){data_->pic_ = pic;}
private:
	class Data{
	public:
		Data():refcount_(1)
		,id_(0)
		,follower_(-1){}
	public:
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	public:
		int64        id_;
		int64        follower_;
		std::string  name_;
		std::string  pic_;
	private:
		int refcount_;
	};

	Data* data_;
};

//APP属性 推荐插件和商场插件都会用到
class AppInfos{
public:
	explicit AppInfos();
	AppInfos(const AppInfos& appinfo);
	AppInfos& operator = (const AppInfos& appinfo);

	base_logic::DictionaryValue* Release(bool summary = true);

	const int64 id() const {return data_->id_;}
	const int32 type() const {return data_->type_;}
	const int64 down() const {return data_->down_;}
	const int64 like() const {return data_->like_;}
	const int32 lang() const {return data_->lang_;}
	const int32 attr() const {return data_->attr_;}
	const double size() const {return data_->size_;}
	const std::string& ios_url() const {return data_->ios_url_;}
	const std::string& android_url() const {return data_->android_url_;}
	const std::string& provider() const {return data_->provider_;}
	const std::string& version() const {return data_->version_;}
	const std::string& ontime() const {return data_->ontime_;}
	const std::string& logo() const {return data_->logo_;}
	const std::string& name() const {return data_->name_;}
	const std::string& summary() const {return data_->summary_;}
	const std::string& content() const {return data_->content_;}

	const int32 emblem_pic_size() const {data_->emblem_pic_list_.size();}
	const int32 summary_pic_size() const {data_->summary_pic_list_.size();}

	void set_id(const int64 id){data_->id_ = id;}
	void set_type(const int32 type){data_->type_ = type;}
	void set_down(const int64 down) {data_->down_ = down;}
	void set_like(const int64 like) {data_->like_ = like;}
	void set_lang(const int lang) {data_->lang_ = lang;}
	void set_size(const double size) {data_->size_ = size;}
	void set_attr(const int32 attr){data_->attr_ = attr;}
	void set_ios_url(const std::string& ios_url){data_->ios_url_ = ios_url;}
	void set_android_url(const std::string& android_url){data_->android_url_ = android_url;}
	void set_provider(const std::string& provider){data_->provider_ = provider;}
	void set_version(const std::string& version){data_->version_ = version;}
	void set_ontime(const std::string& ontime){data_->ontime_ = ontime;}
	void set_logo(const std::string& logo){data_->logo_ = logo;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_summary(const std::string& summary){data_->summary_ = summary;}
	void set_content(const std::string& content){data_->content_ = content;}

	void set_emblem_pic(const std::string& pic){
		data_->emblem_pic_list_.push_back(pic);
	}

	void set_summary_pic(const std::string& pic){
		data_->summary_pic_list_.push_back(pic);
	}

	static bool cmp(AppInfos& t_info,AppInfos& r_info);
private:
	class Data{
	public:
		Data():refcount_(1)
		,id_(0)
		,type_(-1)
		,down_(-1)
		,like_(-1)
		,lang_(-1)
		,size_(0.0)
		,attr_(-1){}
	public:
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	public:
		int64                  id_;
		int32                  type_;
		int64                  down_;
		int64		           like_;
		int32                  lang_;
		int32                  attr_;
		double                 size_;
		std::string            ios_url_;
		std::string            android_url_;
		std::string            provider_;
		std::string            version_;
		std::string            ontime_;
		std::string            logo_;
		std::string            name_;
		std::string            summary_;
		std::string            content_;
		std::list<std::string> emblem_pic_list_;
		std::list<std::string> summary_pic_list_;
	private:
		int refcount_;
	};

	Data* data_;
};


class BookInfo{
public:
	explicit BookInfo();
	BookInfo(const BookInfo& book_info);
	BookInfo& operator = (const BookInfo& book_info);

	base_logic::DictionaryValue* Release();

	const int64 id() const {return data_->id_;}
	const int32 type() const {return data_->type_;}
	const int32 parent() const {return data_->parent_;}
	const int64 chapter() const {return data_->chapter_;}
	const int32 attr() const {return data_->attr_;}
	const int64 down() const {return data_->down_;}
	const int64 freecount() const {return data_->free_count_;}
	//const double star() const {return data_->star_;}
	const std::string& free_url() const {return data_->free_url_;}
	const std::string& name() const {return data_->name_;}
	const std::string& author() const {return data_->author_;}
	const std::string& pic() const {return data_->pic_;}
	const std::string& summary() const {return data_->summary_;}
	const std::string& token() const {return data_->token_;}
	const std::string& pubtime() const {return data_->pubtime_;}

	void set_id(const int64 id){data_->id_ = id;}
	void set_type(const int32 type){data_->type_ = type;}
	void set_parent(const int32 parent){data_->parent_ = parent;}
	void set_chapter(const int64 chapter){data_->chapter_ = chapter;}
	void set_attr(const int32 attr){data_->attr_ = attr;}
	void set_down(const int64 down){data_->down_ = down;}
	void set_freecount(const int64 freecount){data_->free_count_ = freecount;}
	//void set_star(const double star){data_->star_ = star;}
	void set_free_url(const std::string& free_url){data_->free_url_ = free_url;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_pic(const std::string& pic){data_->pic_ = pic;}
	void set_author(const std::string& author) {data_->author_ = author;}
	void set_summary(const std::string& summary) {data_->summary_ = summary;}
	void set_token(const std::string& token){data_->token_ = token;}
	void set_pubtime(const std::string& pubtime){data_->pubtime_ = pubtime;}

	class Data{
	public:
		Data()
		:refcount_(1)
		,id_(-1)
		,type_(-1)
		,parent_(-1)
		,chapter_(-1)
		,down_(-1)
		,free_count_(-1)
		,attr_(0){}
	public:
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	public:
		int64        id_;
		int32        type_;
		int32        parent_;
		int64        chapter_;
		int64        down_;
		int64        free_count_;
		int32        attr_;
		std::string  token_;
		std::string  author_;
		std::string  free_url_;
		std::string  name_;
		std::string  pic_;
		std::string  summary_;
		std::string  pubtime_;
	private:
		int refcount_;
	};
	Data*    data_;
};

class Dimension{
public:
	explicit Dimension();
	Dimension(const Dimension& dimension);
	Dimension& operator = (const Dimension& dimension);

	base_logic::DictionaryValue* Release();

	const int64 id() const {return data_->id_;}
	const int32 sid() const {return data_->sid_;}
	const int64 like() const {return data_->like_;}
	const std::string& name() const {return data_->name_;}
	const std::string& logo() const {return data_->logo_;}
	const std::string& dimension() const {return data_->dimension_;}
	const std::string& desc() const {return data_->desc_;}

	void set_id(const int64 id){data_->id_ = id;}
	void set_sid(const int32 sid){data_->sid_ = sid;}
	void set_like(const int64 like){data_->like_ = like;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_logo(const std::string& logo){data_->logo_ = logo;}
	void set_dimension(const std::string& dimension){data_->dimension_ = dimension;}
	void set_desc(const std::string& desc){data_->desc_ = desc;}
private:
	class Data{
	public:
		Data():refcount_(1)
			,id_(0)
			,sid_(0)
			,like_(0){}
	public:
		int64           id_;
		int32           sid_;
		int64           like_;
		std::string     name_;
		std::string     logo_;
		std::string     dimension_;
		std::string     desc_;

		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	private:
		int refcount_;
	};
	Data*    data_;

};
class Movies{
public:
	explicit Movies();
	Movies(const Movies& movies);
	Movies& operator = (const Movies& movies);

	base_logic::DictionaryValue* Release();

	const int64 id() const {return data_->id_;}
	const int32 type() const {return data_->type_;}
	const int64 like() const {return data_->like_;}
	const int64 play_count() const {return data_->play_count_;}
	const double size() const {return data_->size_;}
	const int32 attr() const {return data_->attr_;}
	const std::string& name() const {return data_->name_;}
	const std::string& url() const {return data_->url_;}
	const std::string& logo() const {return data_->logo_;}
	const std::string summary() const {return data_->summary_;}
	const std::string& token() const {return data_->token_;}


	void set_id(const int64 id){data_->id_ = id;}
	void set_type(const int32 type){data_->type_ = type;}
	void set_like(const int64 like){data_->like_ = like;}
	void set_play_count(const int64 play_count){data_->play_count_ = play_count;}
	void set_attr(const int32 attr){data_->attr_ = attr;}
	void set_size(const double size){data_->size_ = size;}
	void set_name(const std::string& name){data_->name_ = name;}
	void set_url(const std::string& url){data_->url_ = url;}
	void set_logo(const std::string& logo) {data_->logo_ = logo;}
	void set_summary(const std::string& summary) {data_->summary_ = summary;}
	void set_token(const std::string& token) {data_->token_ = token;}

private:
	class Data{
	public:
		Data():refcount_(1)
		,id_(0),type_(0),attr_(0)
		,like_(0),size_(0),play_count_(0){}

		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	public:
		int64         		   id_;
		int32                  type_;
		int64		           like_;
		int64                  play_count_;
		int64                  attr_;
		double                 size_;
		std::string    		   name_;
		std::string            url_;
		std::string            logo_;
		std::string            summary_;
		std::string            token_;
	private:
		int refcount_;
	};
	Data*            data_;
};

class LBSInfos{
public:
	explicit LBSInfos();
	explicit LBSInfos(const std::string& host,const double& latitude,
			const double& longitude,const std::string& city,const std::string& district,
			const std::string& province,std::string& street);

	LBSInfos(const LBSInfos& lbs_basic_info);
	LBSInfos& operator = (const LBSInfos& lbs_basic_info);

	const std::string& host() const {return data_->host_;}
	const double latitude() const {return data_->latitude_;}
	const double longitude() const {return data_->longitude_;}
	const std::string& city() const {return data_->city_;}
	const std::string& district() const {return data_->district_;}
	const std::string& province() const {return data_->province_;}
	const std::string& street() const {return data_->street_;}


private:
	class Data{
	public:
		Data():refcount_(1)
		,latitude_(0.0)
		,longitude_(0.0){}

		Data(const std::string& host,const double latitude,
				const double longitude,const std::string& city,const std::string& district,
				const std::string& province,std::string& street)
		:refcount_(1)
		,latitude_(latitude)
		,longitude_(longitude)
		,city_(city)
		,district_(district)
		,province_(province)
		,street_(street){}
		void AddRef(){refcount_ ++;}
		void Release(){if (!--refcount_)delete this;}
	public:
		const std::string host_;
		const double latitude_;
		const double longitude_;
		const std::string city_;
		const std::string district_;
		const std::string province_;
		const std::string street_;
	private:
		int refcount_;
	};
	Data*       data_;
};


}

#endif




