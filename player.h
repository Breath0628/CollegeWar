#pragma once
#define VK_CTRL           0x11   //Ctrl键
#define VK_SHIFT          0x10   //shift键
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

extern std::vector<Bullet*>bullet_list;//子弹对象  
extern std::vector<Platform> platform_list; //平台对象
extern Camera main_camera;


class Player
{
public:
	Player() { 
		current_animation = &animation_idle_right;
		//攻击定时器设置
		timer_attack.set_wait_time(attack_cd);
		timer_attack.set_one_shot(1);
		timer_attack.set_callback([&]() {
			can_attck = 1;
			});

		//返回主菜单倒计时
		dieTimer.set_callback([&]() {
			try {
				char buffer[128];
				char text[128];
				sprintf(text, "P%d失败!",int(id)+1);

				writeStringAndTimeToFile("record.txt", text);
				//std::string readTime = readTimeFromFile("record.txt");
			}
			catch (const std::exception& e) {
				std::cerr << "异常: " << e.what() << std::endl;
			}
			scene_manager->switch_to(SceneManager::SceneType::Menu);
			});
		dieTimer.set_one_shot(1);
		dieTimer.set_wait_time(5000);

		//加载恢复图集资源
		begin.load_from_file(_T("resources/recovery/begin%d.png"), 2);
		recovery.load_from_file(_T("resources/recovery/recovery%d.png"), 3);
		//配置恢复动画
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
	//设置身份
		identity = ident;
		if (identity == 1 && hp != 200) {
			//天使身份
			hp = 200;
		}
		if (identity == 2 && attack_cd != 333) {
			//恶魔身份
			attack_cd = 333;
		}
	}

	virtual void on_update(int delta) {
		if (pos.y>800)//掉出
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
		int direction = is_right_key_down - is_left_key_down;//玩家是否移动
		
		if (direction != 0) {
			//移动
			is_facing_right = direction > 0;
			current_animation = is_facing_right ? &animation_run_right : &animation_run_left;
			float dis = direction *speed * delta;//向右移动距离
			run(dis);
		}
		
		else
		{
			if (hp<=0)
			{
				current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
			}
			else {
				//静止
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
		current_animation->on_draw(camera,(int)(pos.x), (int)(pos.y));//渲染当前动画
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
		//死亡文字播报
		if (hp <= 0)
		{	
			settextstyle(54, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			_stprintf_s(text2, L"P%d死亡，游戏结束！", (int)id + 1);

			outtextxy(450, 300, text2);

		}
		

		TCHAR text[256];
		//显示蓝条和血量
		settextstyle(24, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
		setbkmode(TRANSPARENT);
		switch (id)
		{
		case PlayerID::P1:
			settextcolor(RED);
			_stprintf_s(text, L"血量:%d", hp);
			outtextxy(80, 600, text);
			settextcolor(BLUE);
			_stprintf_s(text, L"蓝量:%d", mp);
			outtextxy(80, 650, text);
			break;
		case PlayerID::P2:
			settextcolor(RED);
			_stprintf_s(text, L"血量:%d", hp);
			outtextxy(1000, 600, text);
			settextcolor(BLUE);
			_stprintf_s(text, L"蓝量:%d", mp);
			outtextxy(1000, 650, text);
			break;
		}

	}

	virtual void on_input(const ExMessage &msg) {
		//判断按下与松开
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

		//根据按键和id赋值
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
			case 0x46://F普通攻击
				if (can_attck) {
					on_attack();
					can_attck=0;
					timer_attack.restart();
				}
				break;
			case 0x47://G键特殊攻击
				if (mp >= 100) {
					on_attack_ex();
					mp =0;
				}
				break;
			case VK_SHIFT://shift键
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
			case VK_OEM_PERIOD://.普通攻击
				if (can_attck) {
					on_attack();
					can_attck = 0;
					timer_attack.restart();
				}
				break;
			case VK_OEM_2:// ?键特殊攻击
				if (mp >= 100) {
					on_attack_ex();
					mp = 0;
				}
				break;
			case VK_CTRL://ctrl键
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
		if (is_attacking_ex)return;//特殊攻击不移动
		//奔跑
		pos.x += dis;
	}
	virtual void move_collide(float delta) {
		velocity.y += G * delta;//重力速度累加
		pos += velocity * (float)delta;
		//平台单向碰撞检测
		if (velocity.y>0)
		{
			for (const Platform& platform:platform_list)
			{
				const Platform::CollisionShape& shape = platform.shape;
				bool is_collide_x = (
					max(pos.x + size.x, shape.right) - min(pos.x, shape.left)//水平碰撞检测
					<= size.x + (shape.right - shape.left)
					);
				bool is_collide_y = (shape.y >= pos.y && shape.y<pos.y + size.y);//竖直碰撞检测
				
				if (is_collide_x&& is_collide_y)
				{ 
					float delta_pos_y = velocity.y * delta;
					float last_foot_pos_y = pos.y + size.y - delta_pos_y;//上一帧脚部高度
					if (last_foot_pos_y<=shape.y)// 上一帧脚部在平台上方
					{
						pos.y = shape.y - size.y;//将角色脚部位置设置在平台处
						velocity.y = 0;//将水平速度置零
						break;
					}
				}
				
			}
		}
		
	


	}
	virtual void jump() {
		//跳跃
		if (velocity.y==0.0&&!is_attacking_ex)
		{
			velocity.y += jump_speed;
		}
		
	};

	virtual void on_attack() {//普通攻击


	};
	virtual void on_attack_ex(//特色攻击
	) {};

public:
	PlayerID id; //玩家id
	int identity = 0;//玩家身份 1天使 2恶魔
	Vector2<float> pos;//玩家位置
	Vector2<float> size = {96,96};//玩家大小

	bool can_attck = true;//是否可以攻击
	int attack_cd;//攻击间隔
	Timer timer_attack;//攻击冷却计时器
	bool is_attacking_ex=0;//是否在进行特殊攻击

	int mp = 0;//蓝条
	int hp = 100;//红条
	

	//键位是否被按下 -->判断移动 
	bool shift_down = 0;
	bool ctrl_down = 0;
	bool is_left_key_down=0;
	bool is_right_key_down = 0;
	bool is_facing_right = 1;//面向
	const float speed=0.5f;//跑动速度
	const float jump_speed = -1.2f;//跳跃速度
	const float G = 0.00320f;//重力速度
	
	Vector2<float> velocity;//角色矢量速度
	Atlas begin;
	Atlas recovery;
	Animation* current_animation;//当前要播放的动画
	Animation animation_idle_left; //玩家动画
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;//朝左特殊攻击动画
	Animation animation_attack_ex_right;
	Animation animation_die;//死亡动画
	Animation animation_begin;//考研开始
	Animation animation_recovery;//恢复动画
	int exam_time = 0;
	bool exam_suc = 0;
	Timer dieTimer;//角色死亡后返回主菜单倒计时
};


Player::~Player()
{
}