#ifndef __ABHEG__HACKSVC__HACK_LOGIC___
#define __ABHEG__HACKSVC__HACK_LOGIC___

#include "appstore_connector.h"
#include "hack_basic_info.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "net/comm_head.h"
#include "logic/logic_infos.h"
#include "common.h"

namespace hacksvc_logic{

class Hacklogic{

public:
    Hacklogic();
    virtual ~Hacklogic();

private:
    static Hacklogic    *instance_;

public:
    static Hacklogic *GetInstance();
    static void FreeInstance();

public:
    bool OnHackConnect (struct server *srv,const int socket);

    bool OnHackMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnHackClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    bool OnHackWandoujiaSuammry(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);
private:

    bool Init();
private:
    bool OnReplaceAppSummaryUnit(const std::string& pnname);
    bool OnRequestAppSummary(hacksvc_logic::AppSummaryParam& param,std::string& content);

    base_logic::DictionaryValue* AppSummarySerialzer(std::string& content);
private:
    hacksvc_logic::AppStoreConnector*              wandoujia_appstore_connector_engine_;
};


}

#endif

