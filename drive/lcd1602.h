#ifndef   LCD1602_H
#define   LCD1602_H




void lcd_init(void);
void lcd_write_order(u32 lcd_order);
void lcd_write_data(u32 lcd_data);

#endif


/*

≤‚ ‘œ‘ æ

u8  table1[]="LCD1602";
u8  table2[]="STM32";



	lcd1602_init();
	lcd_write_order(0x00);
	char i=0,j=0;
	while(table1[i]!='\0')
	{
	lcd_write_data(table1[i]);
	i++;
	delay_ms(10);	
	}
	
	lcd_write_order(0xc0);
	while(table2[j]!='\0')
	{
	lcd_write_data(table2[j]);
	j++;
	delay_ms(10);	
	}












*/
