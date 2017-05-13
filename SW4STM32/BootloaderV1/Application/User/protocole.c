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
uint8_t Comm_Poll_For_Firmware_Key(void)
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
void Communication_Poll_For_Firmware_Info(void)
{
	if(Comm_Poll_For_Firmware_Key())
	{
		uint32_t FirmwareSize = 0;
		char ch[] = " Key rcv, waiting for size\n\r";
		COMMUNICATION_SEND_FUNCTION(ch,sizeof(ch));

		COMMUNICATION_RECEIVE_FUNCTION(&FirmwareSize,sizeof(uint32_t));
		CommunicationParameter->FirmwareLength |= ((FirmwareSize >> 24)&0x000000FF);
		CommunicationParameter->FirmwareLength |= ((FirmwareSize >> 8)&0x0000FF00);
	}
}
void Communication_Receive_Firmware_And_Store(void)
{
	if(CommunicationParameter->FirmwareLength!=0)
	{
		uint32_t FirmwareValue = 0;
		for(uint32_t i = 0; i<CommunicationParameter->FirmwareLength/4;i++)
		{
			if(COMMUNICATION_RECEIVE_FUNCTION(&FirmwareValue,sizeof(uint32_t)) == 4)
				STORE_IN_EEPROM_FUNCTION(FirmwareValue);
		}
	}
}
uint8_t Communication_Receive_Checksum(void)
{
	uint8_t rcv_checksum = 0;
	COMMUNICATION_RECEIVE_FUNCTION(&rcv_checksum,1);
	return rcv_checksum;
}

uint8_t Calculate_Checksum_From_Storage(void)
{
	uint32_t* storage_address;
	storage_address = GET_STORAGE_ADDRESS();
	uint32_t currentAddress = *storage_address;
	for(uint32_t i = 0; i < CommunicationParameter->FirmwareLength/4; i++)
	{
		uint32_t value = READ_IN_MEMORY(currentAddress);
		CommunicationSecurityAdd(&value,4);
		currentAddress+=4;
	}
	return CommunicationSecurityCalc();
}
