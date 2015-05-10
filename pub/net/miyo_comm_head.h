/*
 * miyo_comm.h
 *
 *  Created on: 2015年5月10日
 *      Author: kerry
 */

#ifndef MIYO_COMM_H_
#define MIYO_COMM_H_

#include "net/comm_head.h"
#include "basic/basictypes.h"
#include "basic/scoped_ptr.h"
#include "logic/base_values.h"
#include <list>
#include <string>
#include <sstream>

namespace netcomm_recv{

class Collect:public LoginHeadPacket{
public:
	Collect(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
#if defined(__OLD_VERSION__)
		GETBIGINTTOINT(L"taruid",tid_);
#else
		GETBIGINTTOINT(L"tid",tid_);
#endif
	}


	const inline int64 tid() const {return this->tid_;}

	inline void set_tid(const int64 tid) {m_->SetBigInteger(L"tid",tid);}

private:
	int64  tid_;
};

class DelCollect:public LoginHeadPacket{
public:
	DelCollect(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void Init(){
		bool r = false;
		GETBIGINTTOINT(L"songid",songid_);
		if(!r) error_code_ = MUSIC_SONG_ID_LACK;
	}

	const int64 songid() const {return this->songid_;}

private:
	int64 songid_;
};

typedef DelCollect SetHateCollect;

class SetCollect:public LoginHeadPacket{
public:
	SetCollect(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	void Init(){
		bool r = false;
		GETBIGINTTOINT(L"songid",songid_);
		if(!r) error_code_ = MUSIC_SONG_ID_LACK;

		GETBIGINTTOINT(L"typeid",dimemsion_id_);

		if(!r){
			GETBIGINTTOINT(L"sid",dimemsion_id_);
		}

		if(!r) error_code_ = MUSIC_TYPE_ID_LACK;

		r = m_->GetString(L"modetype",&dimension_alais_);
		if(!r)
			r = m_->GetString(L"dimension",&dimension_alais_);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
	}

	const int64 songid() const {return this->songid_;}
	const int64 dimemsion_id() const {return this->dimemsion_id_;}
	const std::string& dimension_alais() const {return this->dimension_alais_;}

private:
	int64 songid_;
	int64 dimemsion_id_;
	std::string dimension_alais_;
};


class Dimension:public LoginHeadPacket{
public:
	Dimension(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
		GETBIGINTTOINT(L"sid",dimension_sub_id_);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		r = m_->GetString(L"dimension",&dimension_name_);
		if(!r) error_code_ = MUSIC_TYPE_ID_LACK;
	}

	const std::string& dimension_name() const {return dimension_name_;}
	const int64 dimension_sub_id() const {return dimension_sub_id_;}

private:
	std::string  dimension_name_;
	int64  dimension_sub_id_;
};

class DimensionUnit{
public:
	DimensionUnit()
	:dimension_id_(-1)
	,dimension_index_(-1){}

	void set_dimension_id(const int64 dimension_id){this->dimension_id_ = dimension_id;}
	void set_dimension_index(const int64 dimension_index){this->dimension_index_ = dimension_index;}
	void set_dimension_alias_name(const std::string& alias_name){this->dimension_alias_name_ = alias_name;}

	const int64 dimension_id() const {return this->dimension_id_;}
	const int64 dimension_index() const {return this->dimension_index_;}
	const std::string& dimension_alias_name() const {return this->dimension_alias_name_;}


private:
	int64        dimension_id_;
	int64        dimension_index_;
	std::string  dimension_alias_name_;
};

class Dimensions:public LoginHeadPacket{
public:
	Dimensions(NetBase* m)
	:LoginHeadPacket(m){
		mood_dimension_.set_dimension_alias_name("mm");
		scens_dimension_.set_dimension_alias_name("ms");
		channel_dimension_.set_dimension_alias_name("chl");
		Init();
	}

