/*
 * user_basic_info.cc
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#include "store_basic_info.h"
namespace storesvc_logic{

GameStrategy::GameStrategy(){
	data_ = new Data();
}

GameStrategy::GameStrategy(const GameStrategy& strategy)
:data_(strategy.data_){
	if(data_!=NULL){
		data_->AddRef();
	}
}


GameStrategy& GameStrategy::operator =(const GameStrategy& strategy){
	if(strategy.data_!=NULL){
		strategy.data_->AddRef();
	}

	if(data_!=NULL){
		data_->Release();
	}
	data_ = strategy.data_;
	return (*this);
}

base_logic::DictionaryValue* GameStrategy::Release(){
	scoped_ptr<base_logic::DictionaryValue> dict(new base_logic::DictionaryValue());
	if(data_->id_!=0)
		dict->SetBigInteger(L"id",data_->id_);
	if(!data_->name_.empty())
		dict->SetString(L"name",data_->name_);
	if(!data_->details_.empty())
		dict->SetString(L"details",data_->details_);
	if(!data_->address_.empty())
		dict->SetString(L"address",data_->address_);
	return dict.release();
}

}
