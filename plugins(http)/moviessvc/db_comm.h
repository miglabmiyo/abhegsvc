/*
 * db_comm.h
 *
 *  Created on: 2015年3月27日
 *      Author: pro
 */

#ifndef MOVIE_DB_COMM_H_
#define MOVIE_DB_COMM_H_
#include "logic/logic_infos.h"
#include "config/config.h"
#include <list>
namespace moviesvc_logic{

class DBComm{
public:
	DBComm();
	virtual ~DBComm();
public:
	static void Init(std::list<base::ConnAddr>& addrlist);
	static void Dest();
public:
	static bool OnGetMovieSummary(const int64 uid,const int64 moiveid,const int32 machine,
			int32& like,base_logic::Movies& movie);

	static bool OnGetMovieByType(const int32 type,std::list<base_logic::Movies>& list);

	static bool OnGetAboutAdvert(const int64 movieid,const int32 type,
			base_logic::AdvertInfos& advert);

	static bool OnMovieLike(const int64 uid,const int64 movieid);
};


}




#endif /* DB_COMM_H_ */
