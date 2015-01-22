#include "find_logic.h"
#include "common.h"

namespace findsvc_logic{

Findlogic*
Findlogic::instance_=NULL;

Findlogic::Findlogic(){
   if(!Init())
      assert(0);
}

Findlogic::~Findlogic(){
}

bool Findlogic::Init(){
    return true;
}

Findlogic*
Findlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Findlogic();

    return instance_;
}



void Findlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Findlogic::OnFindConnect(struct server *srv,const int socket){

    return true;
}



bool Findlogic::OnFindMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Findlogic::OnFindClose(struct server *srv,const int socket){

    return true;
}



bool Findlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Findlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Findlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Findlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Findlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

