#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "archi_player.h"
#include "computer_player.h"
#include "math_player.h"
#include "eam_player.h"
extern SceneManager* scene_manager; //����������
extern Player* player_1P;//1p����
extern Player* player_2P;//2p����
//������Դ
extern IMAGE img_VS;//vs������ͼƬ
extern IMAGE img_1P;//1p�ı�ͼ
extern IMAGE img_2P;//2p�ı�ͼ
extern IMAGE img_3P;//3p�ı�ͼ
extern IMAGE img_4P;

extern IMAGE img_1P_desc;//1p��λ����ͼ
extern IMAGE img_2P_desc;//2p��λ����ͼ
extern IMAGE img_gravestone_left;//������Ŀ��ͼ
extern IMAGE img_gravestone_right;//����
extern IMAGE img_gravestone_3;    //34���ͷ���
extern IMAGE img_gravestone_4;

extern IMAGE img_selector_background;//ѡ�ǽ��汳��ͼ
extern IMAGE img_selector_tip;//ѡ�ǽ�����ʾ��Ϣ�ı�ͼ

extern IMAGE img_1P_selector_btn_idle_left;            // 1P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_idle_right;           // 1P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_left;            // 1P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_1P_selector_btn_down_right;           // 1P ����ѡ��ť����״̬ͼƬ

extern IMAGE img_2P_selector_btn_idle_left;            // 2P ����ѡ��ťĬ��״̬ͼƬ                                                                                
extern IMAGE img_2P_selector_btn_idle_right;           // 2P ����ѡ��ťĬ��״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_left;            // 2P ����ѡ��ť����״̬ͼƬ
extern IMAGE img_2P_selector_btn_down_right;           // 2P ����ѡ��ť����״̬ͼƬ

extern IMAGE img_peashooter_selector_background_left;  // ѡ�ǽ��泯����ı���ͼƬ
extern IMAGE img_peashooter_selector_background_right; // ѡ�ǽ��泯���ҵı���ͼƬ
extern IMAGE img_sunflower_selector_background_left;   // ѡ�ǽ��泯����ı���ͼƬ
extern IMAGE img_sunflower_selector_background_right;  // ѡ�ǽ��泯���ҵ�������ͼƬ

//����ѧԺ
extern Atlas atlas_archi_idle_left;               // ��ѧԺ�������Ĭ�϶���ͼ��   
extern Atlas atlas_archi_idle_right;

//�������ɫ
extern Atlas atlas_computer_idle_left;               // �����Ĭ�϶���ͼ��
extern Atlas atlas_computer_idle_right;              // ���ҵ�Ĭ�϶���ͼ��

extern Atlas atlas_player3_idle;                       //34������ﻹû����
extern Atlas atlas_player4_idle;
//��ѧԺ
extern Atlas atlas_math_idle_left;               // ��ѧԺ�������Ĭ�϶���ͼ��   
extern Atlas atlas_math_idle_right;

//����
extern Atlas EAM_idle_left;
extern Atlas EAM_idle_right;


//ѡ�ǳ��������Դ
extern Atlas atlas_angel;
extern Atlas atlas_demon;

extern int identity_1p, identity_2p; //1P2P�����

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;
private:
	enum class PlayerType {
		Computer,
		Math,
		Eam,
		Archi
	};


