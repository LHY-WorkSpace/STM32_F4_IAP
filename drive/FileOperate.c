#include "IncludeFile.h"



static FATFS fs;
static FIL fils;
static DIR dp;		
// static FILINFO fno;
static u32 DataPointer;







//初始化文件系统
u8 File_FATFSInit()
{
    
		GPIO_InitTypeDef GPIOA_Initstruc;
        	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);	

		GPIOA_Initstruc.GPIO_Pin=GPIO_Pin_8;
		GPIOA_Initstruc.GPIO_Mode=GPIO_Mode_IN;
		GPIOA_Initstruc.GPIO_PuPd=GPIO_PuPd_UP;
		GPIOA_Initstruc.GPIO_OType=GPIO_OType_PP; 
	  	GPIOA_Initstruc.GPIO_Speed=GPIO_Speed_50MHz;           
		GPIO_Init(GPIOA,&GPIOA_Initstruc);

    return disk_initialize(DEV_SD);
}

//挂载设备：   "1:"
u8 File_MountDisk(const char* Path)
{
	return f_mount(&fs,Path,1);
}

//卸载设备
u8 File_UmountDiak(const char* Path)
{
    return f_mount(0,Path,0);
}

//创建文件系统
u8 File_CreateFAT()
{
    u8 work[512];
    return f_mkfs("1",FM_FAT|FM_SFD,512,work,sizeof(work));
}



//Directory Operate 文件夹操作
//打开文件夹
u8 File_OpenDir(const char* Path)
{
    return f_opendir(&dp,Path);
}

//关闭文件夹
void File_CloseDir()
{
    f_close(&fils);
}

//创建文件夹
u8 File_Mkdir(const char * Path)
{
    return f_mkdir(Path);
}



u8 File_ScanIndex(const char* Path,u8* Num ,FileName NameList)
{


return 0;

}




//File Operate   文件操作
//创建新文件,如果已存在，则删除重新创建
u8 File_CreateNewFile(const char* Path)
{
    u8 sta;

    sta = f_open(&fils,Path,FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);

    if( sta == FR_EXIST)
    {
        sta = f_unlink(Path);
        sta = f_open(&fils,Path,FA_CREATE_ALWAYS|FA_WRITE|FA_CREATE_NEW);
    }
    f_close(&fils);	
    return sta;
}


//读取数据
u8 File_ReadData(const char* Path,u8* Data,u16 Length,u32 Offset)
{
    u8 sta;

    sta=f_open(&fils,Path,FA_READ|FA_OPEN_EXISTING);

    if( Offset != 0)
    {
        f_lseek(&fils,Offset);
    }

    if( sta == FR_OK)
    {
        sta=f_read(&fils,Data,Length,&DataPointer);
    }
    f_close(&fils);
     return sta;
}


//写入数据
u8 File_WriteData(const char* Path,u8* Data,u16 Length,u32 Offset)
{
    u8 sta;

    sta=f_open(&fils,Path,FA_WRITE|FA_OPEN_EXISTING);
     
    if( Offset != 0)
    {
        f_lseek(&fils,Offset);
    }

    if( sta == FR_OK)
    {
        sta =f_write(&fils,Data,Length,&DataPointer);
    }
    f_close(&fils);
    return sta;

}




//只能获取文件的大小，无法获取文件夹的大小(字节)
u32 File_GetFileSize(const char* Path)
{
    u8 sta;
    FILINFO fno;

    sta=f_stat(Path,&fno);

    if( sta != FR_OK)
    {
        return sta;
    }
    else
    {   
        return (u32)fno.fsize;
    }
}






void File_GetFileNameList(void)
{




}


//修改文件名
u8 File_Rename(const char* path_old, const char* path_new)
{
    return f_rename( path_old, path_new);
}


//删除文件
u8 File_Delete(const char* path)
{
    return f_unlink(path);
}





























