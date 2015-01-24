#include "store_init.h"
#include "store_logic.h"
#include "common.h"
#include "plugins.h"


struct storeplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnStoreStart(){

    signal(SIGPIPE,SIG_IGN);
    struct storeplugin* store=(struct storeplugin*)calloc(1,sizeof(struct storeplugin));

    store->id="";

    store->name="";

    store->version="";

    store->provider="";

    if(!storesvc_logic::Storelogic::GetInstance())
        assert(0);

    return store ;

}

static handler_t OnStoreShutdown(struct server* srv,void* pd){

    storesvc_logic::Storelogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnStoreConnect(struct server *srv, int fd, void *data, int len){

    storesvc_logic::Storelogic::GetInstance()->OnStoreConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnStoreMessage(struct server *srv, int fd, void *data, int len){

    storesvc_logic::Storelogic::GetInstance()->OnStoreMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnStoreClose(struct server *srv, int fd){

    storesvc_logic::Storelogic::GetInstance()->OnStoreClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    storesvc_logic::Storelogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    storesvc_logic::Storelogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    storesvc_logic::Storelogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    storesvc_logic::Storelogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    storesvc_logic::Storelogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int store_plugin_init(struct plugin *pl){


    pl->init=OnStoreStart;

    pl->clean_up = OnStoreShutdown;

    pl->connection = OnStoreConnect;

    pl->connection_close = OnStoreClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnStoreMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

