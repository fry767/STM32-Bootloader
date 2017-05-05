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

 void Comm_ParameterInitialise(Comm_Parameter_Struct* ParamStruct,char* Wanted_Key);
 void CommunicationSecurityAdd(uint8_t* Buffer,uint8_t size);
 uint8_t CommunicationSecurityCalc(void);

#ifdef __cplusplus
}
#endif
#endif
