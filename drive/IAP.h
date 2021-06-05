#ifndef IAP_H
#define IAP_H










//FLASH�ܴ�С  512k
#define FLASH_SIZE             ((u32)0x00080000)


//IAP������ʼ��ַ
#define BOOTLOADER_BASE_ADDR    ((u32)0x08000000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00004000)   //��С 16K



//Ӧ�ó�����ʼ��ַ
#define USERCODE_BASE_ADDR      ( (u32) BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 
#define USERCODE_CODE_SIZE      ( (u32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //��С 496k




#define DATA_BUFFER             ((u16)0x1000)  //���ݻ��� 4kB










#endif 




