#pragma once
#include <graphics.h>
//
enum class IDWaitRoom
{//�ڵȴ�����ʱ��id��ʶ ����Ϊ1
	 P1=1, P2, P3,P4
};

//���ݰ��ı�׼��ʽ
enum class IdentityMark
{//��ݱ�ʶ
	Undeined=-1, fighter = 0, Angel, Daemon
};
struct MsgNode
{
	char type = 2;
	IDWaitRoom UserId;//��Ϣ���Է�����ĸ��ͻ���
	ExMessage msg;
};

//���ݰ��ı�׼��ʽ

//�ȴ��������������ݰ�
struct getIdentity {
	char type = 0;
	IDWaitRoom UserId;
};

//�ȴ��������ݰ�;
struct WaitNode
{
	char type=1;//���ݰ����͵ı�ʶ
	IDWaitRoom UserId;//��Ϣ���Է�����ĸ��ͻ���
	IdentityMark Identity;//���

};