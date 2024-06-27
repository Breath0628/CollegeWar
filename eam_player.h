#pragma once
#include "player.h"
#include <iostream>
#include "animation.h"
#include "eam_bullet.h"
#include "eam_bullet_ex.h"
#include "utli.h"
#include "atlas.h"
extern Atlas EAM_idle_left;
extern Atlas EAM_idle_right;
extern Atlas EAM_attack_left;
extern Atlas EAM_attack_right;
extern Atlas EAM_attack_ex_left;
extern Atlas EAM_attack_ex_right;

class EAMPlayer :public Player
{
public:
	EAMPlayer()
	{
	
		//为动画设置图集
		animation_idle_left.set_atlas(&EAM_idle_left);
		animation_idle_right.set_atlas(&EAM_idle_right);
		animation_run_left.set_atlas(&EAM_idle_left);
		animation_run_right.set_atlas(&EAM_idle_right);
		animation_attack_ex_left.set_atlas(&EAM_attack_left);
		animation_attack_ex_right.set_atlas(&EAM_attack_right);
		//设置动画帧间隔
		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(78);
		//定时器配置
		timer_attack_ex.set_wait_time(attack_ex_duration);//特殊状态定时
		timer_attack_ex.set_one_shot(1);
		timer_attack_ex.set_callback([&]() {
			is_attacking_ex = 0;
			});

		timer_spwan_diamond_ex.set_wait_time(100);//特殊攻击时生成子弹生成定时
		timer_spwan_diamond_ex.set_one_shot(0);
		timer_spwan_diamond_ex.set_callback([&]() {
			spawn_bigdiamond_bullet(speed_diamond_ex);
			});
		//cd
		attack_cd = 500;
	}
	void on_update(int delta) {
		Player::on_update(delta);//调用父类方法

		if (is_attacking_ex)
		{
			main_camera.shake(5, 100);
			timer_attack.on_update(delta);
			timer_spwan_diamond_ex.on_update(delta);
		}

	}
	void on_attack() {//普通攻击
		spawn_diamond_bullet(speed_diamond);
		//随机播放音效
		switch (rand() % 2)
		{
		case 0:
			mciSendString(_T("play pea_shoot_1 from 0"), NULL, 0, NULL);
			break;
		case 1:
			mciSendString(_T("play pea_shoot_2 from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
	};
	void on_attack_ex() {
		//特色攻击
		is_attacking_ex = 1;
		timer_attack_ex.restart();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	};

private:
	void spawn_diamond_bullet(float speed) {
		//生成子弹
		Bullet* bullet = new EAMBullet();
		Vector2<float> bullet_pos, bullet_velocity;
		const Vector2<float>& bullet_size = bullet->size;
		//将子弹中心点设置为人物头部边缘
		bullet_pos.x = is_facing_right ?pos.x + size.x - bullet_size.x / 2: pos.x - bullet_size.x / 2;
		bullet_pos.y = pos.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;
		bullet->pos = bullet_pos;
		bullet->velcity = bullet_velocity;
		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;//设置子弹目标
		bullet->set_callback([&]() {mp += 25; });
		bullet_list.push_back(bullet);//将子弹加入子弹数组
	}
	void spawn_bigdiamond_bullet(float speed)
	{
		//生成子弹
		Bullet* bullet = new EAMBulletEX();
		Vector2<float> bullet_pos, bullet_velocity;
		const Vector2<float>& bullet_size = bullet->size;
		//将子弹中心点设置为人物头部边缘
		bullet_pos.x = is_facing_right ? pos.x + size.x - bullet_size.x / 2 : pos.x - bullet_size.x / 2;
		bullet_pos.y = pos.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;
		bullet->pos = bullet_pos;
		bullet->velcity = bullet_velocity;
		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;//设置子弹目标
		bullet->set_callback([&]() {mp += 25; });
		bullet_list.push_back(bullet);//将子弹加入子弹数组

	}
private:
	const float speed_diamond = 0.9f;//子弹速度
	const float speed_diamond_ex = 1.5f;
	const int attack_ex_duration = 2500;//特殊攻击状态持续
	Timer timer_attack_ex;//特殊状态定时
	Timer timer_spwan_diamond_ex;//子弹生成定时

private:


};
