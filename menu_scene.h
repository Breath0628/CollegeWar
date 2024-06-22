#pragma once
#include <Mmsystem.h>
#include "scene.h"
#include <iostream>
#include "scene_manager.h"
#include "animation.h"
#include "camera.h"
#include "timer.h"
using namespace std;

extern SceneManager* scene_manager;
extern bool Running;
class MenuScene:public Scene
{
public:
	MenuScene() =default;
	~MenuScene() =default;

	void on_enter() {
		//背景更新定时器
		itleAtlas.load_from_file(L"resources/menu/title%d.png", 1);
		titleImg=itleAtlas.get_image(0);
		ChangeBkTimer.set_wait_time(5000);
		ChangeBkTimer.set_callback([&]() {
			bk1 = bkAtlas.get_image(rand() % 5);
			});
		bkAtlas.load_from_file(L"resources/menu/bk%d.jpg", 5);
		bk1 = bkAtlas.get_image(rand() % 5);
		
		titlePos = {getwidth()/2 - titleImg->getwidth() / 2,0 };
		textHead = { getwidth() / 2-150,titleImg->getheight()};
		mciSendString(_T("play bgm_menu repeat from 0"),NULL,0,NULL);
		settextstyle(60, 0, _T("IPix"));
		setbkmode(TRANSPARENT);
		loadimage(&hand, _T("resources/menu/attack.png"));
		handPos = { textHead.x-hand.getwidth()+5, textHead.y-10};
		
		loadimage(&hand3, L"resources/menu/hand2.png");
		flip_image(&hand3, &hand2);

	}
	void on_update(int delta){
		//背景移动
		ChangeBkTimer.on_update(delta);
		bkPos.x -= toRight*1;
		bkPos.y -= toDown*1;
		if (getwidth() >= bk1->getwidth() + bkPos.x||bkPos.x>=0)toRight = -1 * toRight;
		if (getheight() >= bk1->getheight() + bkPos.y||bkPos.y>=0)toDown = -1 * toDown;
	
	}
	void on_draw(const Camera& camera){
		//背景渲染
		putimage(bkPos.x, bkPos.y, bk1);
		puimage_alpha(titlePos.x, titlePos.y, titleImg);
		outtextxy(textHead.x, textHead.y, L"加入房间");
		outtextxy(textHead.x, textHead.y+90, L"创建房间");
		outtextxy(textHead.x, textHead.y+180, L"角色仓库");
		outtextxy(textHead.x, textHead.y+270, L"荣誉榜单");
		outtextxy(textHead.x, textHead.y+360, L"退出游戏");
		puimage_alpha(handPos.x, handPos.y ,&hand);
		puimage_alpha(handPos.x+330, handPos.y-10, &hand2);
	}
	void on_input(const ExMessage &msg) {

		switch (msg.vkcode)
		{
		case VK_UP:
			if (handPos.y > textHead.y -10&& msg.message == WM_KEYUP)
			{
				handPos.y -= 90;
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			}
			break;
		case VK_DOWN://.普通攻击
			if (handPos.y < textHead.y - 10 + 360&& msg.message == WM_KEYUP)
			{
				handPos.y += 90;
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			}
			break;

		case 32:
			if(msg.message == WM_KEYUP)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);

				if (handPos.y <= textHead.y - 10)scene_manager->switch_to(SceneManager::SceneType::Rank);
				else if (handPos.y <= textHead.y - 10 + 90)scene_manager->switch_to(SceneManager::SceneType::WAIT);
				else if (handPos.y <= textHead.y - 10 + 180)scene_manager->switch_to(SceneManager::SceneType::Rank);
				else if (handPos.y <= textHead.y - 10 + 270)scene_manager->switch_to(SceneManager::SceneType::Rank);
				else if (handPos.y <= textHead.y - 10 + 360)Running = 0;
				
			}
		}
	};
	void on_exit(){
	}

private:
	IMAGE* bk1,*titleImg,hand, hand2,hand3;//当前背景图

	POINT bkPos = { 0,0 },titlePos;
	Atlas bkAtlas, itleAtlas;
	
	POINT textHead = { 0 },handPos = {0};
	int toRight=1;
	int toDown = 1;
	Timer ChangeBkTimer;
};