	inline void Init(){
		bool r = false;
		int64 id = 0;
		int64 index = 0;
		std::string name;

		r = m_->GetBigInteger(L"typeid",&id);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			type_dimension_.set_dimension_id(id);

		r = m_->GetBigInteger(L"moodid",&id);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			mood_dimension_.set_dimension_id(id);

		GETBIGINTTOINT(L"sceneid",id);
		r = m_->GetBigInteger(L"sceneid",&id);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			scens_dimension_.set_dimension_id(id);

		r = m_->GetBigInteger(L"channelid",&id);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			channel_dimension_.set_dimension_id(id);




		r = m_->GetBigInteger(L"typeindex",&index);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			type_dimension_.set_dimension_index(index);

		r = m_->GetBigInteger(L"channelindex",&index);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			channel_dimension_.set_dimension_index(index);

		r = m_->GetBigInteger(L"moodindex",&index);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			mood_dimension_.set_dimension_index(index);


		r = m_->GetBigInteger(L"sceneindex",&index);
		if(!r) error_code_ = MUSIC_TYPE_LACK;
		else
			scens_dimension_.set_dimension_index(index);

		GETBIGINTTOINT(L"num",num_);
		if(!r) num_ = 5;
	}

	const DimensionUnit& TypdeDimension() const {return this->type_dimension_;}
	const DimensionUnit& ChannelDimension() const {return this->channel_dimension_;}
	const DimensionUnit& MoodDimension() const {return this->mood_dimension_;}
	const DimensionUnit& ScensDimension() const {return this->scens_dimension_;}

	const int64 Num() const {return this->num_;}
private:
	DimensionUnit    type_dimension_;
	DimensionUnit    channel_dimension_;
	DimensionUnit    mood_dimension_;
	DimensionUnit    scens_dimension_;
	int64           num_;
};



class RecordMusic:public LoginHeadPacket{
public:
	RecordMusic(NetBase* m)
	:LoginHeadPacket(m){
		Init();
	}

	inline void Init(){
		bool r = false;
		std::string singer;
		std::string music;

		r = m_->GetBigInteger(L"cursong",&current_song_id_);
		if(!r) error_code_ = MUSIC_SONG_ID_LACK;

		r = m_->GetBigInteger(L"typeid",&dimension_sub_id_);
		if(!r) error_code_ = MUSIC_TYPE_ID_LACK;

		r = m_->GetString(L"mode",&dimension_name_);
		if(!r) error_code_ = MUSIC_TYPE_LACK;

		r = m_->GetBigInteger(L"lastsong",&last_song_id_);
		if(!r) last_song_id_ = 0;

		r = m_->GetBigInteger(L"state",&state_);
		if(!r) state_ = 0;

		r = m_->GetString(L"singer",&singer);
		if(!r)
			singer_ = "佚名";
		else
			base::BasicUtil::UrlDecode(singer,singer_);

		r = m_->GetString(L"song",&music);
		if(!r)
			name_ = "未知";
		else
			base::BasicUtil::UrlDecode(name_,name_);
	}

	const int64 last_song_id() const {return this->last_song_id_;}
	const int64 current_song_id() const {return this->current_song_id_;}
	const int64 dimension_sub_id() const {return this->dimension_sub_id_;}
	const int64 state() const {return this->state_;}
	const std::string& singer() const {return this->singer_;}
	const std::string& name() const {return this->name_;}
	const std::string& dimension_name() const {return this->dimension_name_;}

private:
	int64  last_song_id_;
	int64  current_song_id_;
	int64  dimension_sub_id_;
	int64  state_;
	std::string singer_;
	std::string name_;
	std::string dimension_name_;
};
}

namespace netcomm_send{
class MusicList:public HeadPacket{
public:
	MusicList(){
		base_.reset(new netcomm_send::NetBase());
		list_.reset(new base_logic::ListValue());
	}

	netcomm_send::NetBase* release(){
		if(!list_->empty())
			this->base_->Set(L"song",list_.release());
		head_->Set("result",base_.release());
		this->set_status(1);
		return head_.release();
	}

	inline void set_list(base_logic::DictionaryValue* music){
		list_->Append(music);
	}

private:
	scoped_ptr<netcomm_send::NetBase>             base_;
	scoped_ptr<base_logic::ListValue>             list_;

};


}



#endif /* MIYO_COMM_H_ */
