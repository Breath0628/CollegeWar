#pragma once
#include <graphics.h>
//
enum class IDWaitRoom
{//在等待房间时的id标识 房主为1
	 P1=1, P2, P3,P4
};

//数据包的标准格式
enum class IdentityMark
{//身份标识
	Undeined=-1, fighter = 0, Angel, Daemon
};
struct MsgNode
{
	char type = 2;
	IDWaitRoom UserId;//消息来自房间的哪个客户机
	ExMessage msg;
};

//数据包的标准格式

//等待房间分配身份数据包
struct getIdentity {
	char type = 0;
	IDWaitRoom UserId;
};

//等待房间数据包;
struct WaitNode
{
	char type=1;//数据包类型的标识
	IDWaitRoom UserId;//消息来自房间的哪个客户机
	IdentityMark Identity;//身份

};