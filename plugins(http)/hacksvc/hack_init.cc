#include "hack_init.h"
#include "hack_logic.h"
#include "common.h"
#include "plugins.h"


struct hackplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnHackStart(){

    signal(SIGPIPE,SIG_IGN);
    struct hackplugin* hack=(struct hackplugin*)calloc(1,sizeof(struct hackplugin));

    hack->id="hack";

    hack->name="hack";

    hack->version="1.0.0";

    hack->provider="kerry";

    if(!hacksvc_logic::Hacklogic::GetInstance())
        assert(0);

    return hack ;

}

static handler_t OnHackShutdown(struct server* srv,void* pd){

    hacksvc_logic::Hacklogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnHackConnect(struct server *srv, int fd, void *data, int len){

    hacksvc_logic::Hacklogic::GetInstance()->OnHackConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnHackMessage(struct server *srv, int fd, void *data, int len){

    hacksvc_logic::Hacklogic::GetInstance()->OnHackMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnHackClose(struct server *srv, int fd){

    hacksvc_logic::Hacklogic::GetInstance()->OnHackClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    hacksvc_logic::Hacklogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    hacksvc_logic::Hacklogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    hacksvc_logic::Hacklogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    hacksvc_logic::Hacklogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    hacksvc_logic::Hacklogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int hack_plugin_init(struct plugin *pl){


    pl->init=OnHackStart;

    pl->clean_up = OnHackShutdown;

    pl->connection = OnHackConnect;

    pl->connection_close = OnHackClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnHackMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

