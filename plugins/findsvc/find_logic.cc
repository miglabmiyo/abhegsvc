#include "find_logic.h"
#include "find_cache_mgr.h"
#include "db_comm.h"
#include "logic/logic_unit.h"
#include "logic/logic_comm.h"
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

	findsvc_logic::CacheManagerOp::GetCacheManagerOp();
	findsvc_logic::CacheManagerOp::GetFindCacheManager();
	//读取APP商城信息
	findsvc_logic::CacheManagerOp::FetchDBFindAppStore();
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
	const char* packet_stream = (char*)(msg);
	std::string http_str(packet_stream,len);
	std::string error_str;
	int error_code = 0;

	LOG_MSG2("%s",packet_stream);

	scoped_ptr<base_logic::ValueSerializer> serializer(base_logic::ValueSerializer::Create(base_logic::IMPL_HTTP,&http_str));


	netcomm_recv::NetBase*  value = (netcomm_recv::NetBase*)(serializer.get()->Deserialize(&error_code,&error_str));
	if(value==NULL){
		error_code = STRUCT_ERROR;
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}
	scoped_ptr<netcomm_recv::HeadPacket> packet(new netcomm_recv::HeadPacket(value));
	int32 type = packet->GetType();
	switch(type){
	   case FIND_STORE_APP:
		   OnFindAppStore(srv,socket,value);
		   break;
	}

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

bool Findlogic::OnFindAppStore(struct server *srv,const int socket,netcomm_recv::NetBase* netbase,
    		const void* msg,const int len){
	scoped_ptr<netcomm_recv::FindType> findapp(new netcomm_recv::FindType(netbase));
	bool r = false;
	int error_code = findapp->GetResult();
	if(error_code!=0){
		//发送错误数据
		send_error(error_code,socket);
		return false;
	}

	if(this->app_store_list_.size()<=0)
		send_error(NULL_DATA,socket);

	//构造发送数据
	scoped_ptr<netcomm_send::FindAppStore> appstore(new netcomm_send::FindAppStore());

	// 推荐广告 推荐APP 推荐专题
	{
		base_logic::RLockGd lk(lock_);
		std::list<base_logic::AppInfos>::iterator appinfo_iterator;
		for(appinfo_iterator=this->app_store_list_.begin();
				appinfo_iterator!=this->app_store_list_.end();
				appinfo_iterator++){
			base_logic::AppInfos appinfo = (*appinfo_iterator);
			if(appinfo.attr()==0)
				appstore->set_important(appinfo.Release());
			else if(appinfo.attr()==1)
				appstore->set_popularity(appinfo.Release());
			else if(appinfo.attr()==2)
				appstore->set_hot(appinfo.Release());
		}
	}
	send_message(socket,(netcomm_send::HeadPacket*)appstore.get());
	return true;
}

}

