#include "test_FLASH_HW.h"
#include "bootloaderHW.h"
#include "bootlib.h"
#include "stm32f1xx_hal.h"
#include "Bootloader_Settings.h"

#define FLASH_SIZE (*((uint32_t*)FLASH_SIZE_DATA_REGISTER))
#define FLASH_ERASE_VALUE 0xFFFFFFFF
static uint16_t boot_pages;
static uint16_t app_pages;
static uint16_t storage_pages;

static void init_test(void)
{
	uint16_t boot_app_store_pages[3] = {0,0,0};
	Bootloader_SplitFlash((*((uint32_t*)FLASH_SIZE_DATA_REGISTER)),boot_app_store_pages);
	boot_pages = boot_app_store_pages[0];
	app_pages = boot_app_store_pages[1];
	storage_pages = boot_app_store_pages[2];
}
static uint8_t test_InitBootloader(void)
{
	uint32_t Start_of_Storage = START_FLASH_ADDRESS + (boot_pages+app_pages)*FLASH_PAGE_SIZE;
	uint32_t End_Of_Storage = START_FLASH_ADDRESS + (FLASH_SIZE)* FLASH_PAGE_SIZE;
	Bootloader_Init();
	uint32_t i = 0;
	uint8_t flag_erase_value = 1;
	for(i = Start_of_Storage;i < End_Of_Storage-4;i+=4)
	{
		if((*((uint32_t*)i)) != FLASH_ERASE_VALUE)
		{
			flag_erase_value = 0;
			break;
		}
	}
	if(flag_erase_value)
	{
		char ch[] = "test_InitBootloader Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_InitBootloader Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

}
static uint8_t test_VerifyDataWrittenInFlash(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t expectedFlashValue = 0x00000055;

	result = Bootloader_WriteStorage8(expectedFlashValue);

	if(result == expectedFlashValue)
	{
		char ch[] = "test_VerifyDataWrittenInFlash Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_VerifyDataWrittenInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}

}
static uint8_t test_Verify32BitWrittenInFlash(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t expectedFlashValue = 0x12345678;


	result = Bootloader_WriteStorage32(expectedFlashValue);
	if(result == expectedFlashValue)
	{
		char ch[] = "test_Verify32BitWrittenInFlash Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_Verify32BitWrittenInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
static uint8_t test_VerifyMultipleWriteInFlash(void)
{
	uint32_t result1 = FLASH_ERASE_VALUE;
	uint32_t result2 = FLASH_ERASE_VALUE;
	uint32_t expectedFlashValue1 = 0x12345678;
	uint32_t expectedFlashValue2 = 0x87654321;

	result1 = Bootloader_WriteStorage32(expectedFlashValue1);
	result2 = Bootloader_WriteStorage32(expectedFlashValue2);

	if(result1 == expectedFlashValue1 && result2 == expectedFlashValue2)
	{
		char ch[] = "test_VerifyMultipleWriteInFlash Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_VerifyMultipleWriteInFlash Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}


}
static uint8_t test_UpperBoundWrite(void)
{
	uint32_t result = FLASH_ERASE_VALUE;

	//result = Bootloader_WriteStorage32(0x12345678,&Address_to_Write);

	if(result == 0)
	{
		char ch[] = "test_UpperBoundWrite Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_UpperBoundWrite Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
static uint8_t test_LesserBoundWrite(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t Address_to_Write = 0x07FFFFFF;

	//result = Bootloader_WriteStorage32(0x12345678,&Address_to_Write);

	if(result == 0)
	{
		char ch[] = "test_LesserBoundWrite Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_LesserBoundWrite Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
static uint8_t test_CopyStorageSpaceInAppSpace(void)
{
	uint32_t i;
	uint32_t Address_of_Storage = START_FLASH_ADDRESS + (boot_pages+app_pages)*FLASH_PAGE_SIZE;
	uint32_t End_Of_Storage = START_FLASH_ADDRESS + (FLASH_SIZE)*FLASH_PAGE_SIZE ;
	uint32_t Address_Of_App = START_FLASH_ADDRESS + (boot_pages)*FLASH_PAGE_SIZE;
	//uint32_t End_Of_App = Address_of_Storage;
	uint8_t flag_same_data = 1;

	if(!Bootloader_CopyStorageInAppspace())
		return 0;

	for(i = 0; i < ((app_pages*FLASH_PAGE_SIZE)-4)/4 ; i++)
	{
		if((*((uint32_t*)Address_of_Storage)) != (*((uint32_t*)Address_Of_App)))
		{
			flag_same_data = 0;
			break;
		}
		Address_of_Storage +=4;
		Address_Of_App+=4;
		if(Address_of_Storage > End_Of_Storage-4)
			break;
	}
	if(flag_same_data)
	{
		char ch[] = "test_CopyStorageSpaceInAppSpace Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_CopyStorageSpaceInAppSpace Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
static uint8_t test_EraseApp(void)
{
	uint32_t Start_of_App = START_FLASH_ADDRESS + (boot_pages)*FLASH_PAGE_SIZE;
	uint32_t End_Of_App = START_FLASH_ADDRESS + (boot_pages+app_pages)* FLASH_PAGE_SIZE;
	uint32_t i = 0;
	uint8_t flag_erase_value = 1;
	Bootloader_EraseApp();
	for(i = Start_of_App;i < End_Of_App-4;i+=4)
	{
		if((*((uint32_t*)i)) != FLASH_ERASE_VALUE)
		{
			flag_erase_value = 0;
			break;
		}
	}
	if(flag_erase_value)
	{
		char ch[] = "test_EraseApp Pass\n\r";
		Send_Char(ch,sizeof(ch));
		return 1;
	}
	else
	{
		char ch[] = "test_EraseApp Failed\n\r";
		Send_Char(ch,sizeof(ch));
		return 0;
	}
}
void test_Bootloader_Jump_To_Application(void)
{
	//Bootloader_JumpToApplication();
}
void runAllTest(void)
{
	uint8_t test_status[20] = {0};
	uint8_t i=0;
	init_test();
	/*test_status[i++] = test_InitBootloader();
	test_status[i++] = test_EraseApp();
	test_status[i++] = test_VerifyDataWrittenInFlash();
	test_status[i++] = test_Verify32BitWrittenInFlash();
	test_status[i++] = test_VerifyMultipleWriteInFlash();
	test_status[i++] = test_CopyStorageSpaceInAppSpace();*/
	test_Bootloader_Jump_To_Application();
	/* Test Lib Bootlaoder*/



	/*test_status[i++] = test_UpperBoundWrite();
		test_status[i++] = test_LesserBoundWrite();*/
}
