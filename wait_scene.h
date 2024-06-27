#pragma once
#include <Mmsystem.h>
#include "scene.h"
#include <iostream>
#include "scene_manager.h"
#include "animation.h"
#include "camera.h"
#include "timer.h"
#include "Identity.h"
using namespace std;

extern SceneManager* scene_manager;
extern bool Running;
extern int identity_1p, identity_2p; //1P2P�����


class WaitScene :public Scene
{
public:
	WaitScene() = default;
	~WaitScene() = default;

	void on_enter() {
		loadimage(&bk, L"resources/wait/bk.png");
		loadimage(&border, L"resources/wait/border.png");
		loadimage(&fighter, L"resources/wait/fighter.png");
		loadimage(&angel, L"resources/wait/angel.jpg");
		loadimage(&daemon, L"resources/wait/daemon.jpg");
		//loadimage(&hand, _T("resources/menu/attack.png"));
		flip_image(&border, &LeftBorder);
		P1 = fighter, P2 = angel, P3 = fighter, P4 = daemon;
		borderPos1 = {20};
		borderPos2 = { 20+300,0 };
		borderPos3 = { 20+600,0 };
		borderPos4 = { 20+900,0 };

		settextstyle(25, 0, _T("IPix"));
		setbkmode(TRANSPARENT);
	

	}
	void on_update(int delta) {
	
		
	}
	void on_draw(const Camera& camera) {
		//������Ⱦ
		putimage(bkPos.x, bkPos.y,& bk);
		putimage(borderPos1.x + borderOffsetX, borderPos1.y + borderOffsetY, &P1);
		putimage(borderPos2.x + borderOffsetX, borderPos2.y + borderOffsetY, &P2);
		putimage(borderPos3.x + borderOffsetX, borderPos3.y + borderOffsetY, &P3);
		putimage(borderPos4.x + borderOffsetX, borderPos4.y + borderOffsetY, &P4);
		puimage_alpha(borderPos1.x, borderPos1.y, &LeftBorder);
		puimage_alpha(borderPos2.x, borderPos2.y, &LeftBorder);
		puimage_alpha(borderPos3.x, borderPos3.y, &border);
		puimage_alpha(borderPos4.x, borderPos4.y, &border);
		//puimage_alpha(handPos.x, handPos.y, &hand);
		settextstyle(28, 0, _T("IPix"),0,0,700,0,0,0);
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);

