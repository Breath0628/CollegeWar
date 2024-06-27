#pragma once
#include "timer.h"
#include "camera.h"
#include "animation.h"

extern bool is_debug;
class Platform
{
public:

	struct CollisionShape
	{
		float y, left, right;
	};

	Platform() = default;
	~Platform() = default;
public:
	CollisionShape shape;//碰撞形状
	IMAGE* img = nullptr; //平台图
	POINT render_pos = { 0 };//渲染位置


	// 更新平台位置的函数
	void move(int a, int b)
	{
		render_pos.x += speed * toRight;
		shape.left += speed * toRight;
		shape.right += speed * toRight;
		if (shape.left <= a || shape.right >= b) {
			toRight = -toRight;
		}
	}


	void on_draw(const Camera& camera)const
	{
		puimage_alpha(camera, render_pos, img);

		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));
			line(camera, (int)shape.left, (int)shape.y, (int)shape.right, (int)shape.y);
		}
	}

public:
	int toRight = 1;
	float speed = 3;
};