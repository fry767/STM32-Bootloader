#ifndef _PROTOCOLE_HW_H
#define _PROTOCOLE_HW_H
#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

 typedef struct{
 	char*    BootKey;
 	uint32_t FirmwareLength;
 	uint8_t PacketCRC;
 }Comm_Parameter_Struct;
 typedef struct{
	 uint8_t msg_header1;
	 uint8_t msg_header2;
	 uint8_t msg_cmd;
	 uint8_t msg_length;
	 uint8_t msg_checksum;
 }Comm_Message_Struct;
void Comm_ParameterInitialise(Comm_Parameter_Struct* ParamStruct,char* Wanted_Key);
void Communication_InitialiseMessage(Comm_Message_Struct *MessageStruct);
void CommunicationSecurityAdd(uint8_t* Buffer,uint8_t size);
uint8_t CommunicationSecurityCalc(void);
void Communication_Poll_For_Firmware_Info(void);
uint8_t Comm_Poll_For_Firmware_Key(void);
void Communication_Receive_Firmware_And_Store(void);
uint8_t Communication_Receive_Checksum(void);
uint8_t Communication_ReceiveIncommingPacket(void);
#ifdef __cplusplus
}
#endif
#endif
