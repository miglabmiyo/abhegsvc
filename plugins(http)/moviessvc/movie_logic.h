#ifndef __ABHEG__MOVIESSVC__MOVIES_LOGIC___
#define __ABHEG__MOVIESSVC__MOVIES_LOGIC___
#include "net/movie_comm_head.h"
#include "net/operator_code.h"
#include "net/error_comm.h"
#include "logic/logic_infos.h"
#include "common.h"

#define DEFAULT_CONFIG_PATH     "./plugins/moviesvc/moviesvc_config.xml"
namespace moviessvc_logic{

class Movieslogic{

public:
    Movieslogic();
    virtual ~Movieslogic();

private:
    static Movieslogic    *instance_;

public:
    static Movieslogic *GetInstance();
    static void FreeInstance();

public:
    bool OnMoviesConnect (struct server *srv,const int socket);

    bool OnMoviesMessage (struct server *srv, const int socket,const void *msg, const int len);

    bool OnMoviesClose (struct server *srv,const int socket);

    bool OnBroadcastConnect(struct server *srv,const int socket,const void *data, const int len);

    bool OnBroadcastMessage (struct server *srv, const int socket, const void *msg, const int len);

    bool OnBroadcastClose (struct server *srv, const int socket);

    bool OnIniTimer (struct server *srv);

    bool OnTimeout (struct server *srv, char* id, int opcode, int time);

private:
    bool OnMovieSummary(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnMovieLike(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg = NULL,const int len = 0);

    bool OnSearchType(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
      		const void* msg = NULL,const int len = 0);
private:

    bool Init();
};


}

#endif

