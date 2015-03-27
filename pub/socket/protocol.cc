#include "protocol.h"
#include "comm_head.h"
#include "protocol/data_packet.h"
#include "logic/logic_comm.h"

bool ProtocolPack::UnpackStream(const void *packet_stream, int len, 
                                        struct PacketHead**packhead ){

	bool r = true;
	if (len < PACKET_HEAD_LENGTH)
		return false;

	int32 packet_length = ((struct PacketHead *) packet_stream)->packet_length;
	int32 packet_operate = ((struct PacketHead *) packet_stream)->operate_code;
	int32 data_length = ((struct PacketHead *) packet_stream)->data_length;
	int32 is_zip = ((struct PacketHead *) packet_stream)->is_zip;
	char* data = NULL;
	if (packet_length < PACKET_HEAD_LENGTH
		||packet_length!= len
		||data_length != packet_length - PACKET_HEAD_LENGTH){
			LOG_ERROR2("packet_length [%d] data_length[%d] PACK_HEAD_LENGTH [%d]",
				packet_length,data_length,PACKET_HEAD_LENGTH);
			return false;
	}

	//
	if (is_zip)
		data = (char*)packet_stream + PACKET_HEAD_LENGTH;
	else
		data = (char*)packet_stream + PACKET_HEAD_LENGTH;

	switch(packet_operate){
		case PAY_USER_LOGIN:
			{
				struct PayUserLogin* vPayUserLogin = new struct PayUserLogin;
				*packhead = (struct PacketHead*)vPayUserLogin;
				BUILDPACKHEAD();
				vPayUserLogin->platform = in.Read32();
				int temp = 0;
				memcpy(vPayUserLogin->imei,in.ReadData(IMEI_LEN,temp),IMEI_LEN);
				vPayUserLogin->imei[IMEI_LEN - 1] = '\0';
				memcpy(vPayUserLogin->sim,in.ReadData(SIM_LEN,temp),SIM_LEN);
				vPayUserLogin->sim[SIM_LEN - 1] = '\0';
			}
			break;
		case PAY_USER_LOGIN_SUCESS:
			{
				struct PayUserLoginSucess* vPayUserLoginSucess = new struct PayUserLoginSucess;
				*packhead = (struct PayUserLoginSucess*)vPayUserLoginSucess;
				BUILDPACKHEAD();
				vPayUserLoginSucess->uid = in.Read64();
				vPayUserLoginSucess->login_time = in.Read64();
				int temp = 0;
				memcpy(vPayUserLoginSucess->token,in.ReadData(TOKEN_LEN,temp),TOKEN_LEN);
				vPayUserLoginSucess->token[TOKEN_LEN - 1] = '\0';
			}
			break;
		case PAY_USER_LOGIN_FAILED:
			{
				struct ErrorPacket* vErrorPacket = new struct ErrorPacket;
				*packhead = (struct ErrorPacket*)vErrorPacket;
				BUILDPACKHEAD();
				vErrorPacket->error_code = in.Read32();
			}
			break;
		case PAY_GET_SMS_CHR_POINT:
			{
				struct PayGetSMSChrPoint* vPayGetSMSChrPoint = new PayGetSMSChrPoint;
				*packhead = (struct PayGetSMSChrPoint*)vPayGetSMSChrPoint;
				BUILDPACKHEAD();
				vPayGetSMSChrPoint->platform = in.Read32();
				vPayGetSMSChrPoint->uid = in.Read64();
				vPayGetSMSChrPoint->type = in.Read32();
				vPayGetSMSChrPoint->flag = in.Read32();
				vPayGetSMSChrPoint->money = in.Read32();
				int temp = 0;
				memcpy(vPayGetSMSChrPoint->token,in.ReadData(TOKEN_LEN,temp),TOKEN_LEN);
				vPayGetSMSChrPoint->token[TOKEN_LEN - 1] = '\0';
			}
			break;
		case PAY_SEND_SMS_UNI:
			{
				struct PaySendSMSUni* vPaySendSMSUni = new PaySendSMSUni;
				*packhead = (struct PaySendSMSUni*)vPaySendSMSUni;
				BUILDPACKHEAD();
				vPaySendSMSUni->charging_channel = in.Read32();
				int temp = 0;
				memcpy(vPaySendSMSUni->target_number,in.ReadData(NUMBER_LEN,temp),NUMBER_LEN);
				vPaySendSMSUni->target_number[NUMBER_LEN - 1] = '\0';
				memcpy(vPaySendSMSUni->target_content,in.ReadData(CONTENT_LEN,temp),CONTENT_LEN);
				vPaySendSMSUni->target_content[CONTENT_LEN - 1] = '\0';
				memcpy(vPaySendSMSUni->serial_number,in.ReadData(SERIALNUMBER_LEN,temp),SERIALNUMBER_LEN);
				vPaySendSMSUni->serial_number[SERIALNUMBER_LEN - 1] = '\0';
			}
			break;
		case PAY_UPDATE_SERIALNUMBER_STATE:
			{
				struct PayUpdateSerialState* vPayUpdateSerialState = new PayUpdateSerialState;
				*packhead = (struct PayUpdateSerialState*)vPayUpdateSerialState;
				BUILDPACKHEAD();
				vPayUpdateSerialState->state = in.Read32();
				int temp = 0;
				memcpy(vPayUpdateSerialState->serial_number,in.ReadData(SERIALNUMBER_LEN,temp),SERIALNUMBER_LEN);
				vPayUpdateSerialState->serial_number[SERIALNUMBER_LEN - 1] = '\0';
				memcpy(vPayUpdateSerialState->serial_number,in.ReadData(SERIALNUMBER_LEN,temp),SERIALNUMBER_LEN);
				vPayUpdateSerialState->serial_number[SERIALNUMBER_LEN - 1] = '\0';
			}
			break;
		default:
			break;
	}
	return r;
}

