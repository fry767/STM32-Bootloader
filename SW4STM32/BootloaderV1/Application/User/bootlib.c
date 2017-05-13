#include "bootlib.h"
#include "bootlibHW.h" 
#include "Bootloader_Settings.h"
/* FLASH_PAGE_SIZE
   IS_FLASH_PROGRAM_ADDRESS(ADDRESS)
   IS_FLASH_NB_PAGES(ADDRESS,NBPAGE)*/

#define UART_POLLING_FUNC	1
#define SPI_POLLING_FUNC	0
#define I2C_POLLING_FUNC	0
#define CAN_POLLING_FUNC	0


static uint16_t BootloaderSize;
static uint16_t ApplicationSize;
static uint16_t StorageSize;
static char mode[4];

typedef void (*pFunction)(void);
pFunction Jump_To_Application;

/**
  * @brief This method split the flash in 3 part depending on the DEFINE of
  * the bootloader size.
  * @param  Size : The total size of the flash in Kb (Ex: 32,64,128,256)
  * @param  Splitted_Part : pointer to a table that will receive the length of
  * 		the 3 parts
  * @retval None
  */
void Bootloader_SplitFlash(uint16_t size, uint16_t *splitted_part)
{
	uint16_t remaining_size = size - BOOTLOADER_SIZE;
	BootloaderSize = BOOTLOADER_SIZE;
	ApplicationSize = remaining_size/2;
	StorageSize = ApplicationSize; 
	splitted_part[0] = BootloaderSize; 
	splitted_part[1] = ApplicationSize; 
	splitted_part[2] = StorageSize;
}
/**
  * @brief This method gives the start and end address of the storage area
  * 		depending on the size of the flash
  * @param  Size : The total size of the flash in Kb (Ex: 32,64,128,256)
  * @param  erase_address : pointer to a table that will receive the length of
  * 		the 2 address(start and end)
  * @retval None
  */
void Bootloader_CalculateSectorForStorage(uint16_t size,uint32_t* erase_address)
{
	uint16_t table[3];
	Bootloader_SplitFlash(size,&table);
	erase_address[0] = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE + (uint32_t)ApplicationSize*FLASH_PAGE_SIZE;
	erase_address[1] = erase_address[0] + (uint32_t)StorageSize*FLASH_PAGE_SIZE;
}
/**
  * @brief This method gives the start and end address of the app area
  * 		depending on the size of the flash
  * @param  Size : The total size of the flash in Kb (Ex: 32,64,128,256)
  * @param  app_address : pointer to a table that will receive the length of
  * 		the 2 address(start and end)
  * @retval None
  */
void Bootloader_CalculateSectorForApp(uint16_t size,uint32_t* app_address)
{
	uint16_t table[3];
	Bootloader_SplitFlash(size,&table);
	app_address[0] = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE;
	app_address[1] = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE + (uint32_t)ApplicationSize*FLASH_PAGE_SIZE;
}
/**
  * @brief This method is use to jump to the application written in the app area
  * @param  None
  * @retval None
  */
void Bootloader_JumpToApplication(void)
{
	uint32_t Application_Address = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE;
    uint32_t Program_Counter = Application_Address + 0x04;
	Jump_To_Application = (pFunction)(*(uint32_t *)(Program_Counter));

	__set_MSP(*(uint32_t*) Application_Address);

	Jump_To_Application();


}
char* Bootloader_Waiting_For_Key(void)
{	
	strcpy(mode,"none");
	if(Bootloader_UART_Poll())
		strcpy(mode,"uart");
	else if(Bootloader_SPI_Poll())
		strcpy(mode,"spi");
	else if(Bootloader_I2C_Poll())
		strcpy(mode,"i2c");
	else if(Bootloader_CAN_Poll())
		strcpy(mode,"can");
	else
		strcpy(mode,"NOIM");

	return mode;
}
