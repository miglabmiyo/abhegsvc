#include "movies_logic.h"
#include "common.h"

namespace moviessvc_logic{

Movieslogic*
Movieslogic::instance_=NULL;

Movieslogic::Movieslogic(){
   if(!Init())
      assert(0);
}

Movieslogic::~Movieslogic(){
}

bool Movieslogic::Init(){
    return true;
}

Movieslogic*
Movieslogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Movieslogic();

    return instance_;
}



void Movieslogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Movieslogic::OnMoviesConnect(struct server *srv,const int socket){

    return true;
}



bool Movieslogic::OnMoviesMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Movieslogic::OnMoviesClose(struct server *srv,const int socket){

    return true;
}



bool Movieslogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Movieslogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Movieslogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Movieslogic::OnIniTimer(struct server *srv){

    return true;
}



bool Movieslogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

