#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "camera.h"
#include "utli.h"
#include "platform.h"
#include "player.h"
#include "eam_player.h"

extern SceneManager* scene_manager;
extern Player* player_1P;//1p对象
extern Player* player_2P;//2p对象
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
		//加载图片资源
		CHUAtlas.load_from_file(L"resources/game/CHU%d.png", 3);
		CHU = CHUAtlas.get_image(rand() % 3);
		loadimage(&stone, L"resources/game/stone.png");
		loadimage(&stone2, L"resources/game/stone2.png");

		//背景图定位
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_img_CHU.x = (getwidth() - CHU->getwidth()) / 2;
		pos_img_CHU.y = (getheight() - CHU->getheight()) / 2;

		//背景更新定时器
		ChangeBkTimer.set_wait_time(5000);
		ChangeBkTimer.set_callback([&]() {
			CHU = CHUAtlas.get_image(rand() % 3);
			});

		//对4个平台位置定位
		platform_list.resize(3);

		Platform& now_platform = platform_list[0];
		now_platform.img = &stone;
		now_platform.render_pos = { 0,500 };
		now_platform.shape = {
			(float)now_platform.render_pos.y + 30 ,//对shape.y赋值
			(float)now_platform.render_pos.x,//left
			(float)now_platform.render_pos.x + stone.getwidth()//right
		};

		Platform& now_platform1 = platform_list[1];
		now_platform1.img = &stone2;
		now_platform1.render_pos = { 115,300 };
		now_platform1.shape = {
			(float)now_platform1.render_pos.y + stone2.getheight() / 2 - 20,//对shape.y赋值
			(float)now_platform1.render_pos.x + 40,//left
			(float)now_platform1.render_pos.x + stone2.getwidth() - 40//right
		};

		Platform& now_platform2 = platform_list[2];
		now_platform2.img = &stone2;
		now_platform2.render_pos = { 805,300 };
		now_platform2.shape = {
			(float)now_platform2.render_pos.y + stone2.getheight() / 2 - 20,//对shape.y赋值
			(float)now_platform2.render_pos.x + 40,//left
			(float)now_platform2.render_pos.x + stone2.getwidth() - 40//right
		};

		//对玩家定位
		player_1P->pos = { 200,50 };
		player_2P->pos = { 975,50 };
	}
	void on_update(int delta) {
		//背景图更新
		ChangeBkTimer.on_update(delta);
		//背景图移动
		pos_img_CHU.x -= toRight * 1;
		if (getwidth() >= CHU->getwidth() + pos_img_CHU.x || pos_img_CHU.x >= 0)
			toRight = -1 * toRight;
		//平台更新
		if (move)
		{
			platform_list[1].move(0, 640);
			platform_list[2].move(640, 1280);
		}
		//玩家更新
		player_1P->on_update(delta);
		player_2P->on_update(delta);
		main_camera.on_update(delta);
		//子弹绘制
		for (Bullet* bullet : bullet_list)
		{
			bullet->on_update(delta);
		}
	}

	void on_draw(const Camera& camera) {

		//绘制背景图
		puimage_alpha(camera, pos_img_sky, &img_sky);
		puimage_alpha(camera, pos_img_CHU, CHU);

		//绘制平台图
		for (const Platform& platform : platform_list)
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
		switch (msg.vkcode) {
		case 32:
			if (msg.message == WM_KEYUP) {
				scene_manager->switch_to(SceneManager::SceneType::Menu);
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			}
			break;
		}

	};
	void on_exit() {

	}

private:
	Atlas CHUAtlas;
	IMAGE* CHU;
	IMAGE stone;
	IMAGE stone2;
	POINT pos_img_sky = { 0 }; //天空位置
	POINT pos_img_CHU = { 0 };//CHU位置
	Timer ChangeBkTimer;
	int toRight = 1;
	bool move = 1;

};