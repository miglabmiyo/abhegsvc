#ifndef __ABHEG__WIFISVC__WIFI_LOGIC___
#define __ABHEG__WIFISVC__WIFI_LOGIC___
#include "common.h"


namespace wifisvc_logic{

class Wifilogic{

public:
    Wifilogic();
    virtual ~Wifilogic();

private:
    static Wifilogic    *instance_;

public:
    static Wifilogic *GetInstance();
    static void FreeInstance();

public:
    bool OnWifiConnect (struct server *srv,const int socket);

    bool OnWifiMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnWifiClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);


private:
    bool OnGainWifiService(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);
private:

    bool Init();
};


}

#endif

