#ifndef   DS18B20_H
#define   DS18B20_H



int ds18B20_init(char CMD);
int ds18b20_read_byte(void);
void ds18b20_write_byte(u32 data);
void tempure_value_OLEDdisplay(char x,char y);
void Get_Temperature(u8 *Temp);


#endif


























