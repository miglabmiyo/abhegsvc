/*
 * db_comm.h
 *
 *  Created on: 2014年12月4日
 *      Author: kerry
 */
#ifndef __ABHEG__FINDSVC__DB_COMM___
#define __ABHEG__FINDSVC__DB_COMM___
//#include "user_basic_info.h"
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace findsvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();
public:

	static bool GetFindApp(std::list<base_logic::AppInfos>& list);
	static bool GetFindBook(std::list<base_logic::BookInfo>& list);
	static bool GetFindGame(std::list<base_logic::AppInfos>& list);
	static bool GetFindMovie(std::list<base_logic::Movies>& list);

	static bool GetAdver(std::list<base_logic::AdvertInfos>& list);

	static bool GetFindStoreApp(std::list<base_logic::AppInfos>& list);
	static bool GetAdverAppStore(std::list<base_logic::AdvertInfos>& list);
	static bool GetTopicsAppStore(std::list<base_logic::Topics>& list);

	static bool GetFindGameRank(std::list<base_logic::AppInfos>& list);
	static bool GetFindAppRank(std::list<base_logic::AppInfos>& list);

	static bool GetFindStoreBook(std::list<base_logic::BookInfo>& list);
	static bool GetAdverBookStore(std::list<base_logic::AdvertInfos>& list);
	static bool GetTopicsBookStore(std::list<base_logic::Topics>& list);

	static bool GetFindStoreGame(std::list<base_logic::AppInfos>& list);
	static bool GetFindEmblemStore(base_logic::AppInfos& app);
	static bool GetAdverGameStore(std::list<base_logic::AdvertInfos>& list);

	static bool GetAdverMoviesStore(std::list<base_logic::AdvertInfos>& list);
	static bool GetFindStoreMovies(std::list<base_logic::Movies>& list);
};

}
#endif


