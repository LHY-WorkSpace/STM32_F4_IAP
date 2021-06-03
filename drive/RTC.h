#ifndef RTC_H
#define RTC_H


typedef struct 
{
    u8 year;
    u8 month;
    u8 date;
    u8 week;
    u8 hour;
    u8 minute;
    u8 second;

}STM32_Time_t;





void RTC_ConfigInit(void);
void RTC_Set_Date(u8 year,u8 month,u8 date,u8 week);
void RTC_Set_Time(u8 hour,u8 minute,u8 second);
void RTC_Get_Date(STM32_Time_t* STM32_Time);
void RTC_Get_Time(STM32_Time_t* STM32_Time);





#endif























