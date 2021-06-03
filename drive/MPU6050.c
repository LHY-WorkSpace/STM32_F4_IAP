#include"IncludeFile.h"

struct rx_s {
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};
static struct hal_s hal = {0};



u8 get_ms(unsigned long *count)
{
	delay_ms(5);
	return 0;
}



static signed char gyro_orientation[9] = {-1, 0, 0,
									0,-1, 0,
									0, 0, 1};	

static unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}


static unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    scalar = inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}





//读写速率210Khz
u8 MPU6050_Read_Data(u8 Reg)
{
	u8 DATA=0;
	
	Start_IIC();
	IIC_SenddByte(MPU6050_ADDRESS|0X00);
    IIC_Wait_Ack_OK();
	IIC_SenddByte(Reg);
	IIC_Wait_Ack_OK();
	
	Start_IIC();
	IIC_SenddByte((Reg|0X01));	
    IIC_Wait_Ack_OK();
	DATA=IIC_GetByte();
	IIC_Send_NAck();
	Stop_IIC();
	
	return DATA;



}


void MPU6050_Write_Data(u8 Reg,u8 data)
{

	Start_IIC();
	IIC_SenddByte(MPU6050_ADDRESS);        
    IIC_Wait_Ack_OK();
	IIC_SenddByte(Reg);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(data);	
	IIC_Wait_Ack_OK();
	Stop_IIC();
	delay_us(1); 
}



u8 MPU6050_Write_DMP(u8 devices_addr,u8 Reg,u8 length,u8 *data)
{
  	u8 i=0;
	Start_IIC();
	IIC_SenddByte(devices_addr|0x00);
	IIC_Wait_Ack_OK();
	IIC_SenddByte(Reg);
	IIC_Wait_Ack_OK();
	for(i=0;i<length;i++)
	{
		IIC_SenddByte(*data);
		if(IIC_Wait_Ack_OK()==1)
		{
			Stop_IIC();
			return 1;
		}
		data++;
	}
 	Stop_IIC();
	delay_us(1);
	return 0;

}



u8 MPU6050_Read_DMP(u8 devices_addr,u8 Reg,u8 length,u8 *data)
{
		u8 i=0;
    	Start_IIC();
		IIC_SenddByte(devices_addr);
		IIC_Wait_Ack_OK();
		IIC_SenddByte(Reg);
		IIC_Wait_Ack_OK();
   		Start_IIC();
		IIC_SenddByte(devices_addr|0X01);	
		IIC_Wait_Ack_OK();
	
		for(i=0;i<length;i++)
		{
			if(i<(length-1))
			{
				*data=IIC_GetByte();
				IIC_Send_Ack();
			}
			else
			{
				*data=IIC_GetByte();
				IIC_Send_NAck();	
			}
			data++;	
		}
		Stop_IIC();

	return 0;
}


static void run_self_test()
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x3) 
	{

        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
    }


}

void MPU6050_Init(void)
{
	IIC_Init();
	MPU6050_Write_Data(MPU6050_PWR1_CONFIG_REG,MPU6050_CLK_SOURCE);                                                              //
	MPU6050_Write_Data(MPU6050_CONFIGURATION_REG,MPU6050_DLPF_CFG);
	MPU6050_Write_Data(MPU6050_SMPTR_DIV_REG,MPU6050_SMPTR_DIV);
	MPU6050_Write_Data(MPU6050_GYR_CONFIG_REG,MPU6050_FS_SEL);
	MPU6050_Write_Data(MPU6050_ACC_CONFIG_REG,MPU6050_AFS_SEL);
	MPU6050_Write_Data(MPU6050_FIFO_ENABLE_REG,MPU6050_TEMP_FIFO_ENABLE|MPU6050_GYRFIFO_ENABLE|MPU6050_ACCFIFO_ENABLE);
	MPU6050_DMP_Init();
	
}

