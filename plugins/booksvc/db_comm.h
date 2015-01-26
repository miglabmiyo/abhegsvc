/*
 * db_comm.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#ifndef __ABHEG__BOOK__DB_COMM___
#define __ABHEG__BOOK__DB_COMM___
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

};

}
#endif


