#ifndef   _MPU6050_H_
#define   _MPU6050_H_
#include "stm32f4xx.h"



//               https://wenku.baidu.com/view/8dbd8f9e360cba1aa911da1d.html?rec_flag=default&sxts=1571581621334
//    G:\BaiduNetdiskDownload\̽����F4 ������(A��)\9����ֵ����\1��ALIENTEK ��Ʒ����\11��ATK-MPU6050���ᴫ����ģ��\4��MPU6050�ο�����


/*
				8 BIT    MSB  -----------------------  LSB
											1  1  0  1  0  0  0 | X
														 0X68         | AD0
											-----------------------
*/
#define MPU6050_ADDRESS                 0xD0             //MPU6050��7bit������ַ    0bit X ���ⲿ����ѡ��       1101 000X
//#define OWN_IIC_ADDRESS               0x11
#define MPU6050_WRITE                   0X00
#define MPU6050_READ                    0X01



/*
    (����Ƶ��)         GYR_OUTPUT_FREQUENCY(���������Ƶ��)
GYR_SAMPLE_FREQUENCY = ---------------------------------    =200HZ
											  (1 + SMPTR_DIV(8 bit unsigned))

GYR_OUTPUT_FREQUENCY:        depend on DLPF[2:0]
                              DLPF = 0 or 7    GYR_OUTPUT_FREQUENCY=8khz
															DLPF = others	   GYR_OUTPUT_FREQUENCY=1khz         USE THIS**


GYR_OUTPUT_FREQUENCY > 2*DLPF_SAMPLE_RATE


*/
#define   MPU6050_SMPTR_DIV_REG                 0X19
#define   MPU6050_SMPTR_DIV                     0X04                 //����Ƶ��  200hz

/*

CONFIGURATION      7  6 |5  4  3 | 2  1  0
                   -  - |  EXT   | DLPF  |

*/
#define   MPU6050_CONFIGURATION_REG             0X1A                //FSYNC DLPF���üĴ���
#define   MPU6050_DLPF_CFG                      0X02                //��ͨ�˲������ò���     DLPF_SAMPLE_RATE~100HZ



/*
GYR_CONFIG��            bit[7:5]     GYR self test  
               FS_SEL = bit[4:3]     full scale �����̷�Χ
							 
*/
#define   MPU6050_GYR_CONFIG_REG                0X1B                //���������üĴ���
#define   MPU6050_FS_SEL                        0X11                //-2000./S~2000./S      65536/4000=16.4LSB/(./s)        
/*
GYR_CONFIG��            bit[7:5]     ACC self test  
              AFS_SEL = bit[4:3]     full scale �����̷�Χ
							 
*/
#define   MPU6050_ACC_CONFIG_REG                0X1C                //���ٶȼ����üĴ���
#define   MPU6050_AFS_SEL                       0X00                //-2g~2g                 65536/4=16384LSB/g


/*
PWR1_CONFIG:    DEVICES_REST     = bit[7]       RESET bit  (��λ���Զ�����)
                AFS_SEL          = bit[6]       SLEEP   
							  CYCLE            = bit[5]       DON'T UNDERSTAND....
								TEMP_DIS         = bit[3]       =1 DISABLE  ,   =0 ENABLE  �¶ȴ�����
								CLK_SOURCE       = bit[2:0]  
*/

#define   MPU6050_PWR1_CONFIG_REG               0X6B         //��Դ����Ĵ���1
#define   MPU6050_CLK_SOURCE                    0X01         //PLL X��Ϊʱ��Դ�ҿ����¶ȴ�����

#define  MPU6050_INT_REG                        0X38         //�ж�ʹ�ܼĴ���
#define  MPU6050_INT_DISABLE                    0X00 



#define  MPU6050_FIFO_ENABLE_REG                0X23         //FIFO  ʹ�ܼĴ���
#define  MPU6050_TEMP_FIFO_ENABLE               0X80         //TEMP	 FIFO ʹ��
#define  MPU6050_GYRFIFO_ENABLE                 0X70         //������  FIFO ʹ��
#define  MPU6050_ACCFIFO_ENABLE                 0X08         //���ٶȼ� FIFOʹ��



#define   MPU6050_GYR_XOUT_L                    0X44
#define   MPU6050_GYR_XOUT_H                    0X43
#define   MPU6050_GYR_YOUT_L              		  0X46
#define   MPU6050_GYR_YOUT_H                    0X45
#define   MPU6050_GYR_ZOUT_L                    0X48
#define   MPU6050_GYR_ZOUT_H                    0X47


#define   MPU6050_ACC_XOUT_L                    0X3C
#define   MPU6050_ACC_XOUT_H                    0X3B
#define   MPU6050_ACC_YOUT_L                    0X3E
#define   MPU6050_ACC_YOUT_H                    0X3D 
#define   MPU6050_ACC_ZOUT_L                    0X40
#define   MPU6050_ACC_ZOUT_H                    0X3F
  
#define   MPU6050_TEMP_OUT_L                    0X42
#define   MPU6050_TEMP_OUT_H                    0X41

#define   MPU6050_WHO_AM_I                      0X75

#define   MPU6050_DMP_ENABLE                       1
#define   q30                                  (1073741824.0f)           


/*                DMP                 */

#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)

#define MOTION          (0)
#define NO_MOTION       (1)

#define DEFAULT_MPU_HZ  (100)






void MPU6050_Init(void);
void MPU6050_Write_Data(u8 COMMOND,u8 data);
u8 MPU6050_Read_Data(u8 COMMOND);
void MPU6050_Get_Gyro_Data(void);
void MPU6050_Get_Acce_Data(void);
double MPU6050_Tempure(void);





//DMP API//
u8 MPU6050_DMP_Init(void);
u8 MPU6050_Write_DMP(u8 devices_addr,u8 COMMOND,u8 length,u8  *data);
u8  MPU6050_Read_DMP(u8 devices_addr,u8 COMMOND,u8 length,u8  *data);
u8  get_ms(unsigned long *count);
u16 inv_row_2_scale(const signed char *row);
static u16 inv_orientation_matrix_to_scalar(const signed char *mtx);
void run_self_test(void);	
u8 MPU6050_Get_DMP_Data(float *pitch,float *yaw,float *roll);


//��λ������//
void  mpu6050_SendTo_APP(short roll,short pitch,short yaw);	
void usart1_niming_report(u8 fun,u8 *data,u8 len);
void usart1_send_char(u8 c);

//   mpu6050_SendTo_APP((int)(roll*100),(int)(pitch*100),(int)(yaw*10));	



















#endif

