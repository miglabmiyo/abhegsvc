#ifndef __BUDDHA__ROBOTSVC__ROBOT_LOGIC___
#define __BUDDHA__ROBOTSVC__ROBOT_LOGIC___
#include "net/robot_comm_head.h"
#include "robot_basic_info.h"
#include "logic/logic_infos.h"
#include "net/robot_comm_head.h"
#include "protocol/http_packet.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/robotsvc/robotsvc_config.xml"

namespace robotsvc_logic{

class Robotlogic{

public:
    Robotlogic();
    virtual ~Robotlogic();

private:
    static Robotlogic    *instance_;

public:
    static Robotlogic *GetInstance();
    static void FreeInstance();

public:
    bool OnRobotConnect (struct server *srv,const int socket);

    bool OnRobotMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnRobotClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:

    bool OnGetSpiderPhoneNumber(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnBookCollection(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnBookInfo(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
        		const void* msg = NULL,const int len = 0);


private:

    bool ResolveChapterList(std::list<BookChapterCollection>& list,std::string& str);

    bool ResolveBookInfoList(std::list<BookInfo>& list,std::string& str);

//模板
    template <typename ELEMENT>
    bool ResplveTemplateList(std::list<ELEMENT>& list,std::string& str);
private:

    bool Init();
};


}

#endif

