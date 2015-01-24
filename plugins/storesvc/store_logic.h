#ifndef __ABHEG__STORESVC__STORE_LOGIC___
#define __ABHEG__STORESVC__STORE_LOGIC___
#include "common.h"


namespace storesvc_logic{

class Storelogic{

public:
    Storelogic();
    virtual ~Storelogic();

private:
    static Storelogic    *instance_;

public:
    static Storelogic *GetInstance();
    static void FreeInstance();

public:
    bool OnStoreConnect (struct server *srv,const int socket);

    bool OnStoreMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnStoreClose (struct server *srv,const int socket);

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

