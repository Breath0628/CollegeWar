#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "camera.h"
#include "utli.h"
#include "platform.h"
#include "player.h"
#include "sunflower_player.h"
#include "peashooter_player.h"

extern SceneManager* scene_manager;
extern Player* player_1P ;//1p对象
extern Player* player_2P ;//2p对象
extern Camera main_camera;
extern IMAGE img_sky;                                  // 天空图片
extern IMAGE img_hills;                                // 山脉图片
extern IMAGE img_platform_large;                       //大型平台图片
extern IMAGE img_platform_small;                       //小型平台图片
extern std::vector<Platform> platform_list;
;
class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		//背景图定位
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y= (getheight() - img_sky.getheight()) / 2;

		pos_img_hills.x = (getwidth() - img_hills.getwidth()) / 2;
		pos_img_hills.y = (getheight() - img_hills.getheight()) / 2;

		//对4个平台位置定位
		platform_list.resize(4);
		
		Platform& now_platform = platform_list[0];
		now_platform.img = &img_platform_large;
		now_platform.render_pos = { 122,455 };
		now_platform.shape = {
			(float)now_platform.render_pos.y + 60,//对shape.y赋值
			(float)now_platform.render_pos.x + 30,//left
			(float)now_platform.render_pos.x + img_platform_large.getwidth() - 30//right
		};

		Platform& now_platform1 = platform_list[1];
		now_platform1.img = &img_platform_small;
		now_platform1.render_pos = { 175,360 };
		now_platform1.shape = {
			(float)now_platform1.render_pos.y + img_platform_small.getheight()/2,//对shape.y赋值
			(float)now_platform1.render_pos.x + 40,//left
			(float)now_platform1.render_pos.x + img_platform_small.getwidth() - 40//right
		};

		Platform& now_platform2 = platform_list[2];
		now_platform2.img = &img_platform_small;
		now_platform2.render_pos = { 855,360 };
		now_platform2.shape = {
			(float)now_platform2.render_pos.y + img_platform_small.getheight() / 2,//对shape.y赋值
			(float)now_platform2.render_pos.x + 40,//left
			(float)now_platform2.render_pos.x + img_platform_small.getwidth() - 40//right
		};

		Platform& now_platform3 = platform_list[3];
		now_platform3.img = &img_platform_small;
		now_platform3.render_pos = { 515,225 };
		now_platform3.shape = {
			(float)now_platform3.render_pos.y + img_platform_small.getheight() / 2,//对shape.y赋值
			(float)now_platform3.render_pos.x + 40,//left
			(float)now_platform3.render_pos.x + img_platform_small.getwidth() - 40//right
		};
		//对玩家定位
		player_1P->pos = {200,50};
		player_2P->pos = { 975,50 };
	}
	void on_update(int delta) {
		//玩家更新
		player_1P->on_update(delta);
		player_2P->on_update(delta);
		main_camera.on_update(delta);
		//子弹绘制
		for (Bullet* bullet:bullet_list)
		{
			bullet->on_update(delta);
		}
	}

	void on_draw(const Camera& camera) {
	
		//绘制背景图
		puimage_alpha(camera, pos_img_sky, &img_sky);
		puimage_alpha(camera, pos_img_hills, &img_hills);

		//绘制平台图
		for (const Platform& platform:platform_list)
		{
			platform.on_draw(camera);
		}
		//绘制玩家动画
		player_1P->on_draw(camera);
		player_2P->on_draw(camera);

		for (Bullet* bullet : bullet_list)
		{
			bullet->on_draw(main_camera);
		}

		if (is_debug)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("调试模式,Q键关闭"));

		}
		
	
	}
	void on_input(const ExMessage& msg) {
		//将消息传给玩家消息处理函数
		player_1P->on_input(msg);
		player_2P->on_input(msg);

		switch (msg.message)
		{
		case WM_KEYUP:
			//'q'开启调试
			if (msg.vkcode == 0x51)is_debug = !is_debug;
			break;
		default:
			break;
		}

	};
	void on_exit() {
		
	}

private:
	POINT pos_img_sky = { 0 }; //天空位置
	POINT pos_img_hills = { 0 };//山脉位置

};