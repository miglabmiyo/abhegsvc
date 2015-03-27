#include "wifi_init.h"
#include "wifi_logic.h"
#include "common.h"
#include "plugins.h"


struct wifiplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnWifiStart(){

    signal(SIGPIPE,SIG_IGN);
    struct wifiplugin* wifi=(struct wifiplugin*)calloc(1,sizeof(struct wifiplugin));

    wifi->id="";

    wifi->name="";

    wifi->version="";

    wifi->provider="";

    if(!wifisvc_logic::Wifilogic::GetInstance())
        assert(0);

    return wifi ;

}

static handler_t OnWifiShutdown(struct server* srv,void* pd){

    wifisvc_logic::Wifilogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnWifiConnect(struct server *srv, int fd, void *data, int len){

    wifisvc_logic::Wifilogic::GetInstance()->OnWifiConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnWifiMessage(struct server *srv, int fd, void *data, int len){

    wifisvc_logic::Wifilogic::GetInstance()->OnWifiMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnWifiClose(struct server *srv, int fd){

    wifisvc_logic::Wifilogic::GetInstance()->OnWifiClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    wifisvc_logic::Wifilogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    wifisvc_logic::Wifilogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    wifisvc_logic::Wifilogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    wifisvc_logic::Wifilogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    wifisvc_logic::Wifilogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int wifi_plugin_init(struct plugin *pl){


    pl->init=OnWifiStart;

    pl->clean_up = OnWifiShutdown;

    pl->connection = OnWifiConnect;

    pl->connection_close = OnWifiClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnWifiMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

