#ifndef __ABHEG__GAMEBOXSVC__GAMEBOX_LOGIC___
#define __ABHEG__GAMEBOXSVC__GAMEBOX_LOGIC___
#include "net/gamebox_comm_head.h"
#include "common.h"


#define DEFAULT_CONFIG_PATH     "./plugins/gameboxsvc/gameboxsvc_config.xml"
namespace gameboxsvc_logic{

class Gameboxlogic{

public:
    Gameboxlogic();
    virtual ~Gameboxlogic();

private:
    static Gameboxlogic    *instance_;

public:
    static Gameboxlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnGameboxConnect (struct server *srv,const int socket);

    bool OnGameboxMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnGameboxClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    bool OnCheckGame(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnSharkGame(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);
private:

    bool Init();
};


}

#endif

