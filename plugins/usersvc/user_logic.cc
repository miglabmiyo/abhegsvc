#include "user_logic.h"
#include "common.h"

namespace usersvc_logic{

Userlogic*
Userlogic::instance_=NULL;

Userlogic::Userlogic(){
   if(!Init())
      assert(0);
}

Userlogic::~Userlogic(){
}

bool Userlogic::Init(){
    return true;
}

Userlogic*
Userlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Userlogic();

    return instance_;
}



void Userlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Userlogic::OnUserConnect(struct server *srv,const int socket){

    return true;
}



bool Userlogic::OnUserMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Userlogic::OnUserClose(struct server *srv,const int socket){

    return true;
}



bool Userlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Userlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Userlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Userlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Userlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

