#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "peashooter_player.h"
#include "sunflower_player.h"

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
extern IMAGE img_gravestone_left;//�������Ĺ��ͼ
extern IMAGE img_gravestone_right;//Ĺ������
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

extern IMAGE img_peashooter_selector_background_left;  // ѡ�ǽ��泯����������ֱ���ͼƬ
extern IMAGE img_peashooter_selector_background_right; // ѡ�ǽ��泯���ҵ������ֱ���ͼƬ
//extern IMAGE img_archi_static;
//extern IMAGE img_archi_angery;

extern IMAGE img_sunflower_selector_background_left;   // ѡ�ǽ��泯��������տ�����ͼƬ
extern IMAGE img_sunflower_selector_background_right;  // ѡ�ǽ��泯���ҵ����տ�����ͼƬ


extern Atlas atlas_peashooter_idle_left;               // �����ֳ������Ĭ�϶���ͼ��   
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_left;

extern Atlas atlas_player3_idle;                       //34������ﻹû����
extern Atlas atlas_player4_idle;

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;
private:
	enum class PlayerType {
		Peashooter = 0,
		Sunflower,
		Invalid
	};


private:
	void on_enter() {

		//Ϊ��ɫ��������ͼ����֡���

		animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&atlas_sunflower_idle_right);
		animation_player3.set_atlas(&atlas_player3_idle);    //
		animation_player4.set_atlas(&atlas_player4_idle);

		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);
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
		pos_img_4P.x = pos_img_2P.x;
		pos_img_4P.y = pos_img_3P.y;

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

		pos_animation_1P.x = pos_img_1P_gravestone.x + (pos_img_1P_gravestone.x - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 - OFFSET_X - 22;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 50;
		pos_animation_2P.x = pos_img_2P_gravestone.x + 50;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_animation_3P.x = pos_animation_1P.x;
		pos_animation_3P.y = pos_img_3P_gravestone.y + 50;
		pos_animation_4P.x = pos_animation_2P.x;
		pos_animation_4P.y = pos_animation_3P.y;

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


		//input_timer.set_one_shot(1);
		//input_timer.set_wait_time(500);

	}
	void on_update(int delta) {
		//��ɫ��������
		animation_peashooter.on_update(delta);
		animation_sunflower.on_update(delta);
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

		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter:
			p1_scorll_bk = &img_peashooter_selector_background_right;
			break;
		case SelectorScene::PlayerType::Sunflower:
			p1_scorll_bk = &img_sunflower_selector_background_right;
			break;
		default:
			p1_scorll_bk = &img_peashooter_selector_background_right;
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			p2_scorll_bk = &img_peashooter_selector_background_left;
			break;
		case SelectorScene::PlayerType::Sunflower:
			p2_scorll_bk = &img_sunflower_selector_background_left;
			break;
		default:
			p2_scorll_bk = &img_peashooter_selector_background_left;
			break;
		}

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

		puimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		puimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);
		puimage_alpha(pos_img_3P_gravestone.x, pos_img_3P_gravestone.y, &img_gravestone_3);
		puimage_alpha(pos_img_4P_gravestone.x, pos_img_4P_gravestone.y, &img_gravestone_4);

		puimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);



		//��Ⱦ1p 2p��ɫ����
		animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		animation_player3.on_draw(camera, pos_animation_3P.x, pos_animation_3P.y);
		animation_player4.on_draw(camera, pos_animation_4P.x, pos_animation_4P.y);

		//��Ⱦ����
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter:
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtexy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::Sunflower:
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtexy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtexy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::Sunflower:
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtexy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
			break;

		}


	}
	void on_input(const ExMessage& msg) {            //�����������½�ɫ����޸�
		//��ɫѡȡ ������ת
		if (msg.message != WM_KEYUP) return;

		switch (msg.vkcode)
		{
		case 39://->
			if (player_type_2 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Peashooter;
				animation_sunflower.set_atlas(&atlas_peashooter_idle_left); //ע�ⷽ��
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Sunflower;
				animation_sunflower.set_atlas(&atlas_sunflower_idle_left);
			}
			break;

		case 37://<-
			if (player_type_2 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Peashooter;
				animation_sunflower.set_atlas(&atlas_peashooter_idle_left); //ע�ⷽ��
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Sunflower;
				animation_sunflower.set_atlas(&atlas_sunflower_idle_left);
			}

			break;
		case 68://D
			if (player_type_1 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Peashooter;
				animation_peashooter.set_atlas(&atlas_peashooter_idle_right); //ע�ⷽ��
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Sunflower;
				animation_peashooter.set_atlas(&atlas_sunflower_idle_right);
			}

			break;
		case 65://A
			if (player_type_1 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Peashooter;
				animation_peashooter.set_atlas(&atlas_peashooter_idle_right); //ע�ⷽ��
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Sunflower;
				animation_peashooter.set_atlas(&atlas_sunflower_idle_right);
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
		case SelectorScene::PlayerType::Peashooter:
			player_1P = new PeashooterPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Sunflower:
			player_1P = new SunflowerPlayer();
			player_1P->id = PlayerID::P1;
			break;

		}
		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			player_2P = new PeashooterPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Sunflower:
			player_2P = new SunflowerPlayer();
			player_2P->id = PlayerID::P2;
			break;

		}
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

	Animation animation_peashooter; //�㶹���� -->1p����
	Animation animation_sunflower;//���տ�����-->2p����
	Animation animation_player3;
	Animation animation_player4;


	PlayerType player_type_1 = PlayerType::Peashooter;//1p 2p��ɫ����
	PlayerType player_type_2 = PlayerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("����ѧԺ");      //�������ó�ʼ���ִ��� ���ﲹȫ���
	LPCTSTR str_sunflower_name = _T("��ϢѧԺ");

	int scorll_line_x = 0; //�����������



private:
	void outtexy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};