/*
 * logic_infos.cc
 *
 *  Created on: 2014年12月2日
 *      Author: kerry
 */
#include "logic/logic_infos.h"
#include "logic/logic_unit.h"

namespace base_logic{

AdvertInfos::AdvertInfos(){
	data_ = new Data();
}

AdvertInfos::AdvertInfos(const AdvertInfos& advertinfo)
:data_(advertinfo.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

AdvertInfos& AdvertInfos::operator =(const AdvertInfos& advertinfo){
	if(advertinfo.data_!=NULL){
		advertinfo.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = advertinfo.data_;
	return (*this);
}

base_logic::DictionaryValue* AdvertInfos::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=-1)
		dict->SetBigInteger(L"id",data_->id_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(data_->type_!=-1)
		dict->SetInteger(L"type",data_->type_);
	if(data_->subtype_!=-1)
		dict->SetInteger(L"subtype",data_->subtype_);
	if(!data_->pic_.empty())
		dict->SetString(L"pic",data_->pic_);
	return dict.release();
}

Topics::Topics(){
	data_ = new Data();
}


Topics::Topics(const Topics& topics)
:data_(topics.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

Topics& Topics::operator =(const Topics& topics){
	if(topics.data_!=NULL){
		topics.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = topics.data_;
	return (*this);
}

base_logic::DictionaryValue* Topics::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=0)
		dict->SetBigInteger(L"id",data_->id_);
	if(data_->follower_!=-1)
		dict->SetBigInteger(L"follow",data_->follower_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(!data_->pic_.empty())
		dict->SetString(L"pic",data_->pic_);

	return dict.release();
}

bool set_pic_release(scoped_ptr<base_logic::ListValue>& pic_list,
		std::list<std::string>& list){
	if(list.size()<=0)
		return false;
	std::list<std::string>::iterator it = list.begin();
	for(;it!=list.end();++it){
		std::string pic = (*it);
		pic_list->Append(base_logic::Value::CreateStringValue(pic));
	}
	return true;
}

AppInfos::AppInfos(){
	data_ = new Data();
}


AppInfos::AppInfos(const AppInfos& appinfo)
:data_(appinfo.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

AppInfos& AppInfos::operator =(const AppInfos& appinfo){
	if(appinfo.data_!=NULL){
		appinfo.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = appinfo.data_;
	return (*this);
}


base_logic::DictionaryValue* AppInfos::Release(bool summary){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=-1)
		dict->SetBigInteger(L"id",data_->id_);
	if(data_->type_!=-1)
		dict->SetInteger(L"type",data_->type_);
	if(data_->down_!=-1)
		dict->SetBigInteger(L"down",data_->down_);
	if(data_->like_!=-1)
		dict->SetBigInteger(L"like",data_->like_);
	if(data_->lang_!=-1)
		dict->SetInteger(L"lang",data_->lang_);
	if(data_->size_!=0.0)
		dict->SetReal(L"size",data_->size_);
	if(!data_->ios_url_.empty())
		dict->SetString(L"ios_url",data_->ios_url_);
	if(!data_->android_url_.empty())
		dict->SetString(L"android_url",data_->android_url_);
	if(!data_->provider_.empty())
		dict->SetString(L"provider",data_->provider_);
	if(!data_->version_.empty())
		dict->SetString(L"version",data_->version_);
	if(!data_->ontime_.empty())
		dict->SetString(L"ontime",data_->ontime_);
	if(!data_->logo_.empty())
		dict->SetString(L"logo",data_->logo_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(!data_->summary_.empty())
		dict->SetString(L"summary",data_->summary_);
	if(!data_->content_.empty())
		dict->SetString(L"summary",data_->content_);
	if(data_->like_!=-1&&data_->down_!=-1)
		dict->SetReal(L"star",base_logic::LogicUnit::CalculationAppStar(data_->down_,data_->like_));

	bool r = false;
	scoped_ptr<base_logic::ListValue> pic;
	pic.reset(new base_logic::ListValue());

	if(summary)
		r = set_pic_release(pic,data_->summary_pic_list_);
	else
		r = set_pic_release(pic,data_->emblem_pic_list_);

	if(r)
		dict->SetWithoutPathExpansion(L"pic",pic.release());
	return dict.release();
}

bool AppInfos::cmp(AppInfos& t_info,AppInfos& r_info){ //按照星级排序
	double t_star = base_logic::LogicUnit::CalculationAppStar(t_info.down(),t_info.like());
	double r_star = base_logic::LogicUnit::CalculationAppStar(r_info.down(),r_info.like());
	return t_star < r_star;
}

BookInfo::BookInfo(){
	data_ = new Data();
}

BookInfo::BookInfo(const BookInfo& book_info)
:data_(book_info.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

BookInfo& BookInfo::operator =(const BookInfo& book_info){
	if(book_info.data_!=NULL){
		book_info.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = book_info.data_;
	return (*this);
}


base_logic::DictionaryValue* BookInfo::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=-1)
		dict->SetBigInteger(L"id",data_->id_);
	if(data_->type_ != -1)
		dict->SetInteger(L"type",data_->type_);
	if(data_->chapter_!=-1)
		dict->SetBigInteger(L"chapter",data_->chapter_);
	if(data_->free_count_!=-1&&data_->down_!=-1)
		dict->SetReal(L"star",base_logic::LogicUnit::CalculationBookStar(data_->free_count_,data_->down_));
	//if(data_->star_!=0.0)
		//dict->SetReal(L"star",4.5);

	if(data_->down_!=-1)
		dict->SetBigInteger(L"down",data_->down_);

	if(!data_->free_url_.empty())
		dict->SetString(L"free_url",data_->free_url_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(!data_->pic_.empty())
		dict->SetString(L"pic",data_->pic_);
	if(!data_->summary_.empty())
		dict->SetString(L"summary",data_->summary_);
	if(!data_->author_.empty())
		dict->SetString(L"author",data_->author_);
	if(!data_->token_.empty()){
		dict->SetString(L"token",data_->token_);
		dict->SetString(L"booktoken",data_->token_);
	}
	if(!data_->pubtime_.empty())
		dict->SetString(L"pubtime",data_->pubtime_);

	return dict.release();

}

Movies::Movies(){
	data_ = new Data();
}

Movies::Movies(const Movies& movies)
:data_(movies.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

Movies& Movies::operator =(const Movies& movies){
	if(movies.data_!=NULL){
		movies.data_->AddRef();
	}
	if(data_!=NULL){
		data_->Release();
	}

	data_ = movies.data_;
	return (*this);
}

base_logic::DictionaryValue* Movies::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=0)
		dict->SetBigInteger(L"id",data_->id_);
	if(data_->type_!=0)
		dict->SetInteger(L"type",data_->type_);
	if(data_->like_!=0)
		dict->SetBigInteger(L"like",data_->like_);
	if(data_->play_count_!=0)
		dict->SetBigInteger(L"play",data_->play_count_);
	if(data_->size_!=0)
		dict->SetReal(L"size",data_->size_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(!data_->url_.empty())
		dict->SetString(L"url",data_->url_);
	if(!data_->logo_.empty()){
		dict->SetString(L"pic",data_->logo_);
		dict->SetString(L"logo",data_->logo_);
	}
	if(!data_->summary_.empty())
		dict->SetString(L"summary",data_->summary_);
	if(data_->like_!=0&&data_->play_count_!=0)
		dict->SetBigInteger(L"star",base_logic::LogicUnit::CalculationMovieStar(data_->play_count_,data_->like_));
	else
		dict->SetBigInteger(L"star",0.0);
	return dict.release();
}

LBSInfos::LBSInfos(){
	data_ = new Data();
}

LBSInfos::LBSInfos(const std::string& host,const double& latitude,
			const double& longitude,const std::string& city,const std::string& district,
			const std::string& province,std::string& street){
	data_ = new Data(host,latitude,longitude,city,district,province,street);
}

LBSInfos::LBSInfos(const LBSInfos& lbs_basic_info)
:data_(lbs_basic_info.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}

LBSInfos& LBSInfos::operator =(const LBSInfos& lbs_basic_info){
	if(lbs_basic_info.data_!=NULL){
		lbs_basic_info.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = lbs_basic_info.data_;
	return (*this);
}


}



