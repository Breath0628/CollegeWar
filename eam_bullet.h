#pragma once
#pragma once
#include "bullet.h"
#include "animation.h"
#include "atlas.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;
extern Camera main_camera;
extern Player* player_1P;//1p����
extern Player* player_2P;//2p����
extern 
class EAMBullet :public Bullet
{
public:

	EAMBullet()
	{
		//�����ӵ�ͼ����Դ
		diamond.load_from_file(_T("resources/economy/diamond%d.png"), 6);
		diamondbreak.load_from_file(_T("resources/economy/break%d.png"), 2);
		current_diamond = diamond.get_image(rand() % 6);
		size = { 64 ,64 };
		damage = 2;

		//�������鶯��
		animation_break.set_atlas(&diamondbreak);
		animation_break.set_interval(75);
		animation_break.set_loop(0);
		animation_break.set_callback([&]() {can_remove = 1; });
	}
	~EAMBullet() = default;

	void on_collide() 
	{
		Bullet::on_collide();

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
		pos += velcity * (float)delta;
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
		if (valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, current_diamond);
		else
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}
private:
	Animation animation_break;//�ӵ����Ѷ���
	Atlas diamond;
	Atlas diamondbreak;
	IMAGE* current_diamond;
};