private:
	void on_enter() {
		//���ó�ʼ����
		_stprintf_s(str_P1_name, L"��ϢѧԺ-����");
		_stprintf_s(str_P2_name, L"��ϢѧԺ-����");


		//Ϊ��ɫ��������ͼ����֡���
		animation_P1.set_atlas(&atlas_computer_idle_right);
		animation_P2.set_atlas(&atlas_computer_idle_left);
		animation_player3.set_atlas(&atlas_player3_idle);    //
		animation_player4.set_atlas(&atlas_player4_idle);

		animation_P1.set_interval(100);
		animation_P2.set_interval(100);
		animation_player3.set_interval(100);                //
		animation_player4.set_interval(100);

		//���þ�̬Ԫ��λ�� ��ը
		static const int OFFSET_X = 50;
		pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2 - 15;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X + 125;
		pos_img_1P.y = 15;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X - 125;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_3P.x = pos_img_1P.x;
		pos_img_3P.y = 300;
		pos_img_4P.x = pos_img_2P.x-20;
		pos_img_4P.y = pos_img_3P.y-10;

		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 120;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;

		pos_img_1P_gravestone.x = pos_img_1P.x - 30;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() - 25;
		pos_img_2P_gravestone.x = pos_img_2P.x - 30;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_img_3P_gravestone.x = pos_img_1P_gravestone.x;
		pos_img_3P_gravestone.y = pos_img_3P.y + img_3P.getheight() - 25;
		pos_img_4P_gravestone.x = pos_img_2P_gravestone.x;
		pos_img_4P_gravestone.y = pos_img_3P_gravestone.y;

		pos_animation_1P.x = pos_img_1P_gravestone.x + (pos_img_1P_gravestone.x - 96) / 2 - OFFSET_X - 22;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 50;
		pos_animation_2P.x = pos_img_2P_gravestone.x + 50;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_animation_3P.x = pos_animation_1P.x-3;
		pos_animation_3P.y = pos_img_3P_gravestone.y + 50-3;
		pos_animation_4P.x = pos_animation_2P.x-10;
		pos_animation_4P.y = pos_animation_3P.y-2 ;

		pos_img_1P_name.y = pos_animation_1P.y + 135;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

		//���
		switch (identity_1p)
		{
		case 1:
			animation_player3.set_atlas(&atlas_angel);
			break;
		case 2:
			animation_player3.set_atlas(&atlas_demon);
			break;
		}
		//���
		switch (identity_2p)
		{
		case 1:
			animation_player4.set_atlas(&atlas_angel);
			break;
		case 2:
			animation_player4.set_atlas(&atlas_demon);
			break;
		}
	

	}
	void on_update(int delta) {
		//��ɫ��������
		animation_P1.on_update(delta);
		animation_P2.on_update(delta);
		animation_player3.on_update(delta);
		animation_player4.on_update(delta);

		scorll_line_x += 5; //��׼�߸���
		if (scorll_line_x >= img_peashooter_selector_background_left.getwidth()) scorll_line_x = 0;

	}
	void on_draw(const Camera& camera) {

		putimage(0, 0, &img_selector_background);      ////
		//��Ⱦ������̬ͼ

		IMAGE* p1_scorll_bk = nullptr;
		IMAGE* p2_scorll_bk = nullptr;

		
		p1_scorll_bk = &img_peashooter_selector_background_right;
		p2_scorll_bk = &img_sunflower_selector_background_left;
		
		puimage_alpha(scorll_line_x - p1_scorll_bk->getwidth(), 0, p1_scorll_bk);
		puimage_alpha(scorll_line_x, 0,
			p1_scorll_bk->getwidth() - scorll_line_x, 0,
			p1_scorll_bk, 0, 0);

		puimage_alpha(getwidth() - p2_scorll_bk->getwidth(), 0, p2_scorll_bk->getwidth() - scorll_line_x, 0,
			p2_scorll_bk, scorll_line_x, 0);

		puimage_alpha(getwidth() - scorll_line_x, 0, p2_scorll_bk);

		//��Ⱦ��̬�ز�

		puimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

		puimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		puimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
		puimage_alpha(pos_img_3P.x, pos_img_3P.y, &img_3P);
		puimage_alpha(pos_img_4P.x, pos_img_4P.y, &img_4P);

		puimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		puimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

		//pos_animation_3P
		animation_player3.on_draw(pos_animation_3P.x, pos_animation_3P.y);
		animation_player4.on_draw(pos_animation_4P.x, pos_animation_4P.y);
		puimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		puimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);
		puimage_alpha(pos_img_3P_gravestone.x, pos_img_3P_gravestone.y, &img_gravestone_3);
		puimage_alpha(pos_img_4P_gravestone.x, pos_img_4P_gravestone.y, &img_gravestone_4);

		puimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);



		//��Ⱦ1p 2p��ɫ����
		animation_P1.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		animation_P2.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		
	   //��Ⱦ��ɫ1p 2p����
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_P1_name)) / 2;
		outtexy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_P1_name);
		
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_P2_name)) / 2;
		outtexy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_P2_name);
		

		
	}
	void on_input(const ExMessage& msg) {            //�����������½�ɫ����޸�
		//��ɫѡȡ ������ת
		if (msg.message != WM_KEYUP) return;

		switch (msg.vkcode)
		{
		case 39://->
			//ѡ����ɫ����
			if ((int)player_type_2== Num)player_type_2 = (PlayerType)0;//�˴���2�����Ѿ���3����ɫ
			else
			{
				player_type_2 = PlayerType(((int)player_type_2 + 1));
			}
			
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//Ϊѡ���Ľ�ɫ�趨����������
			switch (player_type_2)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P2_name, L"��ϢѧԺ-����");
				animation_P2.set_atlas(&atlas_computer_run_left);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P2_name, L"��ѧԺ-�B��");
				animation_P2.set_atlas(&atlas_math_idle_left);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P2_name, L"����ѧԺ-˼����");
				animation_P2.set_atlas(&EAM_idle_left);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P2_name, L"����ѧԺ-����");
				animation_P2.set_atlas(&atlas_archi_idle_left);
				break;
			}

			break;

		case 37://<-
			//ѡ����ɫ����
			if ((int)player_type_2 ==0 )player_type_2 = (PlayerType)Num;//�˴���2�����Ѿ���3����ɫ
			else
			{
				player_type_2 = PlayerType(((int)player_type_2 -1));
			}
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//Ϊѡ���Ľ�ɫ�趨����
			//Ϊѡ���Ľ�ɫ�趨����������
			switch (player_type_2)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P2_name, L"��ϢѧԺ-����");
				animation_P2.set_atlas(&atlas_computer_run_left);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P2_name, L"��ѧԺ-�B��");
				animation_P2.set_atlas(&atlas_math_idle_left);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P2_name, L"����ѧԺ-˼����");
				animation_P2.set_atlas(&EAM_idle_left);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P2_name, L"����ѧԺ-����");
				animation_P2.set_atlas(&atlas_archi_idle_left);
				break;

			}

			break;
		case 68://D
			//ѡ����ɫ����
			if ((int)player_type_1 == Num)player_type_1= (PlayerType)0;//�˴���2�����Ѿ���3����ɫ
			else
			{
				player_type_1 = PlayerType(((int)player_type_1 + 1));
			}

			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//Ϊѡ���Ľ�ɫ�趨����������
			switch (player_type_1)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P1_name, L"��ϢѧԺ-����");
				animation_P1.set_atlas(&atlas_computer_run_right);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P1_name, L"��ѧԺ-�B��");
				animation_P1.set_atlas(&atlas_math_idle_right);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P1_name, L"����ѧԺ-˼����");
				animation_P1.set_atlas(&EAM_idle_right);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P1_name, L"����ѧԺ-����");
				animation_P1.set_atlas(&atlas_archi_idle_right);
				break;
			}


			break;

		case 65://A
			//ѡ����ɫ����
			if ((int)player_type_1 == 0)player_type_1 = (PlayerType)Num;//�˴���2�����Ѿ���3����ɫ
			else
			{
				player_type_1 = PlayerType(((int)player_type_1 - 1));
			}

			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//Ϊѡ���Ľ�ɫ�趨����������
			switch (player_type_1)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P1_name, L"��ϢѧԺ-����");
				animation_P1.set_atlas(&atlas_computer_run_right);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P1_name, L"��ѧԺ-�B��");
				animation_P1.set_atlas(&atlas_math_idle_right);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P1_name, L"����ѧԺ-˼����");
				animation_P1.set_atlas(&EAM_idle_right);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P1_name, L"����ѧԺ-����");
				animation_P1.set_atlas(&atlas_archi_idle_right);
				break;
			}


			break;
		case 13://�س�
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager->switch_to(SceneManager::SceneType::Game);

		}

	


	};
	void exit() {
		//����ѡ�����͸�ֵ��Ҷ���
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Computer:
			player_1P = new ComputerPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Math:
			player_1P = new MathPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Eam:
			player_1P = new EAMPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Archi:
			player_1P = new ArchiPlayer();
			player_1P->id = PlayerID::P1;
			break;

		}
		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Computer:
			player_2P = new ComputerPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Math:
			player_2P = new MathPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Eam:
			player_2P = new EAMPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Archi:
			player_2P = new ArchiPlayer();
			player_2P->id = PlayerID::P2;
			break;
		}

		//������ݱ�ʶ ����ѡ�ǳ������л�
		player_1P->setIdentity(identity_1p);
		player_2P->setIdentity(identity_1p);

		
	}

