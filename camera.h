#pragma once
#include "vector2.h"
#include "timer.h"

class  Camera
{
public:
	Camera() {
		timer_shake.set_one_shot(1);
		timer_shake.set_callback(
			[&]() {
				is_shaking = 0;
				reset();
			}
		);
	};
	~ Camera() = default;

	const Vector2<float>& getPos() const{
		return position;
	}

	void reset() {
		position.x = 0;
		position.y = 0;
	}

	void on_update(int delta) {
		//const Vector2 <float> speed = { -0.35f, 0 };
		//position += speed * float(delta);  
		timer_shake.on_update(delta);
		if (is_shaking) {
			position.x = (-50 + rand() % 100) / 50.0f * shaking_strength;
			position.y = (-50 + rand() % 100) / 50.0f * shaking_strength;
		}
	}

	void shake(float strength,int duration) //摄像机抖动
	{
		is_shaking = 1;
		shaking_strength = strength;

		timer_shake.set_wait_time(duration);//设置结束抖动定时器
		timer_shake.restart();
	}

private:
	Vector2<float> position;//摄像机位置

	Timer timer_shake;//抖动计时器
	bool is_shaking = 0;//摄像机是否正在抖动
	float shaking_strength = 0;//抖动幅度

};