		switch (P1Identity)
		{
		case IdentityMark::Undeined:
			break;
		case IdentityMark::fighter:
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY, L"     ��ʿ");
			outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY + 50, L"�㾡ȫ��ɱ���Է�");
			outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY + 100, L"����Ǳ��Է�ɱ��");
			outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY + 150, L"����ɻ��н����");
			settextstyle(26, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			outtextxy(borderPos1.x + textOffsetX + 60, borderPos1.y + textOffsetY + 300, L"1P");

			break;
		case IdentityMark::Angel:
	
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY, L"   ��ʹ");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 100, L"����췦��");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 200, L"�����ò���");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos1.x + textOffsetX + 60, borderPos1.y + textOffsetY + 300, L"1P");
			break;
		case IdentityMark::Daemon:
		
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY, L"   ��ħ");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 100, L"ԡѪҲ����");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos1.x + textOffsetX + 40, borderPos1.y + textOffsetY + 200, L"����������");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos1.x + textOffsetX + 60, borderPos1.y + textOffsetY + 300, L"1P");
			break;
		default:
			break;
		}

		switch (P2Identity)
		{
		case IdentityMark::Undeined:
			break;
		case IdentityMark::fighter:
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
		
			outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY, L"     ��ʿ");
			outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY + 50, L"�㾡ȫ��ɱ���Է�");
			outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY + 100, L"����Ǳ��Է�ɱ��");
			outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY + 150, L"����ɻ��н����");
			settextstyle(26, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			outtextxy(borderPos2.x + textOffsetX + 60, borderPos2.y + textOffsetY + 300, L"1P");

			break;
		case IdentityMark::Angel:
			
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY, L"   ��ʹ");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 100, L"����췦��");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 200, L"�����ò���");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos2.x + textOffsetX + 60, borderPos2.y + textOffsetY + 300, L"1P");
			break;
		case IdentityMark::Daemon:
			
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY, L"   ��ħ");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 100, L"ԡѪҲ����");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos2.x + textOffsetX + 40, borderPos2.y + textOffsetY + 200, L"����������");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos2.x + textOffsetX + 60, borderPos2.y + textOffsetY + 300, L"1P");
			break;
		default:
			break;
		}

		switch (P3Identity)
		{
		case IdentityMark::Undeined:
			break;
		case IdentityMark::fighter:
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
		
			outtextxy(borderPos3.x + textOffsetX, borderPos3.y + textOffsetY, L"     ��ʿ");
			outtextxy(borderPos3.x + textOffsetX, borderPos3.y + textOffsetY + 50, L"�㾡ȫ��ɱ���Է�");
			outtextxy(borderPos3.x + textOffsetX, borderPos3.y + textOffsetY + 100, L"����Ǳ��Է�ɱ��");
			outtextxy(borderPos3.x + textOffsetX, borderPos3.y + textOffsetY + 150, L"����ɻ��н����");
			settextstyle(26, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			outtextxy(borderPos3.x + textOffsetX + 60, borderPos3.y + textOffsetY + 300, L"2P");

			break;
		case IdentityMark::Angel:
				
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY, L"   ��ʹ");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 100, L"����췦��");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 200, L"�����ò���");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos3.x + textOffsetX + 60, borderPos3.y + textOffsetY + 300, L"2P");
			break;
		case IdentityMark::Daemon:

			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			settextcolor(RED);
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY, L"   ��ħ");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 100, L"ԡѪҲ����");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos3.x + textOffsetX + 40, borderPos3.y + textOffsetY + 200, L"����������");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos3.x + textOffsetX + 60, borderPos3.y + textOffsetY + 300, L"2P");
			break;
		default:
			break;
		}

		switch (P4Identity)
		{
		case IdentityMark::Undeined:
			break;
		case IdentityMark::fighter:
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);

			outtextxy(borderPos4.x + textOffsetX, borderPos4.y + textOffsetY, L"     ��ʿ");
			outtextxy(borderPos4.x + textOffsetX, borderPos4.y + textOffsetY + 50, L"�㾡ȫ��ɱ���Է�");
			outtextxy(borderPos4.x + textOffsetX, borderPos4.y + textOffsetY + 100, L"����Ǳ��Է�ɱ��");
			outtextxy(borderPos4.x + textOffsetX, borderPos4.y + textOffsetY + 150, L"����ɻ��н����");
			settextstyle(26, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			outtextxy(borderPos4.x + textOffsetX + 60, borderPos4.y + textOffsetY + 300, L"2P");

			break;
		case IdentityMark::Angel:

			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			settextcolor(YELLOW);
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY, L"   ��ʹ");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 100, L"����췦��");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 200, L"�����ò���");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos4.x + textOffsetX + 60, borderPos4.y + textOffsetY + 300, L"2P");
			break;
		case IdentityMark::Daemon:
			settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			settextcolor(RED);
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY, L"   ��ħ");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 50, L"����������");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 100, L"ԡѪҲ����");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 150, L"����������");
			outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 200, L"����������");
			settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
			outtextxy(borderPos4.x + textOffsetX + 60, borderPos4.y + textOffsetY + 300, L"2P");
			break;
		default:
			break;
		}
	}
	void on_input(const ExMessage& msg) {



		if (msg.message != WM_KEYUP) return;

	
		switch (msg.vkcode)
		{
		case VK_LEFT:
			if ((int)(P4Identity) == 2)
			{
				P4Identity = (IdentityMark)1;
			}else P4Identity = (IdentityMark)2; //��������л�Ϊ��һ�� 
			break;
		case VK_RIGHT:
			if ((int)(P4Identity) == 1)
			{
				P4Identity = (IdentityMark)2;
			}else P4Identity = (IdentityMark)1; //��������л�Ϊ��һ�� 
			break;
		case 65://a
			if ((int)(P2Identity) == 1)
			{
				P2Identity = (IdentityMark)2;
			}else P2Identity = (IdentityMark)1; //��������л�Ϊ��һ�� 
			
			break;

		case 68://d
			if ((int)(P2Identity) == 1)
			{
				P2Identity = (IdentityMark)2;
			}
			else
			{
				P2Identity = (IdentityMark)1; //��������л�Ϊ��һ�� 
			}
			break;
		case 32:
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager->switch_to(SceneManager::SceneType::Selector);
			break;
		}
			switch (P4Identity)
			{
			case IdentityMark::Undeined:
				break;
			case IdentityMark::fighter:
				P4 = fighter;
				break;
			case IdentityMark::Angel:
				P4 = angel;
				break;
			case IdentityMark::Daemon:
				P4= daemon;
				break;
			}
			switch (P2Identity)
			{
			case IdentityMark::Undeined:
				break;
			case IdentityMark::fighter:
				P2 = fighter;
				break;
			case IdentityMark::Angel:
				P2 = angel;
				break;
			case IdentityMark::Daemon:
				P2 = daemon;
				break;
			}
	


	};
	               
	void exit() {
	
		//������ݱ�ʶ ����ѡ�ǳ������л�
		switch (P4Identity)
		{
		case IdentityMark::Angel:
			identity_2p = 1;
			break;
		case IdentityMark::Daemon:
			identity_2p = 2;
			break;
		}
		switch (P2Identity)
		{
		case IdentityMark::Angel:
			identity_1p = 1;
			break;
		case IdentityMark::Daemon:
			identity_1p = 2;
			break;
		}

	}

private:
	IMAGE LeftBorder;
	IMAGE bk, hand,border;//��ǰ����ͼ ָ��ͼ,�߿�
	IMAGE angel, daemon, fighter;//���ͼ
	IMAGE P1, P2,P3, P4;//ÿ��λ��Ӧ�÷ŵ�ͼ 
	IdentityMark P1Identity = IdentityMark(0), P2Identity = IdentityMark(1), P3Identity = IdentityMark(0), P4Identity = IdentityMark(2);//ÿ���û������
	IdentityMark* msgP;//����ָ��Ϣ�¼����û������
	POINT bkPos = { 0,0 }, titlePos;
	Atlas bkAtlas, itleAtlas;
	IdentityMark nowIdentity;//��ǰ�û������
	POINT borderPos1 = { 0 }, borderPos2 = { 0 }, borderPos3 = { 0 }, borderPos4 = { 0 };
	int borderOffsetX = 65, borderOffsetY=75;
	int textOffsetX=40, textOffsetY=300;//�ı�ƫ����
	int msgCount=0;
	MsgNode* msgNode;
	char data[1024];
	getIdentity* IdentityNode;
	//WaitNode* waitNode;
};