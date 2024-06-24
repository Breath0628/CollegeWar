#pragma once
#include "bullet.h"
#include "animation.h"
#include "player.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;
extern Player* player_1P;//1p对象
extern Player* player_2P;//2p对象

class PeaBullet:public Bullet
{
public:

	PeaBullet() {
		size = { 64 ,64 };
		damage = 10;
		//配置破碎动画
		animation_break.set_atlas(&atlas_pea_break);
		animation_break.set_interval(100);
		animation_break.set_loop(0);
		animation_break.set_callback([&]() {can_remove = 1;});
	};
	~PeaBullet()=default;

	void on_collide() {
		Bullet::on_collide();
		switch (target_id)
		{
		case PlayerID::P1:
			//造成伤害
			player_1P->hp -= damage;
			//增加蓝条 
			player_2P->mp += damage * 2;
			break;
		case PlayerID::P2:
			//造成伤害
			player_2P->hp -= damage;
			//增加蓝条 
			player_1P->hp += damage * 2;
			break;
		default:
			break;
		}
		
		
		//随机播放豌豆子弹碎裂音效
		switch (rand()%3)
		{
		case 0:
			mciSendString(_T("play pea_break_1 from 0"), NULL,0,NULL);
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
		if (valid) puimage_alpha(camera, (int)pos.x,(int)pos.y ,&img_pea);
		else
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}
	

private:
	Animation animation_break;//豌豆子弹碎裂动画
	
};

