#include "bootloaderhw.h"
#include "bootlib.h"
#include "Bootloader_Settings.h"

#define FLASH_SIZE FLASH_SIZE_DATA_REGISTER
#define ADDRESS_IS_OUTSIDE_STORAGE_AREA(Address,LowerLimit,UpperLimit) (Address > UpperLimit-1 || Address < LowerLimit)?1:0


static uint32_t storage_address[2] ;
static uint32_t app_address[2];
static uint32_t Current_Store_Address;
static uint32_t Current_App_Address;

static uint32_t Bootloader_Read(uint32_t Address)
{
	if(!IS_FLASH_PROGRAM_ADDRESS(Address))
		return 0;
	if(ADDRESS_IS_OUTSIDE_STORAGE_AREA(Address,app_address[0],storage_address[1]))
	{
		return 0;
	}else
	{
		return (*((uint32_t*)Address));
	}
}
static uint8_t Bootloader_Write(uint32_t value, uint32_t* Address)
{
	uint32_t value_to_flash = value & 0xFFFFFFFF;

	if(HAL_FLASH_Unlock()== HAL_OK)
	{
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,*Address,value_to_flash);
		HAL_FLASH_Lock();
		if(Bootloader_Read(*Address) == value_to_flash)
		{
			*Address +=4;
			return 1;
		}
		return 0;
	}
	return 0;
}
static uint8_t Bootloader_Erase(FLASH_EraseInitTypeDef* EraseStruct)
{
	uint32_t SectorError = 0;
	if(HAL_FLASH_Unlock()== HAL_OK)
	{
		HAL_FLASHEx_Erase(EraseStruct, &SectorError);
	}
	else
	{
		HAL_FLASH_Lock();
		return 0;
	}
	HAL_FLASH_Lock();
	return 1;
}
static uint8_t Bootloader_WriteStorage(uint32_t value)
{
	if(ADDRESS_IS_OUTSIDE_STORAGE_AREA(Current_Store_Address,storage_address[0],storage_address[1]))
	{
		return 0;
	}else
	{
		if(Bootloader_Write(value,&Current_Store_Address))
			return 1;
		else
			return 0;
	}
	return 0;
}
static uint8_t Bootloader_WriteApp(uint32_t value)
{
	if(ADDRESS_IS_OUTSIDE_STORAGE_AREA(Current_App_Address,app_address[0],app_address[1]))
		{
			return 0;
		}else
		{
			if(Bootloader_Write(value,&Current_App_Address))
				return 1;
			else
				return 0;
		}
		return 0;
}
uint8_t Bootloader_EraseApp(void)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks = FLASH_BANK_1;
	EraseInitStruct.PageAddress = app_address[0];
	EraseInitStruct.NbPages = (app_address[1]-app_address[0])/FLASH_PAGE_SIZE;

	if(!Bootloader_Erase(&EraseInitStruct))
		return 0;
	return 1;
}
uint8_t Bootloader_EraseStorage(void)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Banks = FLASH_BANK_1;
	EraseInitStruct.PageAddress = storage_address[0];
	EraseInitStruct.NbPages = (storage_address[1]-storage_address[0])/FLASH_PAGE_SIZE;

	if(!Bootloader_Erase(&EraseInitStruct))
			return 0;
		return 1;

}
uint8_t Bootloader_Init(void)
{
	uint16_t flash_size_data = (*((uint16_t *)FLASH_SIZE));

	storage_address[0] = 0;
	storage_address[1] = 0;
	app_address[0] = 0;
	app_address[1] = 0;

	Bootloader_CalculateSectorForStorage(flash_size_data,&storage_address);
	Bootloader_CalculateSectorForApp(flash_size_data,&app_address);

	Current_Store_Address = storage_address[0];
	Current_App_Address = app_address[0];

	if(!Bootloader_EraseStorage())
		return 0;
	return 1;
}
uint32_t Bootloader_WriteStorage8(uint8_t value)
{
	if(Bootloader_WriteStorage((uint32_t)value))
		return Bootloader_Read(Current_Store_Address-4);
	else
		return 0;
}
uint32_t Bootloader_WriteStorage32(uint32_t value)
{
	if(Bootloader_WriteStorage(value))
			return Bootloader_Read(Current_Store_Address-4);
		else
			return 0;
}

uint8_t Bootloader_CopyStorageInAppspace(void)
{
	uint32_t i = 0;
	uint32_t app_size = (app_address[1] - app_address[0]);
	uint32_t number_of_write = app_size/4;
	uint32_t Storage_address_to_cpy = storage_address[0];

	if(!Bootloader_EraseApp())
		return 0;
	for(;i < number_of_write;i++)
	{
		if(Bootloader_WriteApp((*((uint32_t*)Storage_address_to_cpy))))
		{
			Storage_address_to_cpy+=4;
		}
		else
			break;
	}
	if(i == number_of_write)
		return 1;

	return 0;
}

