#include "protocole.h"
#include "Bootloader_Settings.h"
#include "crc.h"


static uint8_t Comm_State;
static Comm_Parameter_Struct* CommunicationParameter;
static uint32_t Crc_Value;

void Comm_ParameterInitialise(Comm_Parameter_Struct* ParamStruct,char* Wanted_Key)
{
	CommunicationParameter = ParamStruct;
	CommunicationParameter->BootKey = Wanted_Key;
	CommunicationParameter->FirmwareLength = 0;
	CommunicationParameter->PacketCRC = 0;
	Crc_Value = 0;
}
char* Get_Communication_Key(void)
{
	return CommunicationParameter->BootKey;
}
uint8_t Comm_Poll_For_Firmware(void)
{

	uint8_t Size_To_Wait = 0;
	Size_To_Wait = strlen(CommunicationParameter->BootKey);
	uint8_t Entered_Key[Size_To_Wait];
	uint8_t error_flag = 0;
	COMMUNICATION_RECEIVE_FUNCTION(Entered_Key,Size_To_Wait);

	for(uint8_t i = 0; i < Size_To_Wait; i++)
	{
		if(Entered_Key[i] != CommunicationParameter->BootKey[i])
			error_flag = 1;
	}
	if(!error_flag)
		return 1;
	return 0;
}
void CommunicationSecurityAdd(uint8_t* Buffer,uint8_t size)
{
	for(uint8_t i = 0; i< size;i++)
		CommunicationParameter->PacketCRC +=Buffer[i];
}
uint8_t CommunicationSecurityCalc(void)
{
	uint8_t inverse = ~CommunicationParameter->PacketCRC;
	inverse += 1;
	return inverse;
}
