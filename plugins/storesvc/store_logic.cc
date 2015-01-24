#include "store_logic.h"
#include "common.h"

namespace storesvc_logic{

Storelogic*
Storelogic::instance_=NULL;

Storelogic::Storelogic(){
   if(!Init())
      assert(0);
}

Storelogic::~Storelogic(){
}

bool Storelogic::Init(){
    return true;
}

Storelogic*
Storelogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Storelogic();

    return instance_;
}



void Storelogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Storelogic::OnStoreConnect(struct server *srv,const int socket){

    return true;
}



bool Storelogic::OnStoreMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Storelogic::OnStoreClose(struct server *srv,const int socket){

    return true;
}



bool Storelogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Storelogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Storelogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Storelogic::OnIniTimer(struct server *srv){

    return true;
}



bool Storelogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

