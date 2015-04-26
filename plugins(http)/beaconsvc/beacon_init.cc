#include "beacon_init.h"
#include "beacon_logic.h"
#include "common.h"
#include "plugins.h"


struct beaconplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnBeaconStart(){

    signal(SIGPIPE,SIG_IGN);
    struct beaconplugin* beacon=(struct beaconplugin*)calloc(1,sizeof(struct beaconplugin));

    beacon->id="beacon";

    beacon->name="beacon";

    beacon->version="1.0.0";

    beacon->provider="kerry";

    if(!beaconsvc_logic::Beaconlogic::GetInstance())
        assert(0);

    return beacon ;

}

static handler_t OnBeaconShutdown(struct server* srv,void* pd){

    beaconsvc_logic::Beaconlogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnBeaconConnect(struct server *srv, int fd, void *data, int len){

    beaconsvc_logic::Beaconlogic::GetInstance()->OnBeaconConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnBeaconMessage(struct server *srv, int fd, void *data, int len){

    beaconsvc_logic::Beaconlogic::GetInstance()->OnBeaconMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnBeaconClose(struct server *srv, int fd){

    beaconsvc_logic::Beaconlogic::GetInstance()->OnBeaconClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    beaconsvc_logic::Beaconlogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    beaconsvc_logic::Beaconlogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    beaconsvc_logic::Beaconlogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    beaconsvc_logic::Beaconlogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    beaconsvc_logic::Beaconlogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int beacon_plugin_init(struct plugin *pl){


    pl->init=OnBeaconStart;

    pl->clean_up = OnBeaconShutdown;

    pl->connection = OnBeaconConnect;

    pl->connection_close = OnBeaconClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnBeaconMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

