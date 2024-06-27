#pragma once
#define VK_CTRL           0x11   //Ctrl��
#define VK_SHIFT          0x10   //shift��
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdexcept>
#include "camera.h"
#include <graphics.h>
#include "vector2.h"
#include "platform.h"
#include "bullet.h"
#include "player_id.h"

extern std::vector<Bullet*>bullet_list;//�ӵ�����  
extern std::vector<Platform> platform_list; //ƽ̨����
extern Camera main_camera;


class Player
{
public:
	Player() { 
		current_animation = &animation_idle_right;
		//������ʱ������
		timer_attack.set_wait_time(attack_cd);
		timer_attack.set_one_shot(1);
		timer_attack.set_callback([&]() {
			can_attck = 1;
			});

		//�������˵�����ʱ
		dieTimer.set_callback([&]() {
			try {
				char buffer[128];
				char text[128];
				sprintf(text, "P%dʧ��!",int(id)+1);

				writeStringAndTimeToFile("record.txt", text);
				//std::string readTime = readTimeFromFile("record.txt");
			}
			catch (const std::exception& e) {
				std::cerr << "�쳣: " << e.what() << std::endl;
			}
			scene_manager->switch_to(SceneManager::SceneType::Menu);
			});
		dieTimer.set_one_shot(1);
		dieTimer.set_wait_time(5000);

		//���ػָ�ͼ����Դ
		begin.load_from_file(_T("resources/recovery/begin%d.png"), 2);
		recovery.load_from_file(_T("resources/recovery/recovery%d.png"), 3);
		//���ûָ�����
		animation_begin.set_atlas(&begin);
		animation_begin.set_interval(75);
		animation_begin.set_loop(1);
		//animation_begin.set_callback([&]() {can_remove = 0; });

		animation_recovery.set_atlas(&recovery);
		animation_recovery.set_interval(200);
		animation_recovery.set_loop(1);
		//animation_recovery.set_callback([&]() {can_remove = 0; });
	};
	~Player();
	
	virtual void setIdentity(int ident){
	//�������
		identity = ident;
		if (identity == 1 && hp != 200) {
			//��ʹ���
			hp = 200;
		}
		if (identity == 2 && attack_cd != 333) {
			//��ħ���
			attack_cd = 333;
		}
	}

