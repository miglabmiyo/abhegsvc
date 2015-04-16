/*
 * hack_basic_info.h
 *
 *  Created on: 2015年4月16日
 *      Author: kerry
 */

#ifndef HACK_BASIC_INFO_H_
#define HACK_BASIC_INFO_H_
#include <string>
namespace hacksvc_logic{

class AppSummaryParam{
public:
	explicit AppSummaryParam();
	AppSummaryParam(const AppSummaryParam& param);

	AppSummaryParam& operator = (const AppSummaryParam& param);

	const void set_pnname(const std::string& pnname){data_->pnname_ = pnname;}


	const std::string& pnname() const {return data_->pnname_;}

private:
	class Data{
	public:
		Data()
			:refcount_(1){}
	public:
		std::string  pnname_;
		void AddRef() {refcount_++;}
		void Release() {if(!--refcount_) delete this;}
	private:
		int refcount_;
	};

	Data*    data_;
};

}



#endif /* HACK_BASIC_INFO_H_ */
