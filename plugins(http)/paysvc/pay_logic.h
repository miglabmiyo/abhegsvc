#ifndef __ABHEG__PAYSVC__PAY_LOGIC___
#define __ABHEG__PAYSVC__PAY_LOGIC___
#include "net/pay_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
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

    //连接SOCKET计费
    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);


private:

    bool Init();

    bool OnPhoneRegister(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnPayUserLogin(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnGetSMSChrgPoint(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnUpdateSerialnumber(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);


    bool OnWeixinUnifiedorder(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);
};


}

#endif

