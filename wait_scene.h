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
class WaitScene :public Scene
{
public:
	WaitScene() = default;
	~WaitScene() = default;

	void on_enter() {
				
		loadimage(&bk, L"resources/wait/bk.png");
		loadimage(&border, L"resources/wait/border.png");
		loadimage(&fighter, L"resources/wait/fighter.png");
		loadimage(&angel, L"resources/wait/angel.jpg");
		loadimage(&daemon, L"resources/wait/daemon.jpg");
		//loadimage(&hand, _T("resources/menu/attack.png"));
		borderPos1 = {20};
		borderPos2 = { 20+300,0 };
		borderPos3 = { 20+600,0 };
		borderPos4 = { 20+900,0 };

		settextstyle(25, 0, _T("IPix"));
		setbkmode(TRANSPARENT);
	}
	void on_update(int delta) {
		

	}
	void on_draw(const Camera& camera) {
		//背景渲染
		putimage(bkPos.x, bkPos.y,& bk);
		putimage(borderPos1.x + borderOffsetX, borderPos1.y + borderOffsetY, &fighter);
		putimage(borderPos2.x + borderOffsetX, borderPos2.y + borderOffsetY, &fighter);
		putimage(borderPos3.x + borderOffsetX, borderPos3.y + borderOffsetY, &angel);
		putimage(borderPos4.x + borderOffsetX, borderPos4.y + borderOffsetY, &daemon);
		puimage_alpha(borderPos1.x, borderPos1.y, &border);
		puimage_alpha(borderPos2.x, borderPos2.y, &border);
		puimage_alpha(borderPos3.x, borderPos3.y, &border);
		puimage_alpha(borderPos4.x, borderPos4.y, &border);
		//puimage_alpha(handPos.x, handPos.y, &hand);
		settextstyle(28, 0, _T("IPix"),0,0,700,0,0,0);
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY, L"      斗士");
		outtextxy(borderPos1.x+textOffsetX, borderPos1.y + textOffsetY+50, L"倾尽全力杀死对方");
		outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY+100, L"亦或是被对方杀死");
		outtextxy(borderPos1.x + textOffsetX, borderPos1.y + textOffsetY+150, L"此外可还有结局吗？");
		settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
		outtextxy(borderPos1.x + textOffsetX+40, borderPos1.y + textOffsetY + 300, L"用户名");

		settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY, L"      斗士");
		outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY + 50, L"倾尽全力杀死对方");
		outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY + 100, L"亦或是被对方杀死");
		outtextxy(borderPos2.x + textOffsetX, borderPos2.y + textOffsetY + 150, L"此外可还有结局吗？");
		settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
		outtextxy(borderPos2.x + textOffsetX + 40, borderPos1.y + textOffsetY + 300, L"用户名");

		setbkmode(TRANSPARENT);
		settextcolor(YELLOW);
		outtextxy(borderPos3.x + textOffsetX+40, borderPos4.y + textOffsetY, L"   天使");
		outtextxy(borderPos3.x + textOffsetX + 40, borderPos4.y + textOffsetY + 50, L"纵起死回生");
		outtextxy(borderPos3.x + textOffsetX + 40, borderPos4.y + textOffsetY + 100, L"亦回天乏术");
		outtextxy(borderPos3.x + textOffsetX + 40, borderPos4.y + textOffsetY + 150, L"生死概天命");
		outtextxy(borderPos3.x + textOffsetX + 40, borderPos4.y + textOffsetY + 200, L"颤颤济苍生");
		settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
		outtextxy(borderPos3.x + textOffsetX + 60, borderPos1.y + textOffsetY + 300, L"用户名");

		settextstyle(28, 0, _T("IPix"), 0, 0, 700, 0, 0, 0);
		setbkmode(TRANSPARENT);
		settextcolor(RED);
		outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY, L"   恶魔");
		outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 50, L"落镰非无情");
		outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 100, L"浴血也有义");
		outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 150, L"生若常戚戚");
		outtextxy(borderPos4.x + textOffsetX + 40, borderPos4.y + textOffsetY + 200, L"何若长已矣");
		settextstyle(26, 0, _T("IPix"), 0, 0, 500, 0, 0, 0);
		outtextxy(borderPos4.x + textOffsetX + 60, borderPos1.y + textOffsetY + 300, L"用户名");
		
	
	}
	void on_input(const ExMessage& msg) {

	
	};
	void on_exit() {
	}

private:
	IMAGE bk, hand,border;//当前背景图 指针图,边框
	IMAGE angel, daemon, fighter;//身份图
	POINT bkPos = { 0,0 }, titlePos;
	Atlas bkAtlas, itleAtlas;

	POINT borderPos1 = { 0 }, borderPos2 = { 0 }, borderPos3 = { 0 }, borderPos4 = { 0 };
	int borderOffsetX = 65, borderOffsetY=75;
	int textOffsetX=40, textOffsetY=300;//文本偏移量

	
};