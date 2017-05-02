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
		printf("Init Boot PASS\n");
		return 1;
	}
	else
	{
		printf("Init Boot Failed\n");
		return 0;
	}

}
static uint8_t test_VerifyDataWrittenInFlash(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t expectedFlashValue = 0x00000055;
	uint32_t Address_to_Write = START_FLASH_ADDRESS + (boot_pages+app_pages)*FLASH_PAGE_SIZE;

	result = Bootloader_WriteStorage8(expectedFlashValue,&Address_to_Write);

	if(result == expectedFlashValue)
	{
		printf("VerifyDataWrittenInFlash PASS\n");
		return 1;
	}
	else
	{
		printf("VerifyDataWrittenInFlash Failed\n");
		return 0;
	}

}
static uint8_t test_Verify32BitWrittenInFlash(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t expectedFlashValue = 0x12345678;
	uint32_t Address_to_Write = START_FLASH_ADDRESS + (boot_pages+app_pages)*FLASH_PAGE_SIZE + 4;

	result = Bootloader_WriteStorage32(expectedFlashValue,&Address_to_Write);
	if(result == expectedFlashValue)
	{
		printf("Verify32BitWrittenInFlash PASS\n");
		return 1;
	}
	else
	{
		printf("Verify32BitWrittenInFlash Failed\n");
		return 0;
	}
}
static uint8_t test_VerifyMultipleWriteInFlash(void)
{
	uint32_t result1 = FLASH_ERASE_VALUE;
	uint32_t result2 = FLASH_ERASE_VALUE;
	uint32_t expectedFlashValue1 = 0x12345678;
	uint32_t expectedFlashValue2 = 0x87654321;
	uint32_t Address_to_Write = START_FLASH_ADDRESS + (boot_pages+app_pages)*FLASH_PAGE_SIZE + 8;

	result1 = Bootloader_WriteStorage32(expectedFlashValue1,&Address_to_Write);
	result2 = Bootloader_WriteStorage32(expectedFlashValue2,&Address_to_Write);

	if(result1 == expectedFlashValue1 && result2 == expectedFlashValue2)
	{
		printf("VerifyMultipleWriteInFlash PASS\n");
		return 1;
	}
	else
	{
		printf("VerifyMultipleWriteInFlash Failed\n");
		return 0;
	}


}
static uint8_t test_UpperBoundWrite(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t Address_to_Write = START_FLASH_ADDRESS + (FLASH_SIZE)*FLASH_PAGE_SIZE;

	result = Bootloader_WriteStorage32(0x12345678,&Address_to_Write);

		if(result == 0)
		{
			printf("UpperBoundWrite PASS\n");
			return 1;
		}
		else
		{
			printf("UpperBoundWrite Failed\n");
			return 0;
		}
}
static uint8_t test_LesserBoundWrite(void)
{
	uint32_t result = FLASH_ERASE_VALUE;
	uint32_t Address_to_Write = 0x07FFFFFF;

	result = Bootloader_WriteStorage32(0x12345678,&Address_to_Write);

	if(result == 0)
	{
		printf("LesserBoundWrite PASS\n");
		return 1;
	}
	else
	{
		printf("LesserBoundWrite Failed\n");
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
		printf("CopyStorageSpaceInAppSpace PASS\n");
		return 1;
	}
	else
	{
		printf("CopyStorageSpaceInAppSpace Failed\n");
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
		printf("EraseApp PASS\n");
		return 1;
	}
	else
	{
		printf("EraseApp Failed\n");
		return 0;
	}
}

void runAllTest(void)
{
	uint8_t test_status[20] = {0};
	uint8_t i=0;
	init_test();
	test_status[i++] = test_InitBootloader();
	test_status[i++] = test_EraseApp();
	test_status[i++] = test_VerifyDataWrittenInFlash();
	test_status[i++] = test_Verify32BitWrittenInFlash();
	test_status[i++] = test_UpperBoundWrite();
	test_status[i++] = test_LesserBoundWrite();
	test_status[i++] = test_VerifyMultipleWriteInFlash();
	test_status[i++] = test_CopyStorageSpaceInAppSpace();
}
