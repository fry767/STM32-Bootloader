#include "bootloaderhw.h"
#include "bootlib.h"
#include "Bootloader_Settings.h"

#define FLASH_SIZE FLASH_SIZE_DATA_REGISTER
#define ADDRESS_IS_OUTSIDE_AREA(Address,LowerLimit,UpperLimit) (Address > UpperLimit-1 || Address < LowerLimit)?1:0


static uint32_t storage_address[2] ;
static uint32_t app_address[2];
static uint32_t Current_Store_Address;
static uint32_t Current_App_Address;

<<<<<<< HEAD
uint32_t Bootloader_Read(uint32_t Address)
=======
/**
  * @brief  Read the value of the flash at the given address.
  * @note 	I've add some protection to not let you read not readable address.
  * 		This resulted in infinite loop.
  * @param  Address : Address where you want to read a value
  * @retval Value read at the given address
  */
static uint32_t Bootloader_Read(uint32_t Address)
>>>>>>> d5360eef85482471922c86c17e168608071935b1
{
	if(!IS_FLASH_PROGRAM_ADDRESS(Address))
		return 0;
	if(ADDRESS_IS_OUTSIDE_AREA(Address,app_address[0],storage_address[1]))
	{
		return 0;
	}else
	{
		return (*((uint32_t*)Address));
	}
}
/**
  * @brief Write a given value at a given address that will increment by word for
  * 	   the next write
  * @note There is no protection in this method. I've write other function
  * that take this one and these one have protection.
  * @param  Value : value to write in flash in 32 bits
  * @param  Address : pointer to the address that you want to write in flash
  * @note I'm taking the pointer here because i will update the address
  * value for the next write
  * @retval 1 if the write is successful
  * 		0 if the write failed
  */
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
/**
  * @brief  Erase the flash depending on the settings of the struct
  * @param  EraseStruct : pointer to an FLASH_EraseInitTypeDef structure that
  *         contains the configuration information for the erasing.

  * @retval 1 Erase Successful
  * 		0 Erase Failed
  */
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
/**
  * @brief  Write a value in the storage area.
  * @note 	If you use this method, you dont need to manage the address
  * 		the drivers will increment the address by itself. You only need to
  * 		give the actual received firmware
  * @param  Value : Value to write

  * @retval 1 Write Successful
  * 		0 Write Failed
  */
static uint8_t Bootloader_WriteStorage(uint32_t value)
{
	if(ADDRESS_IS_OUTSIDE_AREA(Current_Store_Address,storage_address[0],storage_address[1]))
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
/**
  * @brief  Write a value in the App area.
  * @note 	If you use this method, you dont need to manage the address
  * 		the drivers will increment the address by itself. You only need to
  * 		give the actual received firmware
  * @param  Value : Value to write
  * @retval 1 Write Successful
  * 		0 Write Failed
  */
static uint8_t Bootloader_WriteApp(uint32_t value)
{
	if(ADDRESS_IS_OUTSIDE_AREA(Current_App_Address,app_address[0],app_address[1]))
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
/**
  * @brief  Erase the area that will contains the application
  * @note You must have init the bootloader prior to this method because we need
  * the size of the different part to erase the app
  * @param  none

  * @retval 1 : Erase successful
  * 		0 : Erase failed
  *
  */
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
/**
  * @brief  Erase the area where we store the application
  * @note You must have init the bootloader prior to this method because we need
  * the size of the different part to erase the storage space
  * @param  none

  * @retval 1 : Erase successful
  * 		0 : Erase failed
  *
  */
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
/**
  * @brief  Initialise the bootloader
  * @note   This method will only work on STM32 platform with the
  * 		FLASH_DATA_SIZE_REGISTER.
  * @param  none

  * @retval 1 : Erase successful
  * 		0 : Erase failed
  *
  */
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
/**
  * @brief  Write an 8 bit in the storage area
  * @param  none

  * @retval The read value at the given write address
  *
  *
  */
uint32_t Bootloader_WriteStorage8(uint8_t value)
{
	if(Bootloader_WriteStorage((uint32_t)value))
		return Bootloader_Read(Current_Store_Address-4);
	else
		return 0;
}
/**
  * @brief  Write a 32 bit in the storage area
  * @param  none

  * @retval The read value at the given write address
  *
  *
  */
uint32_t Bootloader_WriteStorage32(uint32_t value)
{
	if(Bootloader_WriteStorage(value))
			return Bootloader_Read(Current_Store_Address-4);
		else
			return 0;
}
/**
  * @brief  Write an 32 bit in the app area
  * @param  none

  * @retval The read value at the given write address
  *
  *
  */
uint32_t Bootloader_WriteApp32(uint32_t value)
{
	if(Bootloader_WriteApp(value))
			return Bootloader_Read(Current_App_Address-4);
		else
			return 0;
}
<<<<<<< HEAD
/* Use with caution. I only protect you from writing in the bootloader space and to access memory outside
 * the flash area*/
uint8_t Bootloader_ManualWrite(uint32_t value,uint32_t* Address)
{
	if(ADDRESS_IS_OUTSIDE_AREA(*Address,app_address[0],storage_address[1]))
	{
		return 0;
	}else
	{
		if(Bootloader_Write(value,Address))
			return 1;
		else
			return 0;
	}
}
=======
/**
  * @brief  Copy the app store in the storage area in the app area for
  * 		further jumping.
  * @param none
  * @retval 1 : Copy Successful
  * 		0 : Copy Failed
  *
  */
>>>>>>> d5360eef85482471922c86c17e168608071935b1
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
uint32_t* Bootloader_GetStorageAddress(void)
{
	return storage_address;
}
uint32_t* Bootloader_GetAppAddress(void)
{
	return app_address;
}

