#include "movie_logic.h"
#include "db_comm.h"
#include "logic/logic_infos.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
#include "net/movie_comm_head.h"
#include "common.h"

namespace moviessvc_logic{

Movieslogic*
Movieslogic::instance_=NULL;

Movieslogic::Movieslogic(){
   if(!Init())
      assert(0);
}

Movieslogic::~Movieslogic(){
	moviesvc_logic::DBComm::Dest();
}

bool Movieslogic::Init(){
	bool r = false;
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	r = config->LoadConfig(path);

	moviesvc_logic::DBComm::Init(config->mysql_db_list_);
    return true;
}

Movieslogic*
Movieslogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Movieslogic();

    return instance_;
}



void Movieslogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Movieslogic::OnMoviesConnect(struct server *srv,const int socket){

    return true;
}



bool Movieslogic::OnMoviesMessage(struct server *srv, const int socket, const void *msg,const int len){
	const char* packet_stream = (char*)(msg);
	std::string http_str(packet_stream,len);
	std::string error_str;
	int error_code = 0;

	LOG_MSG2("%s",packet_stream);

	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP,&http_str));


	netcomm_recv::NetBase*  value = (netcomm_recv::NetBase*)(serializer.get()->Deserialize(&error_code,&error_str));
	if(value==NULL){
		error_code = STRUCT_ERROR;
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	scoped_ptr<netcomm_recv::HeadPacket> packet(new netcomm_recv::HeadPacket(value));
	int32 type = packet->GetType();
	switch(type){
		case MOVIE_SUMMARY:
			OnMovieSummary(srv,socket,value);
			break;
		case MOVIE_LIKE:
			OnMovieLike(srv,socket,value);
			break;
		case MOVIE_SEARCH_TYPE:
			OnSearchType(srv,socket,value);
			break;
	}

	return true;
}

bool Movieslogic::OnMoviesClose(struct server *srv,const int socket){

    return true;
}



bool Movieslogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Movieslogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Movieslogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Movieslogic::OnIniTimer(struct server *srv){

    return true;
}



bool Movieslogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

bool Movieslogic::OnMovieSummary(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
   		const void* msg,const int len){
	scoped_ptr<netcomm_recv::MovieSummary> rmovie(new netcomm_recv::MovieSummary(netbase));
	bool r = false;
	int error_code = rmovie->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	base_logic::Movies movie;
	base_logic::AdvertInfos advert;
	std::list<base_logic::Movies> list;
	int32 like = 0;
	//读取详情
	r = moviesvc_logic::DBComm::OnGetMovieSummary(rmovie->uid(),rmovie->id(),rmovie->machine(),
			like,movie);
	if(!r)
		return r;
	//关联广告
	r = moviesvc_logic::DBComm::OnGetAboutAdvert(rmovie->id(),movie.type(),advert);
	//相关视频4个
	r = moviesvc_logic::DBComm::OnGetMovieByType(movie.type(),list);
	//发送
	scoped_ptr<netcomm_send::MovieSummary> smovie(new netcomm_send::MovieSummary());
	while(list.size()>0){
		base_logic::Movies movie = list.front();
		list.pop_front();
		smovie->set_movie(movie.Release());
	}
	smovie->set_advert(advert.Release());
	smovie->set_content(movie.summary());
	smovie->set_like(like);
	smovie->set_name(movie.name());
	smovie->set_star(base_logic::LogicUnit::CalculationMovieStar(movie.play_count(),movie.like()));
	smovie->set_url(movie.url());
	send_message(socket,(netcomm_send::HeadPacket*)smovie.get());
	return true;
}

bool Movieslogic::OnMovieLike(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
 		const void* msg,const int len){
	scoped_ptr<netcomm_recv::MovieType> rmovie(new netcomm_recv::MovieType(netbase));
	bool r = false;
	int error_code = rmovie->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	//点赞
	moviesvc_logic::DBComm::OnMovieLike(rmovie->uid(),rmovie->id());
	//发送包头
	scoped_ptr<netcomm_send::HeadPacket> head(new netcomm_send::HeadPacket());
	head->set_status(1);
	send_message(socket,head.get());
	return true;
}

bool Movieslogic::OnSearchType(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
      		const void* msg,const int len){
	scoped_ptr<netcomm_recv::MovieSearchType> rmovie(new netcomm_recv::MovieSearchType(netbase));
	bool r = false;
	int error_code = rmovie->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	std::list<base_logic::Movies> list;
	r = moviesvc_logic::DBComm::OnGetMovieByType(rmovie->tid(),list);
	//发送
	scoped_ptr<netcomm_send::MovieSearch> smovie(new netcomm_send::MovieSearch());
	while(list.size()>0){
		base_logic::Movies movie = list.front();
		list.pop_front();
		if(movie.attr()==1)
			smovie->set_hot(movie.Release());
		else if(movie.attr()==2)
			smovie->set_new(movie.Release());

	}
	send_message(socket,(netcomm_send::HeadPacket*)smovie.get());
	return true;
}

}

