#include "extension_logic.h"
#include "common.h"

namespace extensionsvc_logic{

Extensionlogic*
Extensionlogic::instance_=NULL;

Extensionlogic::Extensionlogic(){
   if(!Init())
      assert(0);
}

Extensionlogic::~Extensionlogic(){
}

bool Extensionlogic::Init(){
    return true;
}

Extensionlogic*
Extensionlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Extensionlogic();

    return instance_;
}



void Extensionlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Extensionlogic::OnExtensionConnect(struct server *srv,const int socket){

    return true;
}



bool Extensionlogic::OnExtensionMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Extensionlogic::OnExtensionClose(struct server *srv,const int socket){

    return true;
}



bool Extensionlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Extensionlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Extensionlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Extensionlogic::OnIniTimer(struct server *srv){

    return true;
}



bool Extensionlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