u8 MPU6050_DMP_Init(void)
{  
	
    if(mpu_init())
		return 1;	
    if(mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
		return 2;
    if(mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
		return 3;		
    if(mpu_set_sample_rate(DEFAULT_MPU_HZ))
		return 4;
    if(dmp_load_motion_driver_firmware())
		return 5;
    if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
		return 6;
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
		DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
		DMP_FEATURE_GYRO_CAL;
    if(dmp_enable_feature(hal.dmp_features))
		return 7;
    if(dmp_set_fifo_rate(DEFAULT_MPU_HZ))
		return 8;	
    if(mpu_set_dmp_state(1))
		return 9;	
    hal.dmp_on = 1;			
		run_self_test();	

	return 0;

}


double MPU6050_Tempure(void)
{
	short int temp;
	double reval;
	temp=(MPU6050_Read_Data(MPU6050_TEMP_OUT_H)<<8|MPU6050_Read_Data(MPU6050_TEMP_OUT_L));
	reval=((double)temp/340+36.53f);
  return reval;

}


/*读取数据到 pitch,yaw,roll  */
u8 MPU6050_Get_DMP_Data(float *pitch,float *yaw,float *roll)
{
	u8 i=0;
	long quat[4];
	short gyro[3], accel[3], sensors;
	unsigned long sensor_timestamp;
	unsigned char more;
	float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;

	while(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more)&&i<30)
	{
		i++;
		delay_us(2);
	}
	
				if(sensors&INV_WXYZ_QUAT)
				{
				q0=quat[0]/q30;
				q1=quat[1]/q30;				
				q2=quat[2]/q30;
				q3=quat[3]/q30;	
					
				*pitch=asin(-2*q1*q3+2*q0*q2)*57.3;
				*roll=atan2(2*q2*q3+2*q0*q1,-2*q1*q1-2*q2*q2+1)*57.3;
				*yaw=atan2(2*(q1*q2+q3*q0),q0*q0+q1*q1-q2*q2-q3*q3)*57.3;

				}

	      return 0;
}



void usart1_niming_report(u8 fun,u8 *data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+3]=0;	//校验数置零
	send_buf[0]=0X88;	//帧头
	send_buf[1]=fun;	//功能字
	send_buf[2]=len;	//数据长度
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//复制数据
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);    //发送数据到串口1
	
	 
}

//匿名上位机//
void mpu6050_SendTo_APP(short pitch,short yaw,short roll)
{
	
	MPU6050_Get_DMP_Data((float*)&pitch,(float*)&yaw,(float*)&roll);
	u8 tbuf[28]; 
	u8 i;
	for(i=0;i<28;i++)tbuf[i]=0;//清0
	
	
	
	//显示曲线
//	tbuf[0]=(roll>>8)&0XFF;
//	tbuf[1]=roll&0XFF;
//	tbuf[2]=(pitch>>8)&0XFF;
//	tbuf[3]=pitch&0XFF;
//	tbuf[4]=(yaw>>8)&0XFF;
//	tbuf[5]=yaw&0XFF;
//	usart1_niming_report(0XA1,tbuf,10);//飞控显示帧,0XAF	
	

	
	//显示姿态
	
//	tbuf[3]=ACC_X_L;
//	tbuf[4]=ACC_X_H;
//	tbuf[5]=ACC_Y_L;
//	tbuf[6]=ACC_Y_H;
//	tbuf[7]=ACC_Z_L;
//	tbuf[8]=ACC_Z_H;
//	
	
	
	tbuf[18]=(roll>>8)&0XFF;
	tbuf[19]=roll&0XFF;
	tbuf[20]=(pitch>>8)&0XFF;
	tbuf[21]=pitch&0XFF;
	tbuf[22]=(yaw>>8)&0XFF;
	tbuf[23]=yaw&0XFF;
	usart1_niming_report(0XAf,tbuf,28);//飞控显示帧,0XAF		
	


} 

void usart1_send_char(u8 c)
{

	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
   USART_SendData(USART1,c);   

} 