	virtual void on_update(int delta) {
		if (pos.y>800)//����
		{
			hp = 0;
		}
		if (hp<=0)
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
		
		
		if (!exam_suc && exam_time >= 5000) {
			mciSendString(_T("play upgrade from 0"), NULL, 0, NULL);
			exam_suc = 1; hp +=100; }
		int direction = is_right_key_down - is_left_key_down;//����Ƿ��ƶ�
		
		if (direction != 0) {
			//�ƶ�
			is_facing_right = direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float dis = direction *speed * delta;//�����ƶ�����
			run(dis);
		}
		
		else
		{
			if (hp<=0)
			{
				current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			}
			else {
				//��ֹ
				current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			}
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

		timer_attack.on_update(delta);
		move_collide(delta);
		current_animation->on_update(delta);
		
	}
	virtual void on_draw(const Camera& camera) 
	{
		current_animation->on_draw(camera,(int)(pos.x), (int)(pos.y));//��Ⱦ��ǰ����
		TCHAR text2[256];
		if (!exam_suc)
		{
			switch (id)
			{
			case PlayerID::P1:
				if (shift_down)
				{
					animation_recovery.on_draw(camera, (int)(pos.x) - 60, (int)(pos.y) - 50);
				}
			case PlayerID::P2:
				if (ctrl_down)
				{
					animation_recovery.on_draw(camera, (int)(pos.x) - 60, (int)(pos.y) - 50);
				}
			}
		}
		if (exam_suc)
		{
			animation_begin.on_draw(camera, (int)(pos.x) - 12, (int)(pos.y) - 70);
		}
		//�������ֲ���
		if (hp <= 0)
		{	
			settextstyle(54, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			_stprintf_s(text2, L"P%d��������Ϸ������", (int)id + 1);

			outtextxy(450, 300, text2);

		}
		

		TCHAR text[256];
		//��ʾ������Ѫ��
		settextstyle(24, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
		setbkmode(TRANSPARENT);
		switch (id)
		{
		case PlayerID::P1:
			settextcolor(RED);
			_stprintf_s(text, L"Ѫ��:%d", hp);
			outtextxy(80, 600, text);
			settextcolor(BLUE);
			_stprintf_s(text, L"����:%d", mp);
			outtextxy(80, 650, text);
			break;
		case PlayerID::P2:
			settextcolor(RED);
			_stprintf_s(text, L"Ѫ��:%d", hp);
			outtextxy(1000, 600, text);
			settextcolor(BLUE);
			_stprintf_s(text, L"����:%d", mp);
			outtextxy(1000, 650, text);
			break;
		}

	}

	virtual void on_input(const ExMessage &msg) {
		//�жϰ������ɿ�
		bool isDown = 0;
		switch (msg.message)
		{
		case WM_KEYDOWN:
			isDown = 1;
			break;
		case WM_KEYUP:
			isDown = 0;
			break;
		}

		//���ݰ�����id��ֵ
		switch (id)
		{
		case PlayerID::P1:
			switch (msg.vkcode)
			{
			case 65://A
				is_left_key_down = isDown;
				break;
			case 68://D
				is_right_key_down= isDown;
				break;
			case 0x57://W
				if (isDown)
				{
					jump();
				}
				break;
			case 0x46://F��ͨ����
				if (can_attck) {
					on_attack();
					can_attck=0;
					timer_attack.restart();
				}
				break;
			case 0x47://G�����⹥��
				if (mp >= 100) {
					on_attack_ex();
					mp =0;
				}
				break;
			case VK_SHIFT://shift��
				if (msg.message == WM_KEYUP && !exam_suc) {
					shift_down = 0;
				}
				else if (msg.message == WM_KEYDOWN) {
					shift_down = 1;
				}

				break;
			default:
				break;
			}
			break;
		case PlayerID::P2:
			switch (msg.vkcode)
			{
			case VK_LEFT://<-
				is_left_key_down = isDown;
				break;
			case VK_RIGHT://->
				is_right_key_down = isDown;
				break;
			case VK_UP:
				if (isDown)
				{
					jump();
				}
				break;
			case VK_OEM_PERIOD://.��ͨ����
				if (can_attck) {
					on_attack();
					can_attck = 0;
					timer_attack.restart();
				}
				break;
			case VK_OEM_2:// ?�����⹥��
				if (mp >= 100) {
					on_attack_ex();
					mp = 0;
				}
				break;
			case VK_CTRL://ctrl��
				if (msg.message == WM_KEYUP && !exam_suc) {
					ctrl_down = 0;
				}
				else if (msg.message == WM_KEYDOWN) {
					ctrl_down = 1;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	
	}

	virtual void run(float dis) {
		if (is_attacking_ex)return;//���⹥�����ƶ�
		//����
		pos.x += dis;
	}
	virtual void move_collide(float delta) {
		velocity.y += G * delta;//�����ٶ��ۼ�
		pos += velocity * (float)delta;
		//ƽ̨������ײ���
		if (velocity.y>0)
		{
			for (const Platform& platform:platform_list)
			{
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (
					max(pos.x + size.x, shape.right) - min(pos.x, shape.left)//ˮƽ��ײ���
					<= size.x + (shape.right - shape.left)
					);
				bool is_collide_y = (shape.y >= pos.y && shape.y<pos.y + size.y);//��ֱ��ײ���
				
				if (is_collide_x&& is_collide_y)
				{ 
					float delta_pos_y = velocity.y * delta;
					float last_foot_pos_y = pos.y + size.y - delta_pos_y;//��һ֡�Ų��߶�
					if (last_foot_pos_y<=shape.y)// ��һ֡�Ų���ƽ̨�Ϸ�
					{
						pos.y = shape.y - size.y;//����ɫ�Ų�λ��������ƽ̨��
						velocity.y = 0;//��ˮƽ�ٶ�����
						break;
					}
				}
				
			}
		}
		
	


	}
	virtual void jump() {
		//��Ծ
		if (velocity.y==0.0&&!is_attacking_ex)
		{
			velocity.y += jump_speed;
		}
		
	};

	virtual void on_attack() {//��ͨ����


	};
	virtual void on_attack_ex(//��ɫ����
	) {};

public:
	PlayerID id; //���id
	int identity = 0;//������ 1��ʹ 2��ħ
	Vector2<float> pos;//���λ��
	Vector2<float> size = {96,96};//��Ҵ�С

	bool can_attck = true;//�Ƿ���Թ���
	int attack_cd;//�������
	Timer timer_attack;//������ȴ��ʱ��
	bool is_attacking_ex=0;//�Ƿ��ڽ������⹥��

	int mp = 0;//����
	int hp = 100;//����
	

	//��λ�Ƿ񱻰��� -->�ж��ƶ� 
	bool shift_down = 0;
	bool ctrl_down = 0;
	bool is_left_key_down=0;
	bool is_right_key_down = 0;
	bool is_facing_right = 1;//����
	const float speed=0.5f;//�ܶ��ٶ�
	const float jump_speed = -1.2f;//��Ծ�ٶ�
	const float G = 0.00320f;//�����ٶ�
	
	Vector2<float> velocity;//��ɫʸ���ٶ�
	Atlas begin;
	Atlas recovery;
	Animation* current_animation;//��ǰҪ���ŵĶ���
	Animation animation_idle_left; //��Ҷ���
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;//�������⹥������
	Animation animation_attack_ex_right;
	Animation animation_die;//��������
	Animation animation_begin;//���п�ʼ
	Animation animation_recovery;//�ָ�����
	int exam_time = 0;
	bool exam_suc = 0;
	Timer dieTimer;//��ɫ�����󷵻����˵�����ʱ
};


Player::~Player()
{
}