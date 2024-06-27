#pragma once
#include "vector2.h"
#include <graphics.h>
#include <functional>
#include "player_id.h"
#include "camera.h"
#include "player.h"


class Bullet
{
public:
	Bullet() { TotalCount++; };
	~Bullet() { TotalCount--; };

	void set_callback(std::function<void()> callback) {
		//设置回调函数
		this->callback = callback;
	}
	virtual void on_collide() {
	
		//碰撞执行回调
		if (callback)callback();
	}

	virtual bool check_collision(const Vector2<float>& pos, const Vector2<float>& size) {
		//子弹中心点与人物矩形碰撞检测
		return this->pos.x + this->size.x / 2 >= pos.x 
			&& this->pos.x + this->size.x / 2 <= pos.x + size.x
			&& this->pos.y + this->size.y / 2 >= pos.y
			&& this->pos.y + this->size.y <= pos.y + size.y
			&&valid;

	}		
	virtual void on_update(int delta) {
		
	}
	virtual void on_draw(const Camera& camera) const{

	}
	virtual bool check_exceed_screen() {
		//检测子弹超出窗口
		return (pos.x + size.x <= 0 || pos.x >= getwidth()) || (pos.y >= getheight() || pos.y + size.y <= 0);

	}
public:
	friend int getBulletCount();

public:
	PlayerID target_id;//子弹要碰撞的目标id
	Vector2<float> size;//尺寸
	Vector2<float> pos;//子弹位置
	Vector2<float> velcity;//子弹速度
	int damage;//子弹威力
	bool valid = true;//子弹有效
	bool can_remove = false;//可以移除
	std::function<void()> callback;//子弹碰撞后回调函数
private:
	static int TotalCount;//子弹总数
};


int getBulletCount(){
	return Bullet::TotalCount;//返回子弹数量
};//友元