private:
	POINT pos_img_VS = { 0 };// Vs ������ͼƬλ��
	POINT pos_img_tip = { 0 };// ��ʾ��Ϣ�ı�ͼƬλ��
	POINT pos_img_1P = { 0 };// 1P �ı�ͼƬλ��
	POINT pos_img_2P = { 0 };// 2P�ı�ͼƬλ��
	POINT pos_img_3P = { 0 };// 3P�ı�ͼƬλ��
	POINT pos_img_4P = { 0 };

	POINT pos_img_1P_desc = { 0 };//1P��λ����ͼƬλ��
	POINT pos_img_2P_desc = { 0 };// 2P��λ����ͼƬλ��
	POINT pos_img_1P_name = { 0 };//1P��ɫ�����ı�λ��
	POINT pos_img_2P_name = { 0 };//2P��ɫ�����ı�λ��
	POINT pos_animation_1P = { 0 };//1P��ɫ����λ��
	POINT pos_animation_2P = { 0 };// 2P��ɫ����λ��
	POINT pos_animation_3P = { 0 };
	POINT pos_animation_4P = { 0 };

	POINT pos_img_1P_gravestone = { 0 };// 1PĹ��ͼƬλ��
	POINT pos_img_2P_gravestone = { 0 };//2PĹ��ͼƬλ��
	POINT pos_img_3P_gravestone = { 0 };
	POINT pos_img_4P_gravestone = { 0 };

	POINT pos_1P_selector_btn_left = { 0 };//1P�����л���ťλ��
	POINT pos_1P_selector_btn_right = { 0 };// 1P�����л���ťλ��
	POINT pos_2P_selector_btn_left = { 0 };//2P�����л���ťλ��
	POINT pos_2P_selector_btn_right = { 0 };//2P �����л���ťλ��

	Animation animation_P1; //1p����
	Animation animation_P2;//2p����
	Animation animation_player3;
	Animation animation_player4;


	PlayerType player_type_1 = PlayerType::Computer;//1p 2p��ɫ���� 
	PlayerType player_type_2 = PlayerType::Computer;

	TCHAR str_P1_name[256] ;      //�������ó�ʼ���ִ��� ���ﲹȫ���
	TCHAR str_P2_name[256];

	int scorll_line_x = 0; //�����������
	int Num=3;//��ɫ����-1


private:
	void outtexy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};