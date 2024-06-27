#pragma once
#include "bullet.h"
#include "animation.h"
#include "player.h"
extern Camera main_camera;
extern Atlas atlas_computer_bullet;
extern Atlas atlas_computer_bullet_break;
extern Player* player_1P;//1p对象
extern Player* player_2P;//2p对象

class ComputerBullet :public Bullet
{
public:

	ComputerBullet() {
		size = { 64 ,64 };
		type = rand() % 3;//三种子弹
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
		damage = type+1; //伤害分别是1 2 3
		//配置破碎动画
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
			//造成伤害
			player_1P->hp = player_1P->hp - damage >= 0 ? player_1P->hp - damage : 0;
			//增加蓝条 
			player_2P->mp = player_2P->mp + damage * 3 <= 100 ? player_2P->mp + damage * 3 : 100;
			break;
		case PlayerID::P2:
			//造成伤害
			player_2P->hp = player_2P->hp - damage >= 0 ? player_2P->hp - damage : 0;
			//增加蓝条 
			player_1P->mp = player_1P->mp + damage * 3 <= 100 ? player_1P->mp = player_1P->mp + damage * 3 : 100;
			break;
		default:
			break;
		}

		//子弹设置为无效
		valid = 0;

		//mciSendString(_T("open resources/computer/bullet_hit.mp3 alias bgm_hit"), NULL, 0, NULL);
		mciSendString(_T("play bgm_hit from 0"), NULL, 0, NULL);
	}
	void on_update(int delta) {
		pos += velcity * (float)delta;
		if (!valid) {
			animation_break.on_update(delta);
			velcity.x = 0;
		};//无效子弹更新破碎动画

		//检查子弹超出屏幕

		if (check_exceed_screen())can_remove = 1;
		//检查子弹碰撞
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
		//根据子弹状态设置渲染
		if (!can_remove&&valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, img_bullet);
		else if(!can_remove)
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}


private:
	Animation animation_break;//子弹碎裂动画
	IMAGE* img_bullet;//当前种类子弹的图片
	int type ;//子弹种类
};

