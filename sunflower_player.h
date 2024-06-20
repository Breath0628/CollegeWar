#pragma once

#include "player.h"
#include <iostream>
#include "sunflower_player.h"
#include "sun_bullet.h"

extern Atlas atlas_sunflower_idle_left;                // 龙日葵朝向左的默认动画图集
extern Atlas atlas_sunflower_idle_right;               // 龙日葵朝向右的默认动画图集
extern Atlas atlas_sunflower_run_left;                 // 龙日葵朝向左的跑步动画图集
extern Atlas atlas_sunflower_run_right;                // 龙日葵朝向右的跑步动画图集
extern Atlas atlas_sunflower_attack_ex_left;             // 龙日葵朝向左的攻击动画图集
extern Atlas atlas_sunflower_attack_ex_right;            // 龙日葵朝向右的攻击动画图集
extern Atlas atlas_sun_text;                           // “日” 文本动画图集
extern Player* player_1P;
extern Player* player_2P;

class SunflowerPlayer : public Player
{
public:
	SunflowerPlayer() {
		//为动画设定图集
		animation_idle_left.set_atlas(&atlas_sunflower_idle_left);
		animation_idle_right.set_atlas(&atlas_sunflower_idle_right);
		animation_run_left.set_atlas(&atlas_sunflower_run_left);
		animation_run_right.set_atlas(&atlas_sunflower_run_right);
		animation_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
		animation_sun_text.set_atlas(&atlas_sun_text);
		//设置动画帧间隔
		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(100);
		animation_attack_ex_right.set_interval(100);
		animation_sun_text.set_interval(100);
		//单次播放
		animation_attack_ex_left.set_loop(0);
		animation_attack_ex_right.set_loop(0);
		animation_sun_text.set_loop(0);
		//动画播放完毕后回调函数
		animation_attack_ex_left.set_callback([&]() {
			is_attacking_ex = 0;
			is_sun_text_visible = 0;
			});
		animation_attack_ex_right.set_callback([&]() {
			is_attacking_ex = 0;
			is_sun_text_visible = 0;
			});

		attack_cd = 250;
	};
	~SunflowerPlayer() = default;

	void on_update(int delta) {
		Player::on_update(delta);
		if (is_sun_text_visible)
		{
			animation_sun_text.on_update(delta);
		}
		
	}
	void on_draw(const Camera& camera) {
		Player::on_draw(camera);
		if (is_sun_text_visible)
		{//文本渲染位置
			Vector2<float> text_pos;
			IMAGE* frame = animation_sun_text.get_frame();
			text_pos = {
			pos.x - (size.x - frame->getwidth()) / 2,
			pos.y - frame->getheight()
			};
			animation_sun_text.on_draw(camera, (int)text_pos.x, (int)text_pos.y);
		}

	}
	void on_attack() {//普通攻击
		Bullet* bullet = new SunBullet();
		//日光炸弹生成位置
		Vector2<float> bullet_pos;
		const Vector2<float>& bullet_size = bullet->size;
		bullet_pos.x = pos.x + (size.x - bullet_size.x) / 2;
		bullet_pos.y = pos.y;
		bullet->pos = bullet_pos;
		//初始速度继承角色并具有初速度
		bullet->velcity.x += is_facing_right ? velocity.x +0.5f :-velocity.x-0.5f;
		bullet->velcity.y += velocity.y-0.8f;
		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;
		bullet->set_callback([&]() {mp += 35;});
		bullet_list.push_back(bullet);
	};
	void on_attack_ex(//特色攻击
	) {
		is_attacking_ex = 1;
		is_sun_text_visible = 1;
		animation_sun_text.reset();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();

		Bullet* bullet = new SunBulletEX();
		Player* target_player = id == PlayerID::P1 ? player_1P: player_2P;
		//设置子弹位置速度
		Vector2<float> bullet_pos, bullet_velocity;
		const Vector2<float> bullet_size = bullet->size;
		const Vector2<float> target_size = target_player->size;
		const Vector2<float> target_pos = target_player->pos;
		bullet_pos = {
			target_pos.x+(target_size.x-bullet_size.x)/2,-size.y
		};
		bullet_velocity = {0,speed_sun_ex};
		bullet->pos = bullet_pos;
		bullet->velcity = bullet_velocity;

		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;//设置子弹目标
		bullet->set_callback([&]() {mp += 50;});
		bullet_list.push_back(bullet);
		mciSendString(_T("play sun_text from 0"), NULL, 0, NULL);

	};
private:
	Animation animation_sun_text;//头顶动画
	bool is_sun_text_visible = 0;
	const float speed_sun_ex = 0.15f;//特殊炸弹速度
	const Vector2<float> velocity_sun = { 0.25f,-0.5f };//普通炸弹速度
};


