#pragma once
#include "bullet.h"
#include "animation.h"
#include "math.h"
#include <mmsystem.h>
extern Camera main_camera;
extern IMAGE img_math;
extern Atlas atlas_math_break;

class mathBullet :public Bullet
{
public:

	mathBullet() {
		size = { 64 ,64 };
		damage = 2;
		//�������鶯��
		animation_break.set_atlas(&atlas_math_break);
		animation_break.set_interval(200);
		animation_break.set_loop(0);
		animation_break.set_callback([&]() {can_remove = 1; });
	};
	~mathBullet() = default;

	void on_collide() {
		Bullet::on_collide();
		main_camera.shake(5, 250);
		switch (target_id)
		{
		case PlayerID::P1:
			//����˺�
			player_1P->hp = player_1P->hp - damage >= 0 ? player_1P->hp - damage : 0;
			//�������� 
			player_2P->mp = player_2P->mp + damage * 3 <= 100 ?player_2P->mp + damage * 3 : 100;
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
		valid = 0;
		//��������㶹�ӵ�������Ч
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
		if (valid) {
			velcity.y = 3 * sinf(pos.x);
			pos += velcity * (float)delta;
		}
		if (!valid) animation_break.on_update(delta);//��Ч�ӵ��������鶯��
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
		if (!can_remove && valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, &img_math);
		else if (!can_remove)
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
		
	}
private:
	Animation animation_break;//�㶹�ӵ����Ѷ���
};


