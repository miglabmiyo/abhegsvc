#include "extension_init.h"
#include "extension_logic.h"
#include "common.h"
#include "plugins.h"


struct extensionplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnExtensionStart(){

    signal(SIGPIPE,SIG_IGN);
    struct extensionplugin* extension=(struct extensionplugin*)calloc(1,sizeof(struct extensionplugin));

    extension->id="";

    extension->name="";

    extension->version="";

    extension->provider="";

    if(!extensionsvc_logic::Extensionlogic::GetInstance())
        assert(0);

    return extension ;

}

static handler_t OnExtensionShutdown(struct server* srv,void* pd){

    extensionsvc_logic::Extensionlogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnExtensionConnect(struct server *srv, int fd, void *data, int len){

    extensionsvc_logic::Extensionlogic::GetInstance()->OnExtensionConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnExtensionMessage(struct server *srv, int fd, void *data, int len){

    extensionsvc_logic::Extensionlogic::GetInstance()->OnExtensionMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnExtensionClose(struct server *srv, int fd){

    extensionsvc_logic::Extensionlogic::GetInstance()->OnExtensionClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    extensionsvc_logic::Extensionlogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    extensionsvc_logic::Extensionlogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    extensionsvc_logic::Extensionlogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    extensionsvc_logic::Extensionlogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    extensionsvc_logic::Extensionlogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int extension_plugin_init(struct plugin *pl){


    pl->init=OnExtensionStart;

    pl->clean_up = OnExtensionShutdown;

    pl->connection = OnExtensionConnect;

    pl->connection_close = OnExtensionClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnExtensionMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

