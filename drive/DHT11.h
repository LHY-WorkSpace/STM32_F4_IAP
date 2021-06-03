#ifndef  DHT11_H
#define  DHT11_H



u8 DHT11_Init(void);


void DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
 
void DHT11_IO_IN(void);
void DHT11_IO_OUT(u8 DHT11_IO_CMD);


#endif



