/*
 * db_comm.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#ifndef __ABHEG__BOOK__DB_COMM___
#define __ABHEG__BOOK__DB_COMM___
#include "book_basic_info.h"
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace booksvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();

public:
	static bool GetBookTopics(const int64 tid,std::list<base_logic::BookInfo>& list);

	static bool GetBookSearch(const int32 type,std::list<base_logic::BookInfo>& list);

	static bool OnWantGetBook(const int64 uid,const int64 bid,const std::string& token);

	//获取书单
	static bool OnGetBookList(const int64 uid,std::list<base_logic::BookInfo>& list);

	//
	static bool OnGetBookComInfo(const int64 bookid,base_logic::BookInfo& bookinfo);

	//详情
	static bool OnGetBookSummary(const int64 uid,const int64 bookid,int32& issave,
			base_logic::BookInfo& bookinfo);


	static bool OnGetBookChapters(const int64 uid,const int64 bid,const std::string& token,
			const int64 from,const int64 count,
			std::list<booksvc_logic::ChapterInfo>& list);

};

}
#endif


