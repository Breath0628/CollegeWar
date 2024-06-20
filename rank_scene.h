#pragma once
#include <graphics.h>
#include "scene.h"
#include <iostream>
#include "scene_manager.h"
#include "animation.h"
#include "camera.h"
#include "timer.h"
using namespace std;

extern SceneManager* scene_manager;
extern IMAGE img_menu_background;


class RankScene :public Scene
{
public:
	RankScene() = default;
	~RankScene() = default;

	void on_enter() {
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
		loadimage(&img_math_idle,L"resources/math_idle.png");
		loadimage(&rank_bk, L"resources/Ranking_list.png");
	}
	void on_update(int delta) {
	}
	void on_draw(const Camera& camera) {
		putimage(0, 0, &rank_bk);
		outtextxy(100, 100, _T("ÅÅÐÐ°ñ³¡¾°"));
		puimage_alpha(100, 200, &img_math_idle);
	}
	void on_input(const ExMessage& msg) {

		if (msg.vkcode == 32&&msg.message==WM_KEYUP) {
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager->switch_to(SceneManager::SceneType::Selector);
		}
	};
	void on_exit() {
	}
	
private:
	IMAGE img_math_idle;
	IMAGE rank_bk;
};