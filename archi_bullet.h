#pragma once
#include "bullet.h"
#include "animation.h"
#include "mciapi.h"
extern Camera main_camera;
extern IMAGE img_archi_bullet;
extern Atlas atlas_archi_break;
extern Player* player_1P;//1p����
extern Player* player_2P;//2p����


class ArchiBullet :public Bullet
{
public:

	ArchiBullet() {
		size = { 80 ,80 };
		damage = 2;
		//�������鶯��
		animation_break.set_atlas(&atlas_archi_break);
		animation_break.set_interval(100);
		animation_break.set_loop(0);
		animation_break.set_callback([&]() {can_remove = 1; });
	};
	~ArchiBullet() = default;

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

		main_camera.shake(5, 250);

		//��������ӵ�������Ч
		switch (rand() % 3)
		{
		case 0:
			mciSendString(_T("play pea_break_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_break_2 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play pea_break_3 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	}
	void on_update(int delta) {

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

		pos += velcity * (float)delta;
		if (!valid) animation_break.on_update(delta);//��Ч�ӵ��������鶯��
		if (check_exceed_screen())can_remove = 1;

	}
	void on_draw(const Camera& camera) const {
		//�����ӵ�״̬������Ⱦ
		if (valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, &img_archi_bullet);
		else
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}
private:
	Animation animation_break;//�㶹�ӵ����Ѷ���

};

