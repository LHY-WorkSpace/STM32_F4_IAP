#ifndef IAP_H
#define IAP_H



//FLASH总大小  512k
#define FLASH_SIZE             ((u32)0x00080000)

//FLASH总大小  512k
#define SECTOR_0_SIZE      ( (u32) 16*1024 )  
#define SECTOR_1_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_2_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_3_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_4_SIZE      ( (u32) 64*1024 ) 
#define SECTOR_5_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_6_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_7_SIZE      ( (u32) 128*1024 ) 

//IAP程序起始地址
#define BOOTLOADER_BASE_ADDR    ((u32)0x08000000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00004000)   //IAP 大小 16K



//应用程序起始地址
#define USERCODE_BASE_ADDR      ( (u32) BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 
#define USERCODE_CODE_SIZE      ( (u32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //应用大小 496k


//应用程序起始地址
#define USERCODE_BASE_ADDR      ( (u32) BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 
#define USERCODE_CODE_SIZE      ( (u32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //应用大小 496k

#define DATA_BUFFER             ((u16)0x1000)  //数据缓冲 4kB





typedef enum
{
    ACanNotRead,
    ACanRead,
    BCanNotRead,
    BCanRead,
    Busy
}Read_State;



typedef enum
{
    BufferB_Empty,
    BufferA_Empty,
}Buffer_State;
















#endif 




