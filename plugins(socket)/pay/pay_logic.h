#ifndef __ABHEG__PAYSVC__PAY_LOGIC___
#define __ABHEG__PAYSVC__PAY_LOGIC___
#include "socket/protocol.h"
#include "socket/comm_head.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/paysvc/paysvc_config.xml"
namespace paysvc_logic{

class Paylogic{

public:
    Paylogic();
    virtual ~Paylogic();

private:
    static Paylogic    *instance_;

public:
    static Paylogic *GetInstance();
    static void FreeInstance();

public:
    bool OnPayConnect (struct server *srv,const int socket);

    bool OnPayMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnPayClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:

    bool OnPayUserLogin(struct server *srv, int socket, struct PacketHead *packet,
	           const void *msg = NULL, int len = 0);

    bool OnGetSMSChrgPoint(struct server *srv, int socket, struct PacketHead *packet,
	           const void *msg = NULL, int len = 0);

    bool OnUpdateSerialnumber(struct server *srv, int socket, struct PacketHead *packet,
	           const void *msg = NULL, int len = 0);

    bool Init();
};


}

#endif

