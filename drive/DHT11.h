#ifndef  DHT11_H
#define  DHT11_H



u8 DHT11_Init(void);


void DHT11_Read_Data(u8 *temp,u8 *humi);//��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
 
void DHT11_IO_IN(void);
void DHT11_IO_OUT(u8 DHT11_IO_CMD);


#endif



