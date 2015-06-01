#ifndef __ABHEG__EXTENSIONSVC__EXTENSION_LOGIC___
#define __ABHEG__EXTENSIONSVC__EXTENSION_LOGIC___
#include "common.h"


namespace extensionsvc_logic{

class Extensionlogic{

public:
    Extensionlogic();
    virtual ~Extensionlogic();

private:
    static Extensionlogic    *instance_;

public:
    static Extensionlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnExtensionConnect (struct server *srv,const int socket);

    bool OnExtensionMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnExtensionClose (struct server *srv,const int socket);

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

