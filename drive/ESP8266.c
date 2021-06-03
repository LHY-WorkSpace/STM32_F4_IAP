#include"IncludeFile.h"



#define IP_START  	       "@!"
#define IP_END     	       "!@"
#define PASSWORD_START     "#!"
#define PASSWORD_END       "!#"


const char* IP_begin=IP_START;
const char* IP_end=IP_END;
const char* password_begin=PASSWORD_START;
const char* password_end=PASSWORD_END;


char *user_message="\
Input WIFI name and password\n\
such as :@!xxxx!@|#!yyyy!#\n\
xxxx:name\n\
yyyy:password";



//设置本地WIFI///
char CMD_RST[]="AT+RST\r\n";
char CMD_CWMODE[]="AT+CWMODE=3\r\n";
char CMD_CWSAP[]="AT+CWSAP=\"DEVICE1\",\"123456789\",6,3\r\n";
char CMD_CIFSR[]="AT+CIFSR\r\n";
char CMD_CIPMUX[]="AT+CIPMUX=1\r\n";
char CMD_CIPSERVER[]="AT+CIPSERVER=1,8080\r\n";
char CMD_CIPSEND[]="AT+CIPSEND=0,79\r\n";

char Wifi_Name[]="WIFI:DEVICE1";
char Wifi_Password[]="KEY:123456789";
char Port[]="PORT:8080";
char Local_IP[12];
char Net_Name[15];
char Net_Password[10];
char Wifi_Data[300];
u8 USED_FLAG;



void ESP8266_Init(void)
{	
	
	
	
	
	


}

void Set_Mode()
{	
	
	
	
	printf("%s",CMD_RST);
	delay_ms(500);
	printf("%s",CMD_CWMODE);
	delay_ms(100);
	printf("%s",CMD_CWSAP);
	delay_ms(100);
	printf("%s",CMD_CIFSR);
	USED_FLAG=1;	                     //清除缓存，从头开始接收
	delay_ms(100);
	Get_IP(Wifi_Data,Local_IP);        //提取IP
	display_position(0,0,12);
	//display_str_and_speed(Wifi_Name,10);
	display_position(0,2,13);
	//display_str_and_speed(Wifi_Password,10);
	display_position(0,4,9);
	//display_str_and_speed(Port,10);
	display_position(0,6,3);
	//display_str_and_speed("IP:",10);
	display_position(24,6,11);
	//display_str_and_speed(Local_IP,10);
	printf("%s",CMD_CIPMUX);
	delay_ms(100);
	printf("%s",CMD_CIPSERVER);
	delay_ms(100);
	USED_FLAG=1;
	while(1)
	{
		if(Wifi_Data[3]=='O')
		{
		USED_FLAG=1;
		display_position(0,7,3);	
		//display_str_and_speed(":OK",10);
    break;
		}
		else
		{
		display_position(0,7,3);	
		//display_str_and_speed(":XX",10);
	  USED_FLAG=1;
		}
		
		delay_ms(100);
//	  times++;
//		if(times>250)
//		{
//		clear_screen();
//		display_position(0,0,8);	
//		//display_str_and_speed("TIME OUT",1);
//		display_position(0,2,9);	
//		//display_str_and_speed("TRY RESET",1);
//		USED_FLAG=1;
//		break;
//		}
		
		
	}
printf("%s",CMD_CIPSEND);
delay_ms(100);
printf("%s",user_message);
delay_ms(500);
memset(Wifi_Data,0,sizeof(Wifi_Data));	
	while(1)
	{
		if(Wifi_Data[0]=='+')
		{
//		clear_screen();
//		show_All();
//		//display_str_and_speed(Wifi_Data,100);			
			
			
//    Get_NetName(Wifi_Data,Net_Name);	
//    Get_NetPassword(Wifi_Data,Net_Password);
//		display_position(0,1,3);	
//		//display_str_and_speed(Net_Name,100);	
//		display_position(0,3,3);	
//		//display_str_and_speed(Net_Password,10);	
//		delay_ms(500);
		USED_FLAG=1;			
    break;
		}
		else
		{

	  USED_FLAG=1;
		}
		
		
		
	}	
	
		while(1)
		{
			clear_screen();
			show_All();
			//display_str_and_speed(Wifi_Data,100);
			
	
////		display_position(0,1,16);	
//		//display_str_and_speed(Net_Name,100);	
////		display_position(0,3,strlen(Net_Password));	
//		//display_str_and_speed(Net_Password,10);
//				//display_str_and_speed("OK",10);	
			break;

		}




}


//void Get_IP(char *str,char *temp)
//{
//	u8 i=0;
//	str+=24;
//	for(i=0;i<12;i++)
//	{
//	*(temp+i)=*(str+i);	
//	}
//	*(temp+11)='\0';
//	
//}	




void Get_NetName(char *str,char *temp)
{
	while(*str!='\0')
	{
		if((*str==*IP_begin)&&*(str+1)==*(IP_begin+1))	
		{
		str+=2;
			while((*str!=*IP_end)&&*(str+1)!=*(IP_end+1))
			{
				*temp=*str;
				temp++;
				str++;
			}
		}
		str++;
	}
}	


void Get_NetPassword(char *str,char *temp)
{

	while(*str!='\0')
	{
		if((*str==*password_begin)&&*(str+1)==*(password_begin+1))	
		{
			str+=2;
			while((*str!=*password_end)&&*(str+1)!=*(password_end+1))
			{
				*temp=*str;
				temp++;
				str++;
			}
		}
		str++;
	}

}































