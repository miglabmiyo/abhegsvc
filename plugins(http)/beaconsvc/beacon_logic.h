#ifndef __ABHEG__BEACONSVC__BEACON_LOGIC___
#define __ABHEG__BEACONSVC__BEACON_LOGIC___
#include "net/beacon_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/beaconsvc/beaconsvc_config.xml"


namespace beaconsvc_logic{

class Beaconlogic{

public:
    Beaconlogic();
    virtual ~Beaconlogic();

private:
    static Beaconlogic    *instance_;

public:
    static Beaconlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnBeaconConnect (struct server *srv,const int socket);

    bool OnBeaconMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnBeaconClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);


private:
    bool OnSharkBeacon(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool Init();
};


}

#endif

