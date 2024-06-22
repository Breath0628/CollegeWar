#pragma once
#include <graphics.h>
//
enum class IDWaitRoom
{//在等待房间时的身份标识 房主为0
	Leader = 0, P1, P2, P3
};

//数据包的格式
enum class IdentityMark
{//身份标识
	Undeined=-1,Player1P = 0, Player2P, Angel, Daemon
};
struct DataNode
{
	IdentityMark Identity;//消息来自哪个房间的哪个客户机 未确定身份时默认为-1，等待服务器给予身份标识
	ExMessage msg;
};