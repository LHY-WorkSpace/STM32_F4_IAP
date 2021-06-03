#ifndef  FILEOPERATE_H
#define  FILEOPERATE_H

//最大支持30字节文件名长度
#define FILE_MAX_NAME_LENGTH        (30)




typedef struct
{
	u8 Length;
	char Name[FILE_MAX_NAME_LENGTH];
}FileName;



//System Operate 系统操作
u8 File_FATFSInit(void);
u8 File_MountDisk(const char* Path);
u8 File_UmountDiak(const char* Path);
u8 File_CreateFAT(void);


//Directory Operate 文件夹操作
u8 File_OpenDir(const char* Path);
void File_CloseDir(void);
u8 File_ScanIndex(const char* Path,u8* Num ,FileName NameList);
u8 File_Mkdir(const char * Path);



//File Operate   文件操作
u8 File_CreateNewFile(const char* Path);
u8 File_ReadData(const char* Path,u8* Data,u16 Length,u32 Offset);
u8 File_WriteData(const char* Path,u8* Data,u16 Length,u32 Offset);
u32 File_GetFileSize(const char* Path);
void File_GetFileNameList(void);
u8 File_Rename(const char* path_old, const char* path_new);
u8 File_Delete(const char* path);






#endif

