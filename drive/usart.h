#ifndef     __USART_H__
#define     __USART_H__



#define  USART_DATA_8bit     USART_WordLength_8b
#define  USART_DATA_9bit     USART_WordLength_9b


#define  USART_STOP_1bit      USART_StopBits_1
#define  USART_STOP_0_5bit    USART_StopBits_0_5
#define  USART_STOP_2bit      USART_StopBits_2
#define  USART_STOP_1_5bit    USART_StopBits_1_5


#define  USART_PARTYT_NO     USART_Parity_No
#define  USART_PARTYT_ODD    USART_Parity_Odd
#define  USART_PARTYT_EVEN   USART_Parity_Even


#define USART1_MODE_A
#define USART2_MODE_A   



#define BUFFER_SIZE      (1024)


// typedef struct 
// {
//     /* data */
// };



void USART1_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity);   
void USART2_Init(u32 bode,u16 DataLength,u16 StopBit,u16 Parity);

int fputc(int ch, FILE* stream);
#endif







