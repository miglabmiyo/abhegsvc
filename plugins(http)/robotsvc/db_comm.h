/*
 * db_comm.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#ifndef __BUDDHA__ROBOTSVC__DB_COMM___
#define __BUDDHA__ROBOTSVC__DB_COMM___
#include "robot_basic_info.h"
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace robotsvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();

	//获取更新的电影
	static bool GainMovie(const int64 from,const int32 count,
			std::list<base_logic::Movies>& list);
	//批量写入小说
	static bool CollectionBookChapter(std::list<BookChapterCollection>& list);

	//批量写入小说的信息
	static bool CollectionBookInfo(std::list<BookInfo>& list);

	//获取爬虫电信号码
	static bool GetCTPhoneNumber(std::list<std::string>& list);
};

}

#endif

