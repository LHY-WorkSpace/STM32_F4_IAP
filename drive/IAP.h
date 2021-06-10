#ifndef IAP_H
#define IAP_H



//FLASH�ܴ�С  512k
#define FLASH_SIZE             ((u32)0x00080000)

//FLASH�ܴ�С  512k
#define SECTOR_0_SIZE      ( (u32) 16*1024 )  
#define SECTOR_1_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_2_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_3_SIZE      ( (u32) 16*1024 ) 
#define SECTOR_4_SIZE      ( (u32) 64*1024 ) 
#define SECTOR_5_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_6_SIZE      ( (u32) 128*1024 ) 
#define SECTOR_7_SIZE      ( (u32) 128*1024 ) 

//IAP������ʼ��ַ
#define BOOTLOADER_BASE_ADDR    ((u32)0x08000000)      
#define BOOTLOADER_CODE_SIZE    ((u32)0x00004000)   //IAP ��С 16K



//Ӧ�ó�����ʼ��ַ
#define USERCODE_BASE_ADDR      ( (u32) BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 
#define USERCODE_CODE_SIZE      ( (u32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //Ӧ�ô�С 496k


//Ӧ�ó�����ʼ��ַ
#define USERCODE_BASE_ADDR      ( (u32) BOOTLOADER_BASE_ADDR + BOOTLOADER_CODE_SIZE ) 
#define USERCODE_CODE_SIZE      ( (u32) FLASH_SIZE - BOOTLOADER_CODE_SIZE )    //Ӧ�ô�С 496k

#define DATA_BUFFER             ((u16)0x1000)  //���ݻ��� 4kB





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




