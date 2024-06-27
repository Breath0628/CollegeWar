#pragma once
#include <Mmsystem.h>
#include "scene.h"
#include <iostream>
#include "scene_manager.h"
#include "animation.h"
#include "camera.h"
#include "timer.h"
#include "Identity.h"
using namespace std;


extern Atlas atla_com_repo;
extern Atlas atla_eam_repo;
extern Atlas atla_math_repo;
extern Atlas atla_arch_repo;
class ReposScene :public Scene
{
public:
	ReposScene() = default;
	~ReposScene() = default;

	void on_enter() {
		settextstyle(30, 0, _T("IPix"));
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		//资源载入
		loadimage(&bk, L"resources/repos/bk.png");
		loadimage(&hand, L"resources/repos/hand.png");
		loadimage(&computerRoleImg, L"resources/repos/computer2.png");
		loadimage(&border, L"resources/repos/showBorder2.png");
		nowRolePos = { 30,10 };

		for (size_t i = 0; i < 4; i++)
		{
			aniList[i].set_interval(500);
			
		}
		//动画载入
		aniList[0].set_atlas(&atla_com_repo);
		aniList[1].set_atlas(&atla_math_repo);
		aniList[2].set_atlas(&atla_arch_repo);
		aniList[3].set_atlas(&atla_eam_repo);

	}
	void on_update(int delta) {
	//更新相机位置
		cam.x += (right_down - left_down)  * delta*0.5;
	//动画更新
		for (size_t i = 0; i < 4; i++)
		{
			aniList[i].on_update(delta);
		}
		
	}
	void on_draw(const Camera& camera) {
		//静态资源渲染
		putimage(0, 0, &bk);
		
		for (size_t i = 0; i < num; i++)
		{
			settextstyle(30, 0, _T("IPix"));
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			puimage_alpha(nowRolePos.x+480*i- cam.x, nowRolePos.y, &border);//角色框架

			aniList[i].on_draw(nowRolePos.x +50+ 480 * i + offset.x - cam.x, nowRolePos.y +50+ offset.y);
			//puimage_alpha(nowRolePos.x + 480 * i+offset.x- cam.x, nowRolePos.y+offset.y, &computerRoleImg);//角色头像
			outtextxy(nowRolePos.x + 480 * i +110- cam.x, nowRolePos.y + offset.y + 290,nameList[i]);//名字
			settextstyle(25, 0, _T("IPix"));


			for (size_t j = 0; j < 8; j++)
			{
				outtextxy(nowRolePos.x + 480 * i + 40 - cam.x, nowRolePos.y + offset.y + 350+j*40, textList[i][j]);//介绍
			}
		

		}

	}
	void on_input(const ExMessage& msg) {
		
		switch (msg.vkcode)
		{
		case VK_RIGHT://->
			if (msg.message==WM_KEYDOWN)right_down = 1;
			if (msg.message == WM_KEYUP)right_down = 0;
			break;
		case VK_LEFT://<-
			if (msg.message == WM_KEYDOWN)left_down = 1;
			if (msg.message == WM_KEYUP)left_down = 0;
			break;
		case 32:
			if(msg.message==WM_KEYUP)scene_manager->switch_to(SceneManager::SceneType::Menu);
		}

	};
	               
	void exit() {
	}

private:
	IMAGE bk,hand,border,showBorder;//背景 指针 头像框
	IMAGE* nowRole;//在右侧展示的角色
	IMAGE computerRoleImg;//角色头像
	int num = 4;//角色数量
	Vector2<int> nowRolePos;//右侧角色动态图展示的位置
	Vector2<int> offset = {70,-15};//角色头像偏移量
	Animation* nowRoleAnimation;//当前展示的角色动画
	Vector2<int> nowTextPos;//右侧角色介绍文本的位置
	RECT  rectList[4];//介绍文本的矩形位置
	TCHAR textList[4][8][256] = {
		{
			_T("普雷已经忘记了自己是如何卷入这"),
			_T("场战争的,他只是个破敲代码的,并"),
			_T("且平心而论敲的也不怎么样。战争"),
			_T("伊始,他只是带着电脑抱头鼠窜,直"),
			_T("到有一天他发现自己的代码居然可"),
			_T("以发射出去。知识就是力量,我现在"),
			_T("认识到了,他说。")
			
		},
		{
			_T("珺珂总是带着一副厚重的黑框眼镜,"),
			_T("手里拿着一本《数学分析方法》头"),
			_T("上只有三根头发，面带“和善”的"),
			_T("微笑。当然啦，如果有人坚持问他"),
			_T("头发为什么只有三根,他会从物理"),
			_T("层面劝人“积德”")

		},
		{

		    _T("这是建筑学院的小小艺术家伊特,画"),
			_T("笔和调色盘是他最好的朋友，看他"),
			_T("的头发和胡子那么飘逸有诗意,你就"),
			_T("该知道他的艺术功底绝对很棒。他"),
			_T("是学建筑设计的.是画图的,不是建"),
			_T("房子刷漆的！！如果有人说他是粉"),
			_T("刷匠那他就真的要生气了：吃我一"),
			_T("塔！吃我一桥！吃我一楼！")

		},
		{
			

		    _T("思丽普，一个来自阿拉伯的富婆。每"),
			_T("天,她都会展示自己的钻戒，让周围"),
			_T("的人为之羡慕。但是她深知单靠金钱"),
			_T("带来的日子是多么无趣。在她的生活"),
			_T(",一切问题都可以通过金钱解决，这"),
			_T("让她意识到，财富并非唯一的幸福源"),
			_T("泉。她常常在奢华与内心真实之间摇"),
			_T("摆，试图寻找生活的真谛。"),
		}

	
	};
	//角色名字列表
	TCHAR nameList[4][256] = {
			_T("信息学院-普雷"),
			_T("理学院-珺珂"),
			_T("经管学院-伊特"),
			_T("经管学院-思丽普")

	};
	Vector2<int> cam = {0,0};//摄像机
	bool right_down=0,left_down=0;
	

	Animation aniList[4];//动画列表 静止攻击和运动
	Animation* nowAni[4];//播放的动画指针
};