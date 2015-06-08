#include "crawler_logic.h"
#include "appstore_engine.h"
#include "definition.h"
#include "storage/storage_base_engine.h"
#include "logic/logic_comm.h"
#include "check/newmacro.h"
#include "common.h"
#include <stdlib.h>

#define TIME_START_TASK 1000
namespace crawlersvc_logic{

Crawlerlogic*
Crawlerlogic::instance_=NULL;

Crawlerlogic::Crawlerlogic(){
   if(!Init())
      assert(0);
}

Crawlerlogic::~Crawlerlogic(){
}

bool Crawlerlogic::Init(){
	wandoujia_engine_.reset(crawlersvc_logic::AppStoreEngine::Create(IMPL_WANDOUJIA));
	std::string path = DEFAULT_CONFIG_PATH;
	config::FileConfig* config = config::FileConfig::GetFileConfig();
	if(config==NULL)
		return false;
	bool r = config->LoadConfig(path);
	crawlersvc_logic::CrawlerStorageBaseEngine::Init(config);
    return true;
}

Crawlerlogic*
Crawlerlogic::GetInstance(){

    if(instance_==NULL)
        instance_ = new Crawlerlogic();

    return instance_;
}



void Crawlerlogic::FreeInstance(){
    delete instance_;
    instance_ = NULL;
}

bool Crawlerlogic::OnCrawlerConnect(struct server *srv,const int socket){

    return true;
}



bool Crawlerlogic::OnCrawlerMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Crawlerlogic::OnCrawlerClose(struct server *srv,const int socket){

    return true;
}



bool Crawlerlogic::OnBroadcastConnect(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}

bool Crawlerlogic::OnBroadcastMessage(struct server *srv, const int socket, const void *msg,const int len){

    return true;
}



bool Crawlerlogic::OnBroadcastClose(struct server *srv, const int socket){

    return true;
}

bool Crawlerlogic::OnIniTimer(struct server *srv){
	srv->add_time_task(srv,"crawler",TIME_START_TASK,1,50);
    return true;
}



bool Crawlerlogic::OnTimeout(struct server *srv, char *id, int opcode, int time){
	switch(opcode){
	case TIME_START_TASK:
		OnTaskStar();
		break;
	default:
		LOG_ERROR2("unkown code :%d",opcode);
	}
    return true;
}

void Crawlerlogic::OnTaskStar(){
	//wandoujia_engine_->OnTasks(TASK_TEST);
	wandoujia_engine_->OnTasks(TASK_DB_READ);
}

}

