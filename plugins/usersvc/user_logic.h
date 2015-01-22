#ifndef __ABHEG__USERSVC__USER_LOGIC___
#define __ABHEG__USERSVC__USER_LOGIC___
#include "common.h"


namespace usersvc_logic{

class Userlogic{

public:
    Userlogic();
    virtual ~Userlogic();

private:
    static Userlogic    *instance_;

public:
    static Userlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnUserConnect (struct server *srv,const int socket);

    bool OnUserMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnUserClose (struct server *srv,const int socket);

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

