/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "IncludeFile.h"


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = RES_OK;
	//int result;----------------------------------------------------------

	switch (pdrv) {
	case DEV_RAM :
	//	result = RAM_disk_status();--------------------------------------------

		// translate the reslut code here

		return stat;

	case DEV_SD :
		//result = MMC_disk_status();---------------------------------------------

		// translate the reslut code here

		return stat;

	case DEV_USB :
	//	result = USB_disk_status();------------------------------

		// translate the reslut code here

		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	u8 Sta;

	switch (pdrv) {
	case DEV_RAM :

		return Sta;

	case DEV_SD :

        Sta =  SD_Init();

		if( Sta != SD_OK )
		{
			return RES_ERROR;
		}
		else
		{
			return RES_OK;
		}

	case DEV_USB :

		return Sta;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */                               //LBAÂß¼­ÉÈÇø           https://blog.csdn.net/limanjihe/article/details/52302711
	UINT count		/* Number of sectors to read */
)
{
	u8 Sta;
//	DWORD Physical_sector;
//	int result;-----------------------------------------------------------

	
//	Physical_sector=(2048+sector)*512;
	
	
	switch (pdrv) 
	{
	case DEV_RAM :
		return RES_NOTRDY;

	case DEV_SD :

			Sta = SD_ReadDisk(buff, sector,count); 

			if( Sta != SD_OK )
			{
				return RES_ERROR;
			}
			else
			{
				return RES_OK;
			}
			

	case DEV_USB :
				return RES_ERROR;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	u8 Sta;


	switch (pdrv)
		{
		case DEV_RAM :

			return RES_NOTRDY;
		case DEV_SD :

			Sta = SD_WriteDisk( (u8*) buff, sector, count); 

			if( Sta != SD_OK )
			{
				return RES_ERROR;
			}
			else
			{
				return RES_OK;
			}

		case DEV_USB :


			return RES_NOTRDY;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
//	int result;----------------------------------------------------------

	switch (pdrv)
		{
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_SD :
			switch ( cmd )
			{			//fatfs????cmd??
				case GET_SECTOR_COUNT:	//sector count, ??sect_cnt
					*(DWORD*)buff = (SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize);
					return RES_OK;
				case GET_SECTOR_SIZE:	//sector size, ??block size(SD),??bytes
					*(DWORD*)buff = 512;
					return RES_OK;
				case GET_BLOCK_SIZE:	//block size, ????????SD2.0???8192??? 1
					*(DWORD*)buff = 1;	//??? sector(FatFs)
					return RES_OK;
				case CTRL_SYNC:			//???????FatFs?????????????
					return RES_OK;
			}
		default:
			printf( "No device %d.\n", pdrv );
			break;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	  }

	return RES_PARERR;
}

