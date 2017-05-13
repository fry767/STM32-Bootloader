#include <bootloaderhw.h>
#include <com_interface.h>
#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_uart.h>
#include <string.h>
#include <sys/_stdint.h>
#include <usart.h>
#include "test_comm.h"
#include "protocole.h"

#define TIMEOUT_VALUE	10000 /* 1ms counter (Systick)*/

extern uint8_t usart1_rx_flag;

uint8_t test_ReceptionInBlockingMode(void)
{
	uint8_t value = 0;
	Receive_Char_In_Blocking_Mode(&value,1);

	if(value == 0x7E)
	{
		char ch[] = "ReceptionInBlockingMode PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "ReceptionInBlockingMode Failed\n\r";
		Send_Char(ch,sizeof(ch));
	}
}
uint8_t test_ReceptionInNonBlockingMode(void)
{
	uint8_t value = 0;
	Receive_Char_In_IT_Mode(&value,1);
	if(value == 0x7E)
	{
		char ch[] = "test_ReceptionInNonBlockingMode PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_ReceptionInNonBlockingMode Failed\n\r";
		Send_Char(ch,sizeof(ch));
	}
}
uint8_t test_MultipleNonBlockingModeReception(void)
{
	uint32_t value = 0;
	uint8_t flag_rcv_error = 0;

	flag_rcv_error = Receive_Char_In_IT_Mode((uint8_t*)&value,4);

	if(flag_rcv_error == 4)
	{
		char ch[] = "test_MultipleNonBlockingModeReception PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_MultipleNonBlockingModeReception Failed\n\r";
		Send_Char(ch,sizeof(ch));
	}
}
uint8_t test_SendHomeMenu(void)
{
	uint8_t value = 0;
	Send_Home_Menu();
	if(Comm_USART_Wait_For_Key("~"))
	{
		char ch[] = "test_SendHomeMenu PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_SendHomeMenu Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
uint8_t test_WriteReceivedDataInFlash(void)
{
	uint32_t Value_Read_In_Flash = 0;
	uint8_t Received_Value = 0;

	if(!Bootloader_Init())
	{
		char ch[] = "Bootloader Init Failed Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

	char ch[] = "Bootloader initialized for test_WriteReceivedDataInFlash \n\r";
	Send_Char(ch,sizeof(ch));

	Receive_Char_In_IT_Mode(&Received_Value,1);
	Value_Read_In_Flash = Bootloader_WriteStorage8(Received_Value);
	if(Value_Read_In_Flash == Received_Value)
	{
		char ch[] = "test_WriteReceivedDataInFlash PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
uint8_t test_MultipleWriteReceivedDataInFlash(void)
{
	uint32_t Value_Read_In_Flash = 0;
	uint32_t Received_Value = 0 ;

	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

	char ch[] = "Bootloader initialized for test_MultipleWriteReceivedDataInFlash\n\r";
	Send_Char(ch,sizeof(ch));


	Receive_Char_In_IT_Mode((uint8_t*)&Received_Value,4);
	Value_Read_In_Flash = Bootloader_WriteStorage32(Received_Value);

	if(Value_Read_In_Flash == Received_Value)
	{
		char ch[] = "test_MultipleWriteReceivedDataInFlash PASS\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_MultipleWriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
uint8_t test_WriteLargerThanAvailableFiles(void)
{
	uint32_t Number_Of_Write = 55300/4;/* Only 54k available in Storage*/
	uint32_t Actual_Number_Of_Write = 0;
	uint32_t Received_Value = 0;
	uint16_t i = 0;

	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

	char ch[] = "Bootloader initialized for test_WriteLargerThanAvailableFile \n\r";
	Send_Char(ch,sizeof(ch));

	for(i = 0;i < Number_Of_Write; i++)
	{
		if(Receive_Char_In_IT_Mode((uint8_t*)&Received_Value,4) == 4)
		{
			if(Bootloader_WriteStorage32(Received_Value) == 0)
				break;
			Actual_Number_Of_Write++;
		}
		else
			return 0;
	}
	if(Actual_Number_Of_Write == (54*1024)/4)
	{
		char ch[] = "test_WriteLargerThanAvailableFiles Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
}
	else
	{
		char ch[] = "test_WriteLargerThanAvailableFiles Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}


}
uint8_t test_WriteFirmware(void)
{
	uint32_t Number_Of_Write = 20000/4;
	uint32_t Actual_Number_Of_Write = 0;
	uint32_t Received_Value = 0;
	uint16_t i = 0;

	if(!Bootloader_Init())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
	if(!Bootloader_EraseApp())
	{
		char ch[] = "test_WriteReceivedDataInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
	char ch[] = "Bootloader initialized for test_WriteFirmware \n\r";
	Send_Char(ch,sizeof(ch));

	for(i = 0;i < Number_Of_Write; i++)
	{
		if(Receive_Char_In_IT_Mode((uint8_t*)&Received_Value,4) == 4)
		{
			Bootloader_WriteApp32(Received_Value);
			Actual_Number_Of_Write++;
		}
		else
			break;
	}
	Bootloader_JumpToApplication();
}
uint8_t test_CommunicationParameterInit(void)
{
	Comm_Parameter_Struct testComParam;
	testComParam.BootKey = "";
	testComParam.FirmwareLength = 0xFFFFFFFF;
	testComParam.PacketCRC = 0x12345678;
	Comm_ParameterInitialise(&testComParam,"MDKEY");
	if(testComParam.FirmwareLength == 0 && testComParam.PacketCRC == 0)
	{
		char ch[] = "test_CommunicationParameterInit Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_CommunicationParameterInit Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

}

uint8_t test_CommunicationPollForFirmware(void)
{
	Comm_Parameter_Struct testComParam;
	Comm_ParameterInitialise(&testComParam,"MDKEY");

	if(Comm_Poll_For_Firmware_Key())
	{
		char ch[] = "test_CommPollForFirmware Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_CommPollForFirmware Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

}
uint8_t test_CommunicationSecurityCalculation(void)
{
	Comm_Parameter_Struct testComParam;
	Comm_ParameterInitialise(&testComParam,"MDKEY");

	char Message_to_encrypt[] = "ALLOQWERTY12";
	CommunicationSecurityAdd(Message_to_encrypt,12);
	uint8_t ActualCheckSum = CommunicationSecurityCalc();

	if(ActualCheckSum == 0x89)
	{
		char ch[] = "test_CommunicationSecurityCalculation Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_CommunicationSecurityCalculation Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
uint8_t test_CommunicationGetFirmwareInfo(void)
{
	Comm_Parameter_Struct testComParam;
	Comm_ParameterInitialise(&testComParam,"MDKEY");

	Communication_Poll_For_Firmware_Info();

	if(testComParam.BootKey == "MDKEY" &&
			testComParam.FirmwareLength == 17516 &&
			testComParam.PacketCRC == 0x0000)
	{
		char ch[] = "test_CommunicationGetFirmwareInfo Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_CommunicationGetFirmwareInfo Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
uint8_t test_CommunicationGetFirmwareAndChecksum(void)
{
	Comm_Parameter_Struct testComParam;
	Comm_ParameterInitialise(&testComParam,"MDKEY");

	Bootloader_Init();
	Bootloader_EraseStorage();
	char ch[] = "BootloaderInitialise";
	Send_Char(ch,sizeof(ch));
	Communication_Poll_For_Firmware_Info();
	if(testComParam.BootKey == "MDKEY")
	{
		Communication_Receive_Firmware_And_Store();
	}
	uint8_t checksum = Communication_Receive_Checksum();
	if(checksum == Calculate_Checksum_From_Storage())
	{
		char ch[] = "test_CommunicationGetFirmwareAndChecksum Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_CommunicationGetFirmwareAndChecksum Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

}
void runAllCommTest(void)
{
	char ch[] = "Starting Com Test\n\r";
	Send_Char(ch,sizeof(ch));

	/* Reception Test*/
	/*test_ReceptionInBlockingMode();
	test_ReceptionInNonBlockingMode();
	test_MultipleNonBlockingModeReception();*/

	/* Send Test */
	/*test_SendHomeMenu();*/

	/* Receive and Write in Flash Test */
	/*test_WriteReceivedDataInFlash();
	test_MultipleWriteReceivedDataInFlash();
	test_WriteLargerThanAvailableFiles();
	test_WriteFirmware();*/

	/*Protocol Test*/
	/*test_CommunicationParameterInit();
	test_CommunicationPollForFirmware();
	test_CommunicationSecurityCalculation();*/
	//test_CommunicationGetFirmwareInfo();
	test_CommunicationGetFirmwareAndChecksum();
}
