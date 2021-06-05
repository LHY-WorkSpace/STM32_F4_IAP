#ifndef IAP_H
#define IAP_H










//FLASH总大小  512k
#define FLASH_SIZE             ((u32)0x00080000)


//IAP程序起始地址
#define BOOTLOADER_BASE_ADDR    ((u32)0x08000000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00004000)   //大小 16K



//应用程序起始地址
#define USERCODE_BASE_ADDR      ( (u32) BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 
#define USERCODE_CODE_SIZE      ( (u32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //大小 496k




#define DATA_BUFFER             ((u16)0x1000)  //数据缓冲 4kB










#endif 




