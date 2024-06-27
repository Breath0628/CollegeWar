#pragma once
#pragma once
#include "bullet.h"
#include "animation.h"
#include "atlas.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;
extern Camera main_camera;
extern Player* player_1P;//1p对象
extern Player* player_2P;//2p对象
extern 
class EAMBullet :public Bullet
{
public:

	EAMBullet()
	{
		//加载子弹图集资源
		diamond.load_from_file(_T("resources/economy/diamond%d.png"), 6);
		diamondbreak.load_from_file(_T("resources/economy/break%d.png"), 2);
		current_diamond = diamond.get_image(rand() % 6);
		size = { 64 ,64 };
		damage = 2;

		//配置破碎动画
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

		main_camera.shake(5, 250);
		//随机播放豌豆子弹碎裂音效
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
		if (!valid) animation_break.on_update(delta);//无效子弹更新破碎动画
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
		if (valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, current_diamond);
		else
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}
private:
	Animation animation_break;//子弹碎裂动画
	Atlas diamond;
	Atlas diamondbreak;
	IMAGE* current_diamond;
};