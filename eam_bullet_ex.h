#pragma once
#pragma once
#pragma once
#include "bullet.h"
#include "animation.h"
#include "atlas.h"

extern IMAGE img_pea;
extern Atlas atlas_pea_break;
extern Camera main_camera;

class EAMBulletEX :public Bullet
{
public:

	EAMBulletEX() {
		//加载子弹图集资源
		bigdiamond.load_from_file(_T("resources/economy/bigdiamond%d.png"), 4);
		bigdiamondbreak.load_from_file(_T("resources/economy/bigbreak%d.png"), 6);
		current_bigdiamond = bigdiamond.get_image(rand() % 3);

		size = { 100 , 100 };
		damage = 2;
		//配置破碎动画
		animation_break.set_atlas(&bigdiamondbreak);
		animation_break.set_interval(100);
		animation_break.set_loop(0);
		animation_break.set_callback([&]() {can_remove = 1; });
	};
	~EAMBulletEX() = default;

	void on_collide() {
		Bullet::on_collide();
		main_camera.shake(10, 250);
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
		if (!valid) animation_break.on_update(delta);//无效子弹更新破碎动画
		if (check_exceed_screen())can_remove = 1;
	}
	void on_draw(const Camera& camera) const {
		//根据子弹状态设置渲染
		if (valid) puimage_alpha(camera, (int)pos.x, (int)pos.y, current_bigdiamond);
		else
		{
			animation_break.on_draw(camera, (int)pos.x, (int)pos.y);
		}
	}
private:
	Animation animation_break;//子弹碎裂动画
	Atlas bigdiamond;
	Atlas bigdiamondbreak;
	IMAGE* current_bigdiamond;
};