#include "wifi_logic.h"
#include "common.h"

namespace wifisvc_logic{

Wifilogic*
Wifilogic::instance_=NULL;

Wifilogic::Wifilogic(){
   if(!Init())
      assert(0);
}

Wifilogic::~Wifilogic(){
}

bool Wifilogic::Init(){
    return true;
}

Wifilogic*
Wifilogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Wifilogic();

    return instance_;
}



void Wifilogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Wifilogic::OnWifiConnect(struct server *srv,const int socket){

    return true;
}



bool Wifilogic::OnWifiMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Wifilogic::OnWifiClose(struct server *srv,const int socket){

    return true;
}



bool Wifilogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Wifilogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Wifilogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Wifilogic::OnIniTimer(struct server *srv){

    return true;
}



bool Wifilogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

