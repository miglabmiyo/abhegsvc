#include "book_init.h"
#include "book_logic.h"
#include "common.h"
#include "plugins.h"


struct bookplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnBookStart(){

    signal(SIGPIPE,SIG_IGN);
    struct bookplugin* book=(struct bookplugin*)calloc(1,sizeof(struct bookplugin));

    book->id="book";

    book->name="book";

    book->version="1.0.0";

    book->provider="kerry";

    if(!booksvc_logic::Booklogic::GetInstance())
        assert(0);

    return book ;

}

static handler_t OnBookShutdown(struct server* srv,void* pd){

    booksvc_logic::Booklogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnBookConnect(struct server *srv, int fd, void *data, int len){

    booksvc_logic::Booklogic::GetInstance()->OnBookConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnBookMessage(struct server *srv, int fd, void *data, int len){

    booksvc_logic::Booklogic::GetInstance()->OnBookMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnBookClose(struct server *srv, int fd){

    booksvc_logic::Booklogic::GetInstance()->OnBookClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    booksvc_logic::Booklogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    booksvc_logic::Booklogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    booksvc_logic::Booklogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    booksvc_logic::Booklogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    booksvc_logic::Booklogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int book_plugin_init(struct plugin *pl){


    pl->init=OnBookStart;

    pl->clean_up = OnBookShutdown;

    pl->connection = OnBookConnect;

    pl->connection_close = OnBookClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnBookMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

