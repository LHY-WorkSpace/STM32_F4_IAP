#ifndef IAP_H
#define IAP_H

//IAP程序起始地址
#define BOOTLOADER_BASE_ADDR    ((u32)0x08000000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00003C00)   //大小 15K



//应用程序起始地址
#define USERCODE_BASE_ADDR      ( (u32)BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 





void 











#endif 




