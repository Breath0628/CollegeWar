#pragma once
#include "player.h"
#include <iostream>
#include "animation.h"
#include "computer_bullet.h"

//计算机角色
extern Atlas atlas_computer_idle_left;               // 向左的默认动画图集
extern Atlas atlas_computer_idle_right;              // 向右的默认动画图集
extern Atlas atlas_computer_run_left;                // 朝向左的跑步动画图集
extern Atlas atlas_computer_run_right;               // 朝向右的跑步动画图集
extern Atlas atlas_computer_attack_left;             // 朝向左的攻击动画图集     
extern Atlas atlas_computer_attack_right;	// 向右的攻击动画图集
extern Atlas atlas_computer_attack_ex_left;             // 朝向左的特殊攻击动画图集     
extern Atlas atlas_computer_attack_ex_right;	// 向右的特殊攻击动画图集
extern Atlas atlas_computer_ex;//释放技能特效

class ComputerPlayer : public Player
{
public:
	ComputerPlayer() {
	
		//为动画设定图集
		animation_idle_left.set_atlas(&atlas_computer_idle_left);
		animation_idle_right.set_atlas(&atlas_computer_idle_right);
		animation_run_left.set_atlas(&atlas_computer_run_left);
		animation_run_right.set_atlas(&atlas_computer_run_right);
		animation_computer_attack_left.set_atlas(&atlas_computer_attack_left);
		animation_computer_attack_right.set_atlas(&atlas_computer_attack_right);
		animation_attack_ex_left.set_atlas(&atlas_computer_attack_ex_left);
		animation_attack_ex_right.set_atlas(&atlas_computer_attack_ex_right);
		animation_computer_ex.set_atlas(&atlas_computer_ex);
		//设置动画帧间隔
		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_computer_attack_left.set_interval(75);
		animation_computer_attack_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(75);
		animation_computer_ex.set_interval(300);
		animation_computer_ex.set_loop(0);
		animation_computer_ex.set_callback([&]() {
			animation_computer_ex.reset();
			});
		//定时器配置
		timer_attack_ex.set_wait_time(attack_ex_duration);//特殊状态定时
		timer_attack_ex.set_one_shot(1);
		timer_attack_ex.set_callback([&]() {
			is_attacking_ex = 0;
			});
		timer_spwan_pea_ex.set_wait_time(100);//特殊攻击时生成子弹生成定时
		timer_spwan_pea_ex.set_one_shot(0);
		timer_spwan_pea_ex.set_callback([&]() {
			spawn_pea_bullet(speed_pea_ex);
			});
		//cd
		attack_cd = 500;
		timer_attack.set_wait_time(attack_cd);
		timer_attack.set_one_shot(1);
		timer_attack.set_callback([&]() {
			can_attck = 1;
			});
		//技能音效
		timer_ex_sound.set_wait_time(250);
		timer_ex_sound.set_one_shot(0);
		timer_ex_sound.set_callback([&]() {
	
			});
	};
	~ComputerPlayer() = default;

	void on_update(int delta) {
		
		if (pos.y > 800)//掉出
		{
			hp = 0;
		}
		if (hp <= 0)
		{
			dieTimer.on_update(delta);

		}
		if (pos.x < 0)
		{
			pos.x = 0;
		}
		if (pos.x > 1210)
		{
			pos.x = 1210;
		}

		if (!exam_suc && exam_time >= 5000) { exam_suc = 1; hp += 100; }
		int direction = is_right_key_down - is_left_key_down;//玩家是否移动

		if (direction != 0) {
			//移动
			is_facing_right = direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
		
			float dis = direction * speed * delta;//向右移动距离
			run(dis);
		}
		else
		{
			if (hp <= 0)
			{
				current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			}
			else {
				//静止
				current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			}
		}
		if (!can_attck)
		{//在攻击间隔时切换攻击动画
			current_animation = is_facing_right ? &animation_computer_attack_right : &animation_computer_attack_left;
		}
		if (is_attacking_ex)
		{
			current_animation = is_facing_right ? &animation_attack_ex_right : &animation_attack_ex_left;
		}
		timer_attack.on_update(delta);
		move_collide(delta);
		current_animation->on_update(delta);
		//特殊攻击期间
		if (is_attacking_ex)
		{
			
			main_camera.shake(5, 100);
			timer_attack.on_update(delta);
			timer_attack_ex.on_update(delta);
			timer_spwan_pea_ex.on_update(delta);
			animation_computer_ex.on_update(delta);
			timer_ex_sound.on_update(delta);
		}

		switch (id)
		{
		case PlayerID::P1:
			if (shift_down)
			{
				animation_recovery.on_update(delta);
				exam_time += delta;
				animation_begin.on_update(delta);
			}
		case PlayerID::P2:
			if (ctrl_down)
			{
				exam_time += delta;
				animation_recovery.on_update(delta);
				animation_begin.on_update(delta);
			}
		}
	
	}
	void on_draw(const Camera& camera) {
		Player::on_draw(camera);
		if (is_attacking_ex)
		{
			animation_computer_ex.on_draw(camera,0, 0);
		}
	}
	void on_attack() {//普通攻击
		spawn_pea_bullet(speed_pea);
		can_attck = 0;
		timer_attack.restart();
		//随机播放音效
		
		mciSendString(_T("play computer_shoot from 0"), NULL, 0, NULL);

	};
	void on_attack_ex() {
		//特色攻击
		timer_ex_sound.restart();
		is_attacking_ex = 1;
		timer_attack_ex.restart();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
		//mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	};

private:
	void spawn_pea_bullet(float speed) {
		//生成子弹
		Bullet* bullet = new ComputerBullet();
		Vector2<float> bullet_pos, bullet_velocity;
		const Vector2<float>& bullet_size = bullet->size;

		//将子弹中心点设置为人物头部边缘
		bullet_pos.x = is_facing_right ?
			pos.x + size.x - bullet_size.x / 2
			: pos.x - bullet_size.x / 2;
		bullet_pos.y = pos.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;
		bullet->pos = bullet_pos;
		bullet->velcity = bullet_velocity;
		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;//设置子弹目标
		bullet->set_callback([&]() {mp += 25;});
		bullet_list.push_back(bullet);//将子弹加入子弹数组
	}
	
private:
	
	const float speed_pea = 0.75f;//子弹速度
	const float speed_pea_ex = 1.5f;
	const int attack_ex_duration = 2500;//特殊攻击状态持续
	
	Timer timer_attack_ex;//特殊状态定时
	Timer timer_spwan_pea_ex;//子弹生成定时
	Timer timer_ex_sound;//技能音效
	Animation animation_computer_attack_left;
	Animation animation_computer_attack_right;
	Animation animation_computer_ex;
	Animation animation_computer_attack_ex_left;
	Animation animation_computer_attack_ex_right;
	
};


