#ifndef   __SD_H
#define   __SD_H
#include "stm32f4xx_sdio.h"


	

/********************************************命令索引************************/
#define CMD0           0                               
#define CMD1           1
#define CMD2           2                    //CMD2-获取CID
#define CMD3           3                    ///CMD3-获取RCA
#define CMD4           4                    ///设置SD传输速度
#define CMD5           5
#define CMD6           6
#define CMD7           7
#define CMD8           8
#define CMD9           9                   //CSD获取卡的存储信息//
#define CMD10          10                  //CID
#define CMD11          11



#define CMD12          12                  //CMD12-停止传输
#define CMD13          13                  //获取卡状态

#define CMD16          16                  //设置块大小(字节数)

#define CMD17          17                  //读取单个块
#define CMD18          18                  //读取多个块，直到发送CMD12

#define CMD24          24                   //写入单个块
#define CMD25          25                   //写入多个块

#define CMD23          23                  //预擦除

#define CMD32          32                  //擦除一个块(起始地址)
#define CMD33          33                  //擦除一个块(终止地址)
#define CMD38          38                  //选择好起始终止地址后，启动擦除



#define CMD52          52
#define CMD53          53
#define CMD55          55
#define CMD41          41


/*   OCR   */
//#define HCS            (1<<30)       /*      bit[30]   SDSC: 0         SDHC/SDXC: 1        */
//#define VOL_RANGE      () 


#define CMD11          11
#define CMD52          52
#define CMD53          53
#define CMD55          55
#define CMD41          41






#define HIGH_SPEED_SDCLK         6       //初始化完成后高速传输----0~25Mhz   48/[6+2]=6MB/S
#define LOW_SPEED_SDCLK          240     //低速初始化-------------<400KHz   100K



#define  N_RESPONSE     SDIO_Response_No               //响应类型
#define  S_RESPONSE     SDIO_Response_Short
#define  L_RESPONSE     SDIO_Response_Long

#define  BLOCK_SIZE     512



#define  DATA_TIME_OUT     0xFFFFFFF0

typedef enum
{
		SDIO_OK                        =0,

		SDIO_CCRCFAIL                    =1,
		SDIO_DCRCFAIL                    =2,
		SDIO_CTIMEOUT                    =3,
		SDIO_DTIMEOUT                    =4,
		SDIO_TXUNDERR                    =5,
		SDIO_RXOVERR                     =6,
		SDIO_CMDREND                     =7,
		SDIO_CMDSENT                     =8,
		SDIO_DATAEND                     =9,
		SDIO_STBITERR                    =10,
		SDIO_DBCKEND                     =11,
		SDIO_CMDACT                      =12,
		SDIO_TXACT                       =13,
		SDIO_RXACT                       =14,
		SDIO_TXFIFOHE   	                =15,
		SDIO_RXFIFOHF   	                =16,
		SDIO_TXFIFOF    	                =17,
		SDIO_RXFIFOF    	                =18,
		SDIO_TXFIFOE    	                =19,
		SDIO_RXFIFOE    	                =20,
		SDIO_TXDAVL     	                =21,
		SDIO_RXDAVL     	                =22,
		SDIO_SDIOIT     	                =23,
		SDIO_CEATAEND   	                =24,
																					

		SD_timeout                     =25,
		SD_UNKNOWCARD                  =26

}SD_error;

typedef enum
{
		SDIO_High_Speed=HIGH_SPEED_SDCLK,    
		SDIO_Low_Speed=LOW_SPEED_SDCLK     
}SDIO_Speed;

typedef enum
{
	TO_SD_CARD =SDIO_TransferDir_ToCard,             
	TO_SDIO=SDIO_TransferDir_ToSDIO 
}SDIO_Dirction;


typedef enum
{
	SD_CARD_WIDTH_1b=0X00,          
	SD_CARD_WIDTH_4b=0X02

}SD_TransmissionWide;

typedef enum
{
	SDIO_Buswide_1b =((uint32_t)0x00000000),
	SDIO_Buswide_4b =((uint32_t)0x00000800),
	SDIO_Buswide_8b =((uint32_t)0x00001000)
}SDIO_Buswide;

typedef enum
{
	SD_SC=0x00,
	SD_HC

}SD_Type;

typedef enum
{
	SD_V1=0x00,
	SD_V2

}SD_Version;




typedef struct 
{

	SD_Type SD_type;                        //SDSC/SDHC
	SD_Version SD_version;                  //v2/v1
	u32 SD_RCA;                            //RCA
 	u32 SD_Block_Size;
	u32 SD_MID;
 	u32 SD_SN;
	u32 SD_Memory;
	u8 SD_InsideState;
	u8 READ_BL_LEN;
	u32 C_SIZE;
	u32 C_SIZE_MULT;
	int MULT;
	u32 CSD[4];
	
}SD_Information;







SD_error CMD_ERROR(void);
SD_error SD_CARD_Init(void );
void CMD_Number_Argument_Responsetype(u8 CMD_x, u32 argument,u32 response_type);
SD_error SD_powerON(void);
void SDIO_SetBusWide(SDIO_Buswide SDIO_wide);
void SDIO_SetSpeed(SDIO_Speed SDIO_speed);
SD_error SD_SetTransmissionWide(SD_TransmissionWide TransmissionWide);
SD_error SD_Select(void);
SD_error SD_CSDInfo(void);
SD_error SD_RCAInfo(void);
SD_error SD_ManufactoryInfo(void);
SD_error SD_TypeInformation(void);
u8 SD_GetVersion(void);
void SDIO_Data_Set(u32 N_BLOCK_SIZE,SDIO_Dirction direction);

SD_error SD_Read_Block(u32 *buffer,u32 Physical_BLOCK_ADDR);
SD_error SD_Write_Block(u32 *buffer,u32 Physical_BLOCK_ADDR);
SD_error SD_Read_MultiBlocks(u32 *buffer,u32 Physical_BLOCK_ADDR,u8 count);
SD_error SD_Write_MultiBlocks(u32 *buffer,u32 Physical_BLOCK_ADDR,u8 count);



#endif

