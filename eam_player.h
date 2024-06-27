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
	
		//Ϊ��������ͼ��
		animation_idle_left.set_atlas(&EAM_idle_left);
		animation_idle_right.set_atlas(&EAM_idle_right);
		animation_run_left.set_atlas(&EAM_idle_left);
		animation_run_right.set_atlas(&EAM_idle_right);
		animation_attack_ex_left.set_atlas(&EAM_attack_left);
		animation_attack_ex_right.set_atlas(&EAM_attack_right);
		//���ö���֡���
		animation_idle_left.set_interval(75);
		animation_idle_right.set_interval(75);
		animation_run_left.set_interval(75);
		animation_run_right.set_interval(75);
		animation_attack_ex_left.set_interval(75);
		animation_attack_ex_right.set_interval(78);
		//��ʱ������
		timer_attack_ex.set_wait_time(attack_ex_duration);//����״̬��ʱ
		timer_attack_ex.set_one_shot(1);
		timer_attack_ex.set_callback([&]() {
			is_attacking_ex = 0;
			});

		timer_spwan_diamond_ex.set_wait_time(100);//���⹥��ʱ�����ӵ����ɶ�ʱ
		timer_spwan_diamond_ex.set_one_shot(0);
		timer_spwan_diamond_ex.set_callback([&]() {
			spawn_bigdiamond_bullet(speed_diamond_ex);
			});
		//cd
		attack_cd = 500;
	}
	void on_update(int delta) {
		Player::on_update(delta);//���ø��෽��

		if (is_attacking_ex)
		{
			main_camera.shake(5, 100);
			timer_attack.on_update(delta);
			timer_spwan_diamond_ex.on_update(delta);
		}

	}
	void on_attack() {//��ͨ����
		spawn_diamond_bullet(speed_diamond);
		//���������Ч
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
		//��ɫ����
		is_attacking_ex = 1;
		timer_attack_ex.restart();
		is_facing_right ? animation_attack_ex_right.reset() : animation_attack_ex_left.reset();
		mciSendString(_T("play pea_shoot_ex from 0"), NULL, 0, NULL);
	};

private:
	void spawn_diamond_bullet(float speed) {
		//�����ӵ�
		Bullet* bullet = new EAMBullet();
		Vector2<float> bullet_pos, bullet_velocity;
		const Vector2<float>& bullet_size = bullet->size;
		//���ӵ����ĵ�����Ϊ����ͷ����Ե
		bullet_pos.x = is_facing_right ?pos.x + size.x - bullet_size.x / 2: pos.x - bullet_size.x / 2;
		bullet_pos.y = pos.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;
		bullet->pos = bullet_pos;
		bullet->velcity = bullet_velocity;
		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;//�����ӵ�Ŀ��
		bullet->set_callback([&]() {mp += 25; });
		bullet_list.push_back(bullet);//���ӵ������ӵ�����
	}
	void spawn_bigdiamond_bullet(float speed)
	{
		//�����ӵ�
		Bullet* bullet = new EAMBulletEX();
		Vector2<float> bullet_pos, bullet_velocity;
		const Vector2<float>& bullet_size = bullet->size;
		//���ӵ����ĵ�����Ϊ����ͷ����Ե
		bullet_pos.x = is_facing_right ? pos.x + size.x - bullet_size.x / 2 : pos.x - bullet_size.x / 2;
		bullet_pos.y = pos.y;
		bullet_velocity.x = is_facing_right ? speed : -speed;
		bullet_velocity.y = 0;
		bullet->pos = bullet_pos;
		bullet->velcity = bullet_velocity;
		bullet->target_id = id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1;//�����ӵ�Ŀ��
		bullet->set_callback([&]() {mp += 25; });
		bullet_list.push_back(bullet);//���ӵ������ӵ�����

	}
private:
	const float speed_diamond = 0.9f;//�ӵ��ٶ�
	const float speed_diamond_ex = 1.5f;
	const int attack_ex_duration = 2500;//���⹥��״̬����
	Timer timer_attack_ex;//����״̬��ʱ
	Timer timer_spwan_diamond_ex;//�ӵ����ɶ�ʱ

private:


};