bool ProtocolPack::PackStream(const struct PacketHead* packhead,void** packet_stream,
							  int32* packet_stream_length){
	bool r = true;

	int32 packet_length = packhead->packet_length;
	int32 operate_code = packhead->operate_code;
	int32 data_length = packhead->data_length;
	int32 current_time = packhead->current_time;
	int8  is_zip = packhead->is_zip;
	int16 msg_type = packhead->msg_type;
	int64 msg_id =packhead->msg_id;
	int32 reserverd = packhead->reserverd;

	char* packet = NULL;
	char* data = NULL;

	switch(operate_code){
		case PAY_USER_LOGIN:
			{
				struct PayUserLogin* vPayUserLogin = (struct PayUserLogin*)packhead;
				BUILDHEAD(PAY_USER_LOGIN_SIZE);
				out.Write32(vPayUserLogin->platform);
				out.WriteData(vPayUserLogin->imei,IMEI_LEN);
				out.WriteData(vPayUserLogin->sim,SIM_LEN);
				packet = (char*)out.GetData();
			}
			break;
		case PAY_USER_LOGIN_SUCESS:
			{
				struct PayUserLoginSucess* vPayUserLoginSucess =(struct PayUserLoginSucess*)packhead;
				BUILDHEAD(PAY_USER_LOGIN_SUCESS_SIZE);
				out.Write64(vPayUserLoginSucess->uid);
				out.Write64(vPayUserLoginSucess->login_time);
				out.WriteData(vPayUserLoginSucess->token,TOKEN_LEN);
				packet = (char*)out.GetData();
			}
			break;
		case PAY_USER_LOGIN_FAILED:
			{
				struct ErrorPacket* vErrorPacket = (struct ErrorPacket*)packhead;
				BUILDHEAD(ERROR_PACKET_SIZE);
				out.Write64(vErrorPacket->error_code);
				packet = (char*)out.GetData();
			}
			break;
		case PAY_GET_SMS_CHR_POINT:
			{
				struct PayGetSMSChrPoint* vPayGetSMSChrPoint = (struct PayGetSMSChrPoint*)packhead;
				BUILDHEAD(PAY_GET_SMS_CHR_POINT_SIZE);
				out.Write32(vPayGetSMSChrPoint->platform);
				out.Write64(vPayGetSMSChrPoint->uid);
				out.Write32(vPayGetSMSChrPoint->type);
				out.Write32(vPayGetSMSChrPoint->flag);
				out.Write32(vPayGetSMSChrPoint->money);
				out.WriteData(vPayGetSMSChrPoint->token,TOKEN_LEN);
				packet = (char*)out.GetData();
			}
			break;
		case PAY_SEND_SMS_UNI:
			{
				struct PaySendSMSUni *vPaySendSMSUni = (struct PaySendSMSUni*)packhead;
				BUILDHEAD(PAY_SEND_SMS_UNI_SIZE);
				out.Write32(vPaySendSMSUni->charging_channel);
				out.WriteData(vPaySendSMSUni->target_number,NUMBER_LEN);
				out.WriteData(vPaySendSMSUni->target_content,CONTENT_LEN);
				out.WriteData(vPaySendSMSUni->serial_number,SERIALNUMBER_LEN);
				packet = (char*)out.GetData();
			}
			break;
		case PAY_UPDATE_SERIALNUMBER_STATE:
			{
				struct PayUpdateSerialState* vPayUpdateSerialState = (struct PayUpdateSerialState*)packhead;
				BUILDHEAD(PAY_UPDATE_SERIALNUMBER_STATE_SIZE);
				out.WriteData(vPayUpdateSerialState->serial_number,SERIALNUMBER_LEN);
				out.WriteData(vPayUpdateSerialState->opertor_serial,SERIALNUMBER_LEN);
				packet = (char*)out.GetData();
			}
			break;
		default:
			break;

	}

	*packet_stream = (void *)packet;

	if (packhead->packet_length == PACKET_HEAD_LENGTH
		&& packhead->data_length == 0)
		*packet_stream_length = PACKET_HEAD_LENGTH;
	else
		*packet_stream_length = packet_length;
	return r;
}

