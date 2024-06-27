#pragma once
#include "bullet.h"
#include "animation.h"
#include "player.h"
extern Camera main_camera;
extern Atlas atlas_computer_bullet;
extern Atlas atlas_computer_bullet_break;
extern Player* player_1P;//1p����
extern Player* player_2P;//2p����

class ComputerBullet :public Bullet
{
public:

	ComputerBullet() {
		size = { 64 ,64 };
		type = rand() % 3;//�����ӵ�
		switch (type)
		{case 0:
			size = { 50,50 };
			break;
		case 1:
			size = { 64,64 };
			break;
		case 2:
			size = { 80,80 };
			break;
		}
		img_bullet= atlas_computer_bullet.get_image(type);
		damage = type+1; //�˺��ֱ���1 2 3
		//�������鶯��
		animation_break.set_atlas(&atlas_computer_bullet_break);
		animation_break.set_interval(200);
		animation_break.set_loop(0);
		animation_break.set_callback([&]() {can_remove = 1;});
	};
	~ComputerBullet() = default;

	void on_collide() {
		Bullet::on_collide();
		main_camera.shake(5, 250);
		switch (target_id)
		{
		case PlayerID::P1:
			//����˺�
			player_1P->hp = player_1P->hp - damage >= 0 ? player_1P->hp - damage : 0;
			//�������� 
			player_2P->mp = player_2P->mp + damage * 3 <= 100 ? player_2P->mp + damage * 3 : 100;
			break;
		case PlayerID::P2:
			//����˺�
			player_2P->hp = player_2P->hp - damage >= 0 ? player_2P->hp - damage : 0;
			//�������� 
			player_1P->mp = player_1P->mp + damage * 3 <= 100 ? player_1P->mp = player_1P->mp + damage * 3 : 100;
			break;
		default:
			break;
		}

		//�ӵ�����Ϊ��Ч
		valid = 0;

		//mciSendString(_T("open resources/computer/bullet_hit.mp3 alias bgm_hit"), NULL, 0, NULL);
		mciSendString(_T("play bgm_hit from 0"), NULL, 0, NULL);
	}
	void on_update(int delta) {
		pos += velcity * (float)delta;
		if (!valid) {
			animation_break.on_update(delta);
			velcity.x = 0;
		};//��Ч�ӵ��������鶯��

		//����ӵ�������Ļ

		if (check_exceed_screen())can_remove = 1;
		//����ӵ���ײ
		switch (target_id)
		{
		case PlayerID::P1:
			if (check_collision(player_1P->pos, player_1P->size)) on_collide();
			break;
		case PlayerID::P2:
			if (check_collision(player_2P->pos, player_2P->size)) on_collide();
			break;
		}


	}
	void on_draw(const Camera& camera) const {
		//�����ӵ�״̬������Ⱦ
		if (!can_remove&&valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, img_bullet);
		else if(!can_remove)
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}


private:
	Animation animation_break;//�ӵ����Ѷ���
	IMAGE* img_bullet;//��ǰ�����ӵ���ͼƬ
	int type ;//�ӵ�����
};

