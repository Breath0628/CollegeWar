#pragma once
#include <graphics.h>
//
enum class IDWaitRoom
{//�ڵȴ�����ʱ����ݱ�ʶ ����Ϊ0
	Leader = 0, P1, P2, P3
};

//���ݰ��ĸ�ʽ
enum class IdentityMark
{//��ݱ�ʶ
	Undeined=-1,Player1P = 0, Player2P, Angel, Daemon
};
struct DataNode
{
	IdentityMark Identity;//��Ϣ�����ĸ�������ĸ��ͻ��� δȷ�����ʱĬ��Ϊ-1���ȴ�������������ݱ�ʶ
	ExMessage msg;
};