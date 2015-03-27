#ifndef __ABHEG__USERSVC__USER_LOGIC___
#define __ABHEG__USERSVC__USER_LOGIC___
#include "net/user_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/usersvc/usersvc_config.xml"

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
    bool OnQuickLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnThirdLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnBDBindPush(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

private:

    bool Init();
};


}

#endif

