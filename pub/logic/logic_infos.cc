/*
 * logic_infos.cc
 *
 *  Created on: 2014年12月2日
 *      Author: kerry
 */
#include "logic/logic_infos.h"

namespace base_logic{

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



