#ifndef __ABHEG__FINDSVC__FIND_LOGIC___
#define __ABHEG__FINDSVC__FIND_LOGIC___
#include "common.h"


namespace findsvc_logic{

class Findlogic{

public:
    Findlogic();
    virtual ~Findlogic();

private:
    static Findlogic    *instance_;

public:
    static Findlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnFindConnect (struct server *srv,const int socket);

    bool OnFindMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnFindClose (struct server *srv,const int socket);

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

