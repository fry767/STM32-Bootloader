#include "protocole.h"
#include "Bootloader_Settings.h"
#include "crc.h"


static uint8_t Comm_State;
static Comm_Parameter_Struct* CommunicationParameter;
static Comm_Message_Struct* ApplicationMessage;
static uint32_t Crc_Value;

void Comm_ParameterInitialise(Comm_Parameter_Struct* ParamStruct,char* Wanted_Key)
{
	CommunicationParameter = ParamStruct;
	CommunicationParameter->BootKey = Wanted_Key;
	CommunicationParameter->FirmwareLength = 0;
	CommunicationParameter->PacketCRC = 0;
	Crc_Value = 0;
}
void Communication_InitialiseMessage(Comm_Message_Struct *MessageStruct)
{
	ApplicationMessage = MessageStruct;
	ApplicationMessage->msg_header1 = 0;
	ApplicationMessage->msg_header2 = 0;
	ApplicationMessage->msg_cmd = 0;
	ApplicationMessage->msg_length = 0;
	ApplicationMessage->msg_checksum = 0;
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
uint8_t Communication_ReceiveIncommingPacket()
{
	Comm_Message_Struct msg_to_send = {0};
	uint16_t flash_size = 0;
	uint8_t deviceID = Bootloader_GetDeviceID();
	/* Receive the header of the message*/
	if(!COMMUNICATION_RECEIVE_FUNCTION(ApplicationMessage,4))
		return 0;
	if(ApplicationMessage->msg_header1 != 0x04 && ApplicationMessage->msg_header2 != 0x7C)
	{
		return 0;
	}
	uint8_t buffer[ApplicationMessage->msg_length];
	/* Receive the buffer for the command*/
	COMMUNICATION_RECEIVE_FUNCTION(buffer,ApplicationMessage->msg_length);

	/*Receive Checksum*/
	ApplicationMessage->msg_checksum = Communication_Receive_Checksum();

	switch(ApplicationMessage->msg_cmd)
	{
		case 0x00:
			msg_to_send.msg_header1 = 0x04;
			msg_to_send.msg_header2 = 0x7C;
			msg_to_send.msg_cmd = 0x01;
			msg_to_send.msg_length = 3;
			flash_size = Bootloader_GetFlashSize();
			COMMUNICATION_SEND_FUNCTION((uint8_t*)&msg_to_send,4);
			COMMUNICATION_SEND_FUNCTION(&deviceID,1);
			COMMUNICATION_SEND_FUNCTION((uint8_t*)&flash_size,2);
			CommunicationSecurityAdd((uint8_t*)&flash_size,2);
			CommunicationSecurityAdd((uint8_t*)&msg_to_send,4);
			msg_to_send.msg_checksum = CommunicationSecurityCalc();
			COMMUNICATION_SEND_FUNCTION(&msg_to_send.msg_checksum,1);
			break;
		case 0x10:
			msg_to_send.msg_header1 = 0x04;
			msg_to_send.msg_header2 = 0x7C;
			msg_to_send.msg_cmd = 0x11;
			msg_to_send.msg_length = ApplicationMessage->msg_length + 1;
			Bootloader_WriteDeviceName(buffer,ApplicationMessage->msg_length);
			COMMUNICATION_SEND_FUNCTION((uint8_t*)&msg_to_send,4);
			COMMUNICATION_SEND_FUNCTION(&deviceID,1);
			Bootloader_ReadDeviceName(buffer);
			COMMUNICATION_SEND_FUNCTION(buffer,ApplicationMessage->msg_length);
			CommunicationSecurityAdd((uint8_t*)&msg_to_send,4);
			CommunicationSecurityAdd(&deviceID,1);
			CommunicationSecurityAdd(buffer,ApplicationMessage->msg_length);
			msg_to_send.msg_checksum = CommunicationSecurityCalc();
			COMMUNICATION_SEND_FUNCTION(&msg_to_send.msg_checksum,1);
			break;
		case 0x20:
			break;
		case 0x30:
			break;
		case 0x40:
			break;
		case 0x50:
			break;
		case 0x60:
			break;
		case 0x70:
			break;
		default:
			break;
	}
}