#define DUMPPACKBUF     4096

#define PRINT_TITLE(v)   \
	j += snprintf (buf + j, DUMPPACKBUF - j, "\n-------- %s --------\n", v)

#define PRINT_END(v)     \
	j += snprintf (buf + j, DUMPPACKBUF - j, "-------- %s --------\n", v)

#define PRINT_INT(v)    \
	j += snprintf (buf + j, DUMPPACKBUF - j, "\t%s = %d\n", #v, (int)v)

#define PRINT_INT64(v)    \
	j += snprintf (buf + j, DUMPPACKBUF - j, "\t%s = %lld\n", #v, (int64_t)v)

#define PRINT_STRING(v) \
	j += snprintf (buf + j, DUMPPACKBUF - j, "\t%s = %s\n", #v, (const char *)v)

#define DUMPHEAD()	            \
	PRINT_INT (packet_length);	\
	PRINT_INT (operate_code);	\
	PRINT_INT (data_length);    \
	PRINT_INT (current_time);   \
	PRINT_INT (msg_type);       \
	PRINT_INT (is_zip);         \
	PRINT_INT (msg_id);         \
	PRINT_INT (reserved);       \
	if (packet_length == PACKET_HEAD_LENGTH \
	&& data_length == 0)    \
	break;


void ProtocolPack::DumpPacket(const struct PacketHead *packhead){
#if !defined DEBUG || defined _DEBUG
	int32 packet_length = packhead->packet_length;
	int32 operate_code = packhead->operate_code;
	int32 data_length = packhead->data_length;
	int32 current_time = packhead->current_time;
	int16 msg_type = packhead->msg_type;
	int8 is_zip = packhead->is_zip;
	int64 msg_id = packhead->msg_id;
	int32 reserved = packhead->reserverd;
	/*
   int32 packet_length;
   int32 operate_code;
   int32 data_length;
   int32 current_time;
   int16 msg_type;
   int8  is_zip;
   int64 msg_id;
   int32 reserverd;
	 */
	char buf[DUMPPACKBUF];
	bool r = false;
	buf[0] = '\0';
	int j = 0;

	switch(operate_code){
		case PAY_USER_LOGIN:
		{
			struct PayUserLogin* vPayUserLogin =
					(struct PayUserLogin*)packhead;
			DUMPHEAD();
			PRINT_TITLE("struct PayUserLogin DumpBegin");
			PRINT_INT64(vPayUserLogin->platform);
			PRINT_STRING(vPayUserLogin->imei);
			PRINT_STRING(vPayUserLogin->sim);
			PRINT_END ("struct PayUserLogin Dump End");
		}
		break;
		case PAY_USER_LOGIN_SUCESS:
		{
			struct PayUserLoginSucess* vPayUserLoginSucess =
					(struct PayUserLoginSucess*)packhead;
			DUMPHEAD();
			PRINT_TITLE("struct PayUserLoginSucess DumpBegin");
			PRINT_INT64(vPayUserLoginSucess->uid);
			PRINT_INT64(vPayUserLoginSucess->login_time);
			PRINT_STRING(vPayUserLoginSucess->token);
			PRINT_END ("struct PayUserLoginSucess Dump End");

		}
		break;
		case PAY_USER_LOGIN_FAILED:
		{
			struct ErrorPacket* vErrorPacket =
					(struct ErrorPacket*)packhead;
			DUMPHEAD();
			PRINT_TITLE("struct ErrorPacket DumpBegin");
			PRINT_INT64(vErrorPacket->error_code);
			PRINT_END ("struct ErrorPacket Dump End");
		}
		break;
		case PAY_GET_SMS_CHR_POINT:
		{
			struct PayGetSMSChrPoint* vPayGetSMSChrPoint =
						(struct PayGetSMSChrPoint*)packhead;
				DUMPHEAD();
				PRINT_TITLE("struct PayGetSMSChrPoint DumpBegin");

				PRINT_INT64(vPayGetSMSChrPoint->platform);
				PRINT_INT64(vPayGetSMSChrPoint->uid);
				PRINT_INT64(vPayGetSMSChrPoint->type);
				PRINT_INT64(vPayGetSMSChrPoint->flag);
				PRINT_INT64(vPayGetSMSChrPoint->money);
				PRINT_STRING(vPayGetSMSChrPoint->token);
				PRINT_END ("struct PayGetSMSChrPoint Dump End");
		}
		break;
		case PAY_SEND_SMS_UNI:
		{
			struct PaySendSMSUni* vPaySendSMSUni =
						(struct PaySendSMSUni*)packhead;
				DUMPHEAD();
				PRINT_TITLE("struct PaySendSMSUni DumpBegin");

				PRINT_INT64(vPaySendSMSUni->charging_channel);
				PRINT_STRING(vPaySendSMSUni->target_number);
				PRINT_STRING(vPaySendSMSUni->target_content);
				PRINT_STRING(vPaySendSMSUni->serial_number);
				PRINT_END ("struct PaySendSMSUni Dump End");
		}
		break;
		case PAY_UPDATE_SERIALNUMBER_STATE:
		{
			struct PayUpdateSerialState* vPayUpdateSerialState =
						(struct PayUpdateSerialState*)packhead;
				DUMPHEAD();
				PRINT_TITLE("struct PayUpdateSerialState DumpBegin");
				PRINT_STRING(vPayUpdateSerialState->serial_number);
				PRINT_STRING(vPayUpdateSerialState->opertor_serial);
				PRINT_END ("struct PayUpdateSerialState Dump End");
		}
		break;
		default:
			r = false;
			break;
	}
	if (buf[0]!='\0')
		LOG_DEBUG2("%s\n",buf);
#endif
}



void ProtocolPack::HexEncode(const void *bytes, size_t size){
	struct PacketHead* head = (struct PacketHead*)bytes;
	static const char kHexChars[] = "0123456789ABCDEF";
	std::string sret(size*3,'\0');
	for (size_t i = 0;i<size;++i){
		char b = reinterpret_cast<const char*>(bytes)[i];
		sret[(i*3)] = kHexChars[(b>>4) & 0xf];
		sret[(i*3)+1]=kHexChars[b&0xf];
		if ((((i*3)+2+1)%12)!=0)
			sret[(i * 3) + 2] = '\40';
		else
			sret[(i * 3) + 2] = '\n';
	}
	LOG_DEBUG2("===start====\nopcode[%d]:\n%s\n====end====\n",
			head->operate_code,sret.c_str());
}

