#pragma once
#include <graphics.h>
#include "scene.h"
#include <iostream>
#include "scene_manager.h"
#include "animation.h"
#include "camera.h"
#include "timer.h"
#include "algorithm"
using namespace std;

extern SceneManager* scene_manager;
extern IMAGE img_menu_background;


struct Location {
	int x;
	int y;
};
const Location lo[5] = {
	{252,355},
	{850,355},
	{252,479},
	{850,479},
	{484,604}
};//输出用户名的位置参数
struct User {
	TCHAR id[8];
	int Score;
};
vector<User> users;//所有玩家
User nowuser = { _T("visitor"),-1 };//当前登录的玩家
bool cmp(User a, User b) {
	return a.Score > b.Score;
}

class RankScene :public Scene
{
public:
	RankScene() = default;
	~RankScene() = default;

	void on_enter() {
		mciSendString(_T("play bgm_menu repeat from 0"), NULL, 0, NULL);
		loadimage(&rank_bk, L"resources/Rank/rank_background.png");
	}
	void on_update(int delta) {
		sort(users.begin(), users.end(), cmp);
	}
	void on_draw(const Camera& camera) {
		putimage(0, 0, &rank_bk);
		TCHAR score[5];
		if (nowuser.Score != -1)
		{
			outtextxy(lo[4].x, lo[4].y, nowuser.id);
			_stprintf_s(score, _T("%d"), nowuser.Score);
			outtextxy(lo[4].x + 260, lo[4].y, score);
		}
		for (int i = 0;i < users.size() && i < 4;i++)
		{
			outtextxy(lo[i].x, lo[i].y, users[i].id);
			_stprintf_s(score, _T("%d"), users[i].Score);
			outtextxy(lo[i].x + 240, lo[i].y, score);
		}
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