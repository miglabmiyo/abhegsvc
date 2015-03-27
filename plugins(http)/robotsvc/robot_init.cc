#include "robot_init.h"
#include "robot_logic.h"
#include "common.h"
#include "plugins.h"


struct robotplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnRobotStart(){

    signal(SIGPIPE,SIG_IGN);
    struct robotplugin* robot=(struct robotplugin*)calloc(1,sizeof(struct robotplugin));

    robot->id="robot";

    robot->name="robot";

    robot->version="1.0.0";

    robot->provider="kerry";

    if(!robotsvc_logic::Robotlogic::GetInstance())
        assert(0);

    return robot ;

}

static handler_t OnRobotShutdown(struct server* srv,void* pd){

    robotsvc_logic::Robotlogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnRobotConnect(struct server *srv, int fd, void *data, int len){

    robotsvc_logic::Robotlogic::GetInstance()->OnRobotConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnRobotMessage(struct server *srv, int fd, void *data, int len){

    robotsvc_logic::Robotlogic::GetInstance()->OnRobotMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnRobotClose(struct server *srv, int fd){

    robotsvc_logic::Robotlogic::GetInstance()->OnRobotClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    robotsvc_logic::Robotlogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    robotsvc_logic::Robotlogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    robotsvc_logic::Robotlogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    robotsvc_logic::Robotlogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    robotsvc_logic::Robotlogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int robot_plugin_init(struct plugin *pl){


    pl->init=OnRobotStart;

    pl->clean_up = OnRobotShutdown;

    pl->connection = OnRobotConnect;

    pl->connection_close = OnRobotClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnRobotMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

