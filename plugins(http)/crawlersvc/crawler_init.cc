#include "crawler_init.h"
#include "crawler_logic.h"
#include "common.h"
#include "plugins.h"


struct crawlerplugin{
    char* id;
    char* name;
    char* version;
    char* provider;
};


static void *OnCrawlerStart(){

    signal(SIGPIPE,SIG_IGN);
    struct crawlerplugin* crawler=(struct crawlerplugin*)calloc(1,sizeof(struct crawlerplugin));

    crawler->id="crawler";

    crawler->name="crawler";

    crawler->version="1.0.0";

    crawler->provider="kerry";

    if(!crawlersvc_logic::Crawlerlogic::GetInstance())
        assert(0);

    return crawler ;

}

static handler_t OnCrawlerShutdown(struct server* srv,void* pd){

    crawlersvc_logic::Crawlerlogic::FreeInstance();

    return HANDLER_GO_ON;
}

static handler_t OnCrawlerConnect(struct server *srv, int fd, void *data, int len){

    crawlersvc_logic::Crawlerlogic::GetInstance()->OnCrawlerConnect(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnCrawlerMessage(struct server *srv, int fd, void *data, int len){

    crawlersvc_logic::Crawlerlogic::GetInstance()->OnCrawlerMessage(srv,fd,data,len);

    return HANDLER_GO_ON;
}

static handler_t OnCrawlerClose(struct server *srv, int fd){

    crawlersvc_logic::Crawlerlogic::GetInstance()->OnCrawlerClose(srv,fd);

    return HANDLER_GO_ON;
}

static handler_t OnUnknow(struct server *srv, int fd, void *data, int len){


    return HANDLER_GO_ON;

}

static handler_t OnBroadcastConnect(struct server* srv, int fd, void *data, int len){


    crawlersvc_logic::Crawlerlogic::GetInstance()->OnBroadcastConnect(srv,fd,data,len);

    return HANDLER_GO_ON;

}

static handler_t OnBroadcastClose(struct server* srv, int fd){ 


    crawlersvc_logic::Crawlerlogic::GetInstance()->OnBroadcastClose(srv,fd);

    return HANDLER_GO_ON;


}

static handler_t OnBroadcastMessage(struct server* srv, int fd, void *data, int len){


    crawlersvc_logic::Crawlerlogic::GetInstance()->OnBroadcastMessage(srv,fd,data,len);

    return HANDLER_GO_ON;


}

static handler_t OnIniTimer(struct server* srv){ 


    crawlersvc_logic::Crawlerlogic::GetInstance()->OnIniTimer(srv);

    return HANDLER_GO_ON;


}

static handler_t OnTimeOut(struct server* srv,char* id, int opcode, int time){ 


    crawlersvc_logic::Crawlerlogic::GetInstance()->OnTimeout(srv,id,opcode,time);

    return HANDLER_GO_ON;


}






int crawler_plugin_init(struct plugin *pl){


    pl->init=OnCrawlerStart;

    pl->clean_up = OnCrawlerShutdown;

    pl->connection = OnCrawlerConnect;

    pl->connection_close = OnCrawlerClose;

    pl->connection_close_srv = OnBroadcastClose;

    pl->connection_srv = OnBroadcastConnect;

    pl->handler_init_time = OnIniTimer;

    pl->handler_read = OnCrawlerMessage;

    pl->handler_read_srv = OnBroadcastMessage;

    pl->handler_read_other = OnUnknow;

    pl->time_msg = OnTimeOut;

    pl->data = NULL;

    return 0;

}

