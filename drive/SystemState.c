#include "IncludeFile.h"




//�豸״̬�б�˳���� SystemState_n һ��
static volatile u8 DeviceStateList[DEVICES_NUM];



// Device:  SystemState_n  �еĳ�Ա
// State:   SystemState_n  �еĳ�Ա��Ӧ���豸״̬ö���б�
u8 System_GetState(u8 Device,u8 State)
{
	if( State == 0xff )
	{
		return DeviceStateList[Device];
	}

	if( (DeviceStateList[Device]&State) != State )
	{
		return  RESET;
	}
	else
	{
		return  SET;
	}

}


// Device:  SystemState_n  �еĳ�Ա
// State:   SystemState_n  �еĳ�Ա��Ӧ���豸״̬ö���б�
void System_SetState(u8 Device,u8 State)
{

    DeviceStateList[Device] |= State;

}


// Device:  SystemState_n  �еĳ�Ա
// State:   SystemState_n  �еĳ�Ա��Ӧ���豸״̬ö���б�
void System_ResetState(u8 Device,u8 State)
{

    DeviceStateList[Device] &= (~State);
    
}












