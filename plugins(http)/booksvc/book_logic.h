#ifndef __ABHEG__BOOKSVC__BOOK_LOGIC___
#define __ABHEG__BOOKSVC__BOOK_LOGIC___
#include "net/book_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/booksvc/booksvc_config.xml"


namespace booksvc_logic{

class Booklogic{

public:
    Booklogic();
    virtual ~Booklogic();

private:
    static Booklogic    *instance_;

public:
    static Booklogic *GetInstance();
    static void FreeInstance();

public:
    bool OnBookConnect (struct server *srv,const int socket);

    bool OnBookMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnBookClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    bool OnBookTopics(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnBookSearchType(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
        		const void* msg = NULL,const int len = 0);

    bool OnBookSearchKey(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnWantGetBook(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnUserBookList(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
       		const void* msg = NULL,const int len = 0);

    bool OnGetBookChapters(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnGetBookSummary(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnGetBookComplInfo(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);
private:

    bool Init();
};


}

#endif

