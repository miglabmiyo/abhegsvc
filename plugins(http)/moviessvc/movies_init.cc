#include "movies_init.h"
#include "movies_logic.h"
#include "common.h"
#include "plugins.h"


struct moviesplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnMoviesStart(){

    signal(SIGPIPE,SIG_IGN);
    struct moviesplugin* movies=(struct moviesplugin*)calloc(1,sizeof(struct moviesplugin));

    movies->id="movies";

    movies->name="movies";

    movies->version="1.0";

    movies->provider="kerry";

    if(!moviessvc_logic::Movieslogic::GetInstance())
        assert(0);

    return movies ;

}

static handler_t OnMoviesShutdown(struct server* srv,void* pd){

    moviessvc_logic::Movieslogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnMoviesConnect(struct server *srv, int fd, void *data, int len){

    moviessvc_logic::Movieslogic::GetInstance()->OnMoviesConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnMoviesMessage(struct server *srv, int fd, void *data, int len){

    moviessvc_logic::Movieslogic::GetInstance()->OnMoviesMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnMoviesClose(struct server *srv, int fd){

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






int movies_plugin_init(struct plugin *pl){


    pl->init=OnMoviesStart;

    pl->clean_up = OnMoviesShutdown;

    pl->connection = OnMoviesConnect;

    pl->connection_close = OnMoviesClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnMoviesMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

