#pragma once
#include "sun_bullet.h"
#include "animation.h"
#include "camera.h"

extern Camera main_camera;
extern Atlas atlas_sun_ex;
extern Atlas atlas_sun_ex_explode;

class SunBulletEX:public Bullet
{
public:
	SunBulletEX() {
		size = { 288 ,288 };
		damage = 20;
		//配置动画
		animation_idle.set_atlas(&atlas_sun_ex);
		animation_idle.set_interval(50);

		animation_explode.set_atlas(&atlas_sun_ex_explode);
		animation_explode.set_interval(50);
		animation_explode.set_loop(0);
		animation_explode.set_callback([&]() {can_remove = 1;});

		//对齐动画帧图偏移量
		IMAGE* frame_idle = animation_idle.get_frame();
		IMAGE* frame_explode = animation_explode.get_frame();
		explode_render_offset = { (int)((frame_idle->getwidth() - frame_explode->getwidth()) / 2),
									(int)((frame_idle->getheight() - frame_explode->getheight()) / 2)
		};
	};
	~SunBulletEX();

	void on_collide() {
		Bullet::on_collide();
		main_camera.shake(20, 350);//摄像机抖动
		//太阳花爆炸音效
		mciSendString(_T("play sun_explode_ex from 0"), NULL, 0, NULL);
	}

	bool check_collision(const Vector2<float>& pos, const Vector2<float>& size) {
		//子弹矩形与人物矩形碰撞检测
		return (max(this->pos.x + this->size.x, pos.x + size.x) - min(this->pos.x, pos.x) <= this->size.x + size.x)
			&& (max(this->pos.y + this->size.y, pos.y + size.y) - min(this->pos.y, pos.y) <= this->size.y + size.y);

	}
	void on_update(int delta) {
		if (valid)//有效则移动
		{
			pos += velcity * (float)delta;

		}

		if (!valid) animation_explode.on_update(delta);//无效子弹更新破碎动画
		else
		{
			animation_idle.on_update(delta);
		}
		if (check_exceed_screen())can_remove = 1;

	}
	void on_draw(const Camera& camera) const {
		//根据子弹状态设置渲染
		if (valid) {
			animation_idle.on_draw(camera, int(pos.x), int(pos.y));
		}
		else
		{
			animation_explode.on_draw(camera, (int)(pos.x + explode_render_offset.x),
				(int)(pos.y + explode_render_offset.y));
		}
	}
private:
	Animation animation_idle;//日光子弹默认闪烁动画
	Animation animation_explode;//日光子弹爆炸动画
	Vector2<int> explode_render_offset;//爆炸动画渲染偏移
	const float G = 0.003f;
};

