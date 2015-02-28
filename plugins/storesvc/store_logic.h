#ifndef __ABHEG__STORESVC__STORE_LOGIC___
#define __ABHEG__STORESVC__STORE_LOGIC___
#include "net/store_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/storesvc/storesvc_config.xml"


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
    bool OnAppSummary(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
                   		const void* msg = NULL,const int len = 0);

    bool OnWantURL(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
                      		const void* msg = NULL,const int len = 0);

    bool OnLikePraise(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
      					const void* msg = NULL,const int len = 0);

    bool OnAppTopics(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
         					const void* msg = NULL,const int len = 0);

    bool OnSearchByType(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
				const void* msg = NULL,const int len = 0);

    bool OnSearchByKey(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
			const void* msg = NULL,const int len = 0);

private:

    bool Init();
};


}

#endif

