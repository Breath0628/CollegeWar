#include <graphics.h>
#include <iostream>
#include "scene.h"

#include "menu_scene.h"
#include "game_scene.h"
#include "selector_scene.h"
#include "rank_scene.h"
#include "scene_manager.h"


#include "player.h"
#include "platform.h"
#include "atlas.h"
#include "utli.h"
#include "def.h"

#include "bullet.h"

Scene* menu_scene = nullptr;
Scene* game_scene = nullptr;
Scene* selector_scene = nullptr;
Scene* rank_scene = nullptr;
SceneManager* scene_manager;
Camera main_camera;
std::vector<Platform> platform_list; //平台对象
bool is_debug=0;//调试模式
Player* player_1P=nullptr;//1p对象
Player* player_2P=nullptr;//2p对象
std::vector<Bullet*>bullet_list;//子弹对象 

int main() {
	ExMessage msg;
	const int FPS = 60;
	load_game_resources();
	initgraph(1280, 720);
	
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_scene = new GameScene();
	selector_scene = new SelectorScene();
	rank_scene = new RankScene();


	scene_manager = new SceneManager();

	scene_manager->set_current_scene(menu_scene);


	while (true)
	{
		DWORD frame_start_time = GetTickCount();

 		while (peekmessage(&msg, EX_KEY))
		{ 
			scene_manager->on_input(msg);
		}

		//每帧逻辑更新时间
		static DWORD last_tick_time = GetTickCount();
		DWORD current_tick_time = GetTickCount();

		DWORD delta_tick = current_tick_time - last_tick_time;


		if (delta_tick>17)
		{
			delta_tick = 16;//超过30毫秒按30毫秒计算
		}

		scene_manager->on_update(delta_tick); 
		last_tick_time=current_tick_time;

		cleardevice();

		scene_manager->on_draw(main_camera);
		FlushBatchDraw();

		DWORD frame_end_time = GetTickCount();
		DWORD frame_delta_time = frame_end_time - frame_start_time;
		if (frame_delta_time < 1000 / FPS) {
			Sleep(1000/FPS-frame_delta_time);
		}
	}
	EndBatchDraw();
	return 0;

}