#include "IncludeFile.h"




//设备状态列表，顺序与 SystemState_n 一致
static volatile u8 DeviceStateList[DEVICES_NUM];



// Device:  SystemState_n  中的成员
// State:   SystemState_n  中的成员对应的设备状态枚举列表
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


// Device:  SystemState_n  中的成员
// State:   SystemState_n  中的成员对应的设备状态枚举列表
void System_SetState(u8 Device,u8 State)
{

    DeviceStateList[Device] |= State;

}


// Device:  SystemState_n  中的成员
// State:   SystemState_n  中的成员对应的设备状态枚举列表
void System_ResetState(u8 Device,u8 State)
{

    DeviceStateList[Device] &= (~State);
    
}












