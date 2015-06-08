#ifndef __REDIRECT__CRAWLERSVC__CRAWLER_LOGIC___
#define __REDIRECT__CRAWLERSVC__CRAWLER_LOGIC___
#include "appstore_engine.h"
#include "basic/scoped_ptr.h"
#include "common.h"


#define DEFAULT_CONFIG_PATH     "./plugins/crawlersvc/crawlersvc_config.xml";

namespace crawlersvc_logic{

class Crawlerlogic{

public:
    Crawlerlogic();
    virtual ~Crawlerlogic();

private:
    static Crawlerlogic    *instance_;

public:
    static Crawlerlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnCrawlerConnect (struct server *srv,const int socket);

    bool OnCrawlerMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnCrawlerClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    void OnTaskStar();
private:

    bool Init();
private:
    scoped_ptr<crawlersvc_logic::AppStoreEngine>               wandoujia_engine_;
};


}

#endif

