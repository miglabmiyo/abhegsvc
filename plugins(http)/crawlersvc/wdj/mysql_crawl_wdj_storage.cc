/*
 * mysql_crawl_wdj_storage.cc
 *
 *  Created on: 2015年5月25日
 *      Author: Administrator
 */
#include "wdj/mysql_crawl_wdj_storage.h"
#include "storage/mysql_crawl_storage.h"
#include "basic/basic_util.h"
#include "logic/logic_infos.h"
#include "check/newmacro.h"
#include <sstream>

namespace crawlersvc_logic{

MysqlCrawlWDJStorage::MysqlCrawlWDJStorage(void){
	mysql_engine_.reset(crawlersvc_logic::CrawlerStorageBaseEngine::Create(MYSQL_TYPE));
	parser_engine_.reset(new crawlersvc_logic::ParserWDJEngine());
}

MysqlCrawlWDJStorage::~MysqlCrawlWDJStorage(){

}

bool MysqlCrawlWDJStorage::ReadWDJDetailInfo(const int32 from,const int32 count,base_logic::Value* value){
	std::string sql = "call proc_GetWandoujiaDetail("+base::BasicUtil::BasicUtil::StringUtil::Int64ToString(from)+","+base::BasicUtil::BasicUtil::StringUtil::Int64ToString(count)+")";
	mysql_engine_->ReadData(sql,value,CallBackGetWDJDetailInfo);
	return true;
}

bool MysqlCrawlWDJStorage::UpdateCrawlerURLState(const int64 id,const int32 status){
	std::string sql = "call proc_UpdateCrawlerWandoujia("+base::BasicUtil::BasicUtil::StringUtil::Int64ToString(id)+","+base::BasicUtil::StringUtil::Int64ToString(status)+")";
	mysql_engine_->ReadData(sql,NULL,NULL);
	return true;
}

bool MysqlCrawlWDJStorage::CreaeAppDetailInfo(base_logic::Value* value){
	base_logic::AppInfos  info;
	std::list<std::string> pic_list;
	//存储完成数据
	/*
	 *call abheg.proc_CreateAppInfo('com.duokan.reader','多看阅读',1001,'http://img.wdjimg.com/mms/v1/9/54/aa3766428a594b5ecc8db71e58755e25.png',3029774,2183,
'免费电子书阅读器，全新界面及交互设计，简洁明亮的扁平化风格，让一切回归简单','15568429','1.0.2','北京多看科技有限公司',
'海量好书！极致体验！千万读者首选！ 2014印象笔记全球开发者大奖中国最佳应用！ 软件描述：1、海量精品图书尽情获取  拥有国内质量最高的精品电子书库，更有数万杂志和原创作品等您翻阅。 2、极致排版，完美展现 每部多看精品书都是资深编辑呕血之作，无论图文混排、绕排、画廊模式，还是拼音、公式，各种绚丽效果皆可完美呈现，更有注释的无缝嵌入、音频视频完美融入、多点交互互动，全面超越纸书的阅读体验。 3、TXT、PDF阅读神器 领先行业的中文排版技术，让TXT阅读也可以精致优雅。 独步武林的PDF重排功能，让PDF在手机上获得最佳的呈现效果，绝对超出期待。 4、更多功能让您享受阅读乐趣 强大的批注、笔记、书签、字典功能，帮助您深度阅读，更有贴心的阅历、进度同步、云书架、书友圈等功能,让您尽享阅读乐趣。'
)
	*/
	parser_engine_->PaserCompleteAppInfo(value,info);
	//std::string sql = "call proc_CreateAppInfo(\'"+info.packetname()+"\',\'"+info.name()+"\,"+
	std::stringstream os;
	std::stringstream os1;
	std::string sql;
	os<<"call proc_CreateAppInfo(\'"<<info.packetname()<<"\',\'"<<info.name()<<"\',"
			<<base::BasicUtil::BasicUtil::StringUtil::Int64ToString(info.type())<<",\'"
			<<info.logo()<<"\',"<<info.down()<<","<<info.like()<<",\'"<<info.introduction()
			<<"\',\'"<<info.size()<<"\',\'"<<info.version()<<"\',\'"<<info.developer_name()<<"\',\'"
			<<info.android_url()<<"\',\'"<<info.summary()<<"\');";
	sql = os.str();
	mysql_engine_->ReadData(sql,NULL,NULL);

	info.summary_pic(pic_list);
	while(pic_list.size()>0){
		std::string pic = pic_list.front();
		pic_list.pop_front();
		os1<<"call proc_CreateAppInfoSummaryPic(\'"<<info.packetname()
				<<"\',"<<info.type()<<",\'"<<pic<<"\');	 ";
	}

	std::string sql1 = os1.str();
	mysql_engine_->ReadData(sql1,NULL,NULL);
	return true;
}

void MysqlCrawlWDJStorage::CallBackGetWDJDetailInfo(void* param,base_logic::Value* value){
	base_logic::ListValue* list  = (base_logic::ListValue*)(value);
	base_storage::DBStorageEngine* engine  = (base_storage::DBStorageEngine*)(param);
	MYSQL_ROW rows;
	int num = engine->RecordCount();
	if(num>0){
		while(rows = (*(MYSQL_ROW*)(engine->FetchRows())->proc)){
			base_logic::DictionaryValue * value = new base_logic::DictionaryValue();
			if(rows[0]!=NULL)
				value->SetBigInteger(L"id",atoll(rows[0]));
			if(rows[1]!=NULL)
				value->SetString(L"url",std::string(rows[1]));

			list->Append((base_logic::Value*)(value));
		}
		return;
	}
	return;

}

}


