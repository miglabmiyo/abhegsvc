#include "find_init.h"
#include "find_logic.h"
#include "common.h"
#include "plugins.h"


struct findplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnFindStart(){

    signal(SIGPIPE,SIG_IGN);
    struct findplugin* find=(struct findplugin*)calloc(1,sizeof(struct findplugin));

    find->id="find";

    find->name="find";

    find->version="1.0.0";

    find->provider="kerry";

    if(!findsvc_logic::Findlogic::GetInstance())
        assert(0);

    return find ;

}

static handler_t OnFindShutdown(struct server* srv,void* pd){

    findsvc_logic::Findlogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnFindConnect(struct server *srv, int fd, void *data, int len){

    findsvc_logic::Findlogic::GetInstance()->OnFindConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnFindMessage(struct server *srv, int fd, void *data, int len){

    findsvc_logic::Findlogic::GetInstance()->OnFindMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnFindClose(struct server *srv, int fd){

    findsvc_logic::Findlogic::GetInstance()->OnFindClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    findsvc_logic::Findlogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    findsvc_logic::Findlogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    findsvc_logic::Findlogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    findsvc_logic::Findlogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    findsvc_logic::Findlogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int find_plugin_init(struct plugin *pl){


    pl->init=OnFindStart;

    pl->clean_up = OnFindShutdown;

    pl->connection = OnFindConnect;

    pl->connection_close = OnFindClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnFindMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

