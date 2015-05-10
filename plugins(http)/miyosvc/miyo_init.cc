#include "miyo_init.h"
#include "miyo_logic.h"
#include "common.h"
#include "plugins.h"


struct miyoplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnMiyoStart(){

    signal(SIGPIPE,SIG_IGN);
    struct miyoplugin* miyo=(struct miyoplugin*)calloc(1,sizeof(struct miyoplugin));

    miyo->id="miyo";

    miyo->name="miyo";

    miyo->version="1.0.0";

    miyo->provider="kerry";

    if(!miyosvc_logic::Miyologic::GetInstance())
        assert(0);

    return miyo ;

}

static handler_t OnMiyoShutdown(struct server* srv,void* pd){

    miyosvc_logic::Miyologic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnMiyoConnect(struct server *srv, int fd, void *data, int len){

    miyosvc_logic::Miyologic::GetInstance()->OnMiyoConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnMiyoMessage(struct server *srv, int fd, void *data, int len){

    miyosvc_logic::Miyologic::GetInstance()->OnMiyoMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnMiyoClose(struct server *srv, int fd){

    miyosvc_logic::Miyologic::GetInstance()->OnMiyoClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    miyosvc_logic::Miyologic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    miyosvc_logic::Miyologic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    miyosvc_logic::Miyologic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    miyosvc_logic::Miyologic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    miyosvc_logic::Miyologic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int miyo_plugin_init(struct plugin *pl){


    pl->init=OnMiyoStart;

    pl->clean_up = OnMiyoShutdown;

    pl->connection = OnMiyoConnect;

    pl->connection_close = OnMiyoClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnMiyoMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

