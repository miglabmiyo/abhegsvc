#include "book_logic.h"
#include "common.h"

namespace booksvc_logic{

Booklogic*
Booklogic::instance_=NULL;

Booklogic::Booklogic(){
   if(!Init())
      assert(0);
}

Booklogic::~Booklogic(){
}

bool Booklogic::Init(){
    return true;
}

Booklogic*
Booklogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Booklogic();

    return instance_;
}



void Booklogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Booklogic::OnBookConnect(struct server *srv,const int socket){

    return true;
}



bool Booklogic::OnBookMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Booklogic::OnBookClose(struct server *srv,const int socket){

    return true;
}



bool Booklogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Booklogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Booklogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Booklogic::OnIniTimer(struct server *srv){

    return true;
}



bool Booklogic::OnTimeout(struct server *srv, char *id, int opcode, int time){

    return true;
}

}

