#include "pay_init.h"
#include "pay_logic.h"
#include "common.h"
#include "plugins.h"


struct payplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnPayStart(){

    signal(SIGPIPE,SIG_IGN);
    struct payplugin* pay=(struct payplugin*)calloc(1,sizeof(struct payplugin));

    pay->id="pay";

    pay->name="pay";

    pay->version="1.0.0";

    pay->provider="kerry";

    if(!paysvc_logic::Paylogic::GetInstance())
        assert(0);

    return pay ;

}

static handler_t OnPayShutdown(struct server* srv,void* pd){

    paysvc_logic::Paylogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnPayConnect(struct server *srv, int fd, void *data, int len){

    paysvc_logic::Paylogic::GetInstance()->OnPayConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnPayMessage(struct server *srv, int fd, void *data, int len){

    paysvc_logic::Paylogic::GetInstance()->OnPayMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnPayClose(struct server *srv, int fd){

    paysvc_logic::Paylogic::GetInstance()->OnPayClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    paysvc_logic::Paylogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    paysvc_logic::Paylogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    paysvc_logic::Paylogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    paysvc_logic::Paylogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    paysvc_logic::Paylogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int pay_plugin_init(struct plugin *pl){


    pl->init=OnPayStart;

    pl->clean_up = OnPayShutdown;

    pl->connection = OnPayConnect;

    pl->connection_close = OnPayClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnPayMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

