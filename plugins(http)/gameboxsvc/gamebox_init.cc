#include "gamebox_init.h"
#include "gamebox_logic.h"
#include "common.h"
#include "plugins.h"


struct gameboxplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnGameboxStart(){

    signal(SIGPIPE,SIG_IGN);
    struct gameboxplugin* gamebox=(struct gameboxplugin*)calloc(1,sizeof(struct gameboxplugin));

    gamebox->id="gamebox";

    gamebox->name="gamebox";

    gamebox->version="1.0.0";

    gamebox->provider="kerry";

    if(!gameboxsvc_logic::Gameboxlogic::GetInstance())
        assert(0);

    return gamebox ;

}

static handler_t OnGameboxShutdown(struct server* srv,void* pd){

    gameboxsvc_logic::Gameboxlogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnGameboxConnect(struct server *srv, int fd, void *data, int len){

    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnGameboxConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnGameboxMessage(struct server *srv, int fd, void *data, int len){

    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnGameboxMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnGameboxClose(struct server *srv, int fd){

    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnGameboxClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    gameboxsvc_logic::Gameboxlogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int gamebox_plugin_init(struct plugin *pl){


    pl->init=OnGameboxStart;

    pl->clean_up = OnGameboxShutdown;

    pl->connection = OnGameboxConnect;

    pl->connection_close = OnGameboxClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnGameboxMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

