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
void Bootloader_CalculateSectorForStorage(uint16_t size,uint32_t* erase_address)
{
	uint16_t table[3];
	Bootloader_SplitFlash(size,&table);
	erase_address[0] = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE + (uint32_t)ApplicationSize*FLASH_PAGE_SIZE;
	erase_address[1] = erase_address[0] + (uint32_t)StorageSize*FLASH_PAGE_SIZE;
}
void Bootloader_CalculateSectorForApp(uint16_t size,uint32_t* app_address)
{
	uint16_t table[3];
	Bootloader_SplitFlash(size,&table);
	app_address[0] = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE;
	app_address[1] = START_FLASH_ADDRESS + (uint32_t)BootloaderSize*FLASH_PAGE_SIZE + (uint32_t)ApplicationSize*FLASH_PAGE_SIZE;
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
