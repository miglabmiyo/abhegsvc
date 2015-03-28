#include "movie_init.h"
#include "movie_logic.h"
#include "common.h"
#include "plugins.h"


struct movieplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnMovieStart(){

    signal(SIGPIPE,SIG_IGN);
    struct movieplugin* movies=(struct movieplugin*)calloc(1,sizeof(struct movieplugin));

    movies->id="movie";

    movies->name="movie";

    movies->version="1.0";

    movies->provider="kerry";

    if(!moviessvc_logic::Movieslogic::GetInstance())
        assert(0);

    return movies ;

}

static handler_t OnMovieShutdown(struct server* srv,void* pd){

    moviessvc_logic::Movieslogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnMovieConnect(struct server *srv, int fd, void *data, int len){

    moviessvc_logic::Movieslogic::GetInstance()->OnMoviesConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnMovieMessage(struct server *srv, int fd, void *data, int len){

    moviessvc_logic::Movieslogic::GetInstance()->OnMoviesMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnMovieClose(struct server *srv, int fd){

    moviessvc_logic::Movieslogic::GetInstance()->OnMoviesClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    moviessvc_logic::Movieslogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    moviessvc_logic::Movieslogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    moviessvc_logic::Movieslogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    moviessvc_logic::Movieslogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    moviessvc_logic::Movieslogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int movie_plugin_init(struct plugin *pl){


    pl->init=OnMovieStart;

    pl->clean_up = OnMovieShutdown;

    pl->connection = OnMovieConnect;

    pl->connection_close = OnMovieClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnMovieMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

