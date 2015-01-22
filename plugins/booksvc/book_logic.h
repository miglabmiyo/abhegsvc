#ifndef __ABHEG__BOOKSVC__BOOK_LOGIC___
#define __ABHEG__BOOKSVC__BOOK_LOGIC___
#include "common.h"


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

    bool Init();
};


}

#endif

