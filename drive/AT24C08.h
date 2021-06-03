#ifndef  _AT24C08_H_
#define  _AT24C08_H_

//AT24C08的器件地址高四位固定，低四位的BIT2 BIT3 将器件分为4个块，每个256字节，所以数据地址最大一个字节，跨块读写需修改器件地址低四位的BIT2 BIT3
#define AT24C08_ADDRESS                (0xA0)                   //AT24C02 device address
#define AT24C08_BLOCK1                 (AT24C08_ADDRESS|0x00)                                   
#define AT24C08_BLOCK2                 (AT24C08_ADDRESS|0x02)                                 
#define AT24C08_BLOCK3                 (AT24C08_ADDRESS|0x04)                                    
#define AT24C08_BLOCK4                 (AT24C08_ADDRESS|0x06)                                  

void AT24C08_init(void);
u8 AT24C08Read_Byte(u8 dev_addr,u8 Data_addr);
void AT24C08Write_Byte(u8 dev_addr,u8 Data_addr,u8 data);
void AT24C08Read_NBytes(u8 dev_addr,u8 addr,u16 length,u8 *data);
void AT24C08Write_NBytes(u8 dev_addr,u8 addr,u16 length,u8 *data);


#endif



