#ifndef __ABHEG__MIYOSVC__MIYO_LOGIC___
#define __ABHEG__MIYOSVC__MIYO_LOGIC___
#include "net/user_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/miyosvc/miyosvc_config.xml"
namespace miyosvc_logic{

class Miyologic{

public:
    Miyologic();
    virtual ~Miyologic();

private:
    static Miyologic    *instance_;

public:
    static Miyologic *GetInstance();
    static void FreeInstance();

public:
    bool OnMiyoConnect (struct server *srv,const int socket);

    bool OnMiyoMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnMiyoClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    bool OnThirdLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
        		const void* msg = NULL,const int len = 0);
private:

    bool Init();
private:
    std::string          miyo_net_;
};


}

#endif

