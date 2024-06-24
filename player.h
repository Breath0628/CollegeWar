#pragma once
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
		
	};
	~Player();
	
	virtual void on_update(int delta) {
		if (hp<=0)
		{
			die();
		}
		dieTimer.on_update(delta);
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
			//静止
			current_animation = is_facing_right ? &animation_idle_right : &animation_idle_left;
		}
		timer_attack.on_update(delta);
		move_collide(delta);
		current_animation->on_update(delta);
		
	}
	virtual void on_draw(const Camera& camera) 
	{
		current_animation->on_draw(camera,(int)(pos.x), (int)(pos.y));//渲染当前动画
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
	virtual void die(){
	//	current_animation = &animation_die;//切换为死亡动画
		//死亡后返回主菜单定时器
		dieTimer.set_callback([&]() {
			scene_manager->switch_to(SceneManager::SceneType::Menu);
			});
		dieTimer.set_one_shot(1);
		dieTimer.set_wait_time(1000);

	}//死亡

public:
	PlayerID id; //玩家id
	Vector2<float> pos;//玩家位置
	Vector2<float> size = {96,96};//玩家大小

	bool can_attck = true;//是否可以攻击
	int attack_cd;//攻击间隔
	Timer timer_attack;//攻击冷却计时器
	bool is_attacking_ex=0;//是否在进行特殊攻击

	int mp = 0;//蓝条
	int hp = 100;//红条

	//键位是否被按下 -->判断移动 
	bool is_left_key_down=0;
	bool is_right_key_down = 0;
	bool is_facing_right = 1;//面向
	const float speed=0.5f;//跑动速度
	const float jump_speed = -1.2f;//跳跃速度
	const float G = 0.00320f;//重力速度
	Vector2<float> velocity;//角色矢量速度

	Animation* current_animation;//当前要播放的动画
	Animation animation_idle_left; //玩家动画
	Animation animation_idle_right;
	Animation animation_run_left;
	Animation animation_run_right;
	Animation animation_attack_ex_left;//朝左特殊攻击动画
	Animation animation_attack_ex_right;
	Animation animation_die;//死亡动画
	Timer dieTimer;//角色死亡后返回主菜单倒计时
};


Player::~Player()
{
}