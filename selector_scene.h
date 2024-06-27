#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "archi_player.h"
#include "computer_player.h"
#include "math_player.h"
#include "eam_player.h"
extern SceneManager* scene_manager; //场景管理器
extern Player* player_1P;//1p对象
extern Player* player_2P;//2p对象
//引用资源
extern IMAGE img_VS;//vs艺术字图片
extern IMAGE img_1P;//1p文本图
extern IMAGE img_2P;//2p文本图
extern IMAGE img_3P;//3p文本图
extern IMAGE img_4P;

extern IMAGE img_1P_desc;//1p键位描述图
extern IMAGE img_2P_desc;//2p键位描述图
extern IMAGE img_gravestone_left;//朝向左的框架图
extern IMAGE img_gravestone_right;//朝右
extern IMAGE img_gravestone_3;    //34玩家头像框
extern IMAGE img_gravestone_4;

extern IMAGE img_selector_background;//选角界面背景图
extern IMAGE img_selector_tip;//选角界面提示信息文本图

extern IMAGE img_1P_selector_btn_idle_left;            // 1P 向左选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_idle_right;           // 1P 向右选择按钮默认状态图片
extern IMAGE img_1P_selector_btn_down_left;            // 1P 向左选择按钮按下状态图片
extern IMAGE img_1P_selector_btn_down_right;           // 1P 向右选择按钮按下状态图片

extern IMAGE img_2P_selector_btn_idle_left;            // 2P 向左选择按钮默认状态图片                                                                                
extern IMAGE img_2P_selector_btn_idle_right;           // 2P 向右选择按钮默认状态图片
extern IMAGE img_2P_selector_btn_down_left;            // 2P 向左选择按钮按下状态图片
extern IMAGE img_2P_selector_btn_down_right;           // 2P 向右选择按钮按下状态图片

extern IMAGE img_peashooter_selector_background_left;  // 选角界面朝向左的背景图片
extern IMAGE img_peashooter_selector_background_right; // 选角界面朝向右的背景图片
extern IMAGE img_sunflower_selector_background_left;   // 选角界面朝向左的背景图片
extern IMAGE img_sunflower_selector_background_right;  // 选角界面朝向右的龙背景图片

//建筑学院
extern Atlas atlas_archi_idle_left;               // 理学院朝向左的默认动画图集   
extern Atlas atlas_archi_idle_right;

//计算机角色
extern Atlas atlas_computer_idle_left;               // 向左的默认动画图集
extern Atlas atlas_computer_idle_right;              // 向右的默认动画图集

extern Atlas atlas_player3_idle;                       //34玩家人物还没放上
extern Atlas atlas_player4_idle;
//理学院
extern Atlas atlas_math_idle_left;               // 理学院朝向左的默认动画图集   
extern Atlas atlas_math_idle_right;

//经管
extern Atlas EAM_idle_left;
extern Atlas EAM_idle_right;


//选角场景身份资源
extern Atlas atlas_angel;
extern Atlas atlas_demon;

extern int identity_1p, identity_2p; //1P2P的身份

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;
private:
	enum class PlayerType {
		Computer,
		Math,
		Eam,
		Archi
	};


private:
	void on_enter() {
		//设置初始名字
		_stprintf_s(str_P1_name, L"信息学院-普雷");
		_stprintf_s(str_P2_name, L"信息学院-普雷");


		//为角色动画设置图集和帧间隔
		animation_P1.set_atlas(&atlas_computer_idle_right);
		animation_P2.set_atlas(&atlas_computer_idle_left);
		animation_player3.set_atlas(&atlas_player3_idle);    //
		animation_player4.set_atlas(&atlas_player4_idle);

		animation_P1.set_interval(100);
		animation_P2.set_interval(100);
		animation_player3.set_interval(100);                //
		animation_player4.set_interval(100);

		//设置静态元素位置 爆炸
		static const int OFFSET_X = 50;
		pos_img_VS.x = (getwidth() - img_VS.getwidth()) / 2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2 - 15;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X + 125;
		pos_img_1P.y = 15;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X - 125;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_3P.x = pos_img_1P.x;
		pos_img_3P.y = 300;
		pos_img_4P.x = pos_img_2P.x-20;
		pos_img_4P.y = pos_img_3P.y-10;

		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 120;
		pos_img_2P_desc.x = getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;

		pos_img_1P_gravestone.x = pos_img_1P.x - 30;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() - 25;
		pos_img_2P_gravestone.x = pos_img_2P.x - 30;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_img_3P_gravestone.x = pos_img_1P_gravestone.x;
		pos_img_3P_gravestone.y = pos_img_3P.y + img_3P.getheight() - 25;
		pos_img_4P_gravestone.x = pos_img_2P_gravestone.x;
		pos_img_4P_gravestone.y = pos_img_3P_gravestone.y;

		pos_animation_1P.x = pos_img_1P_gravestone.x + (pos_img_1P_gravestone.x - 96) / 2 - OFFSET_X - 22;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 50;
		pos_animation_2P.x = pos_img_2P_gravestone.x + 50;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_animation_3P.x = pos_animation_1P.x-3;
		pos_animation_3P.y = pos_img_3P_gravestone.y + 50-3;
		pos_animation_4P.x = pos_animation_2P.x-10;
		pos_animation_4P.y = pos_animation_3P.y-2 ;

		pos_img_1P_name.y = pos_animation_1P.y + 135;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight()) / 2;
		pos_1P_selector_btn_right.x = pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;

		//身份
		switch (identity_1p)
		{
		case 1:
			animation_player3.set_atlas(&atlas_angel);
			break;
		case 2:
			animation_player3.set_atlas(&atlas_demon);
			break;
		}
		//身份
		switch (identity_2p)
		{
		case 1:
			animation_player4.set_atlas(&atlas_angel);
			break;
		case 2:
			animation_player4.set_atlas(&atlas_demon);
			break;
		}
	

	}
	void on_update(int delta) {
		//角色动画更新
		animation_P1.on_update(delta);
		animation_P2.on_update(delta);
		animation_player3.on_update(delta);
		animation_player4.on_update(delta);

		scorll_line_x += 5; //基准线更新
		if (scorll_line_x >= img_peashooter_selector_background_left.getwidth()) scorll_line_x = 0;

	}
	void on_draw(const Camera& camera) {

		putimage(0, 0, &img_selector_background);      ////
		//渲染背景动态图

		IMAGE* p1_scorll_bk = nullptr;
		IMAGE* p2_scorll_bk = nullptr;

		
		p1_scorll_bk = &img_peashooter_selector_background_right;
		p2_scorll_bk = &img_sunflower_selector_background_left;
		
		puimage_alpha(scorll_line_x - p1_scorll_bk->getwidth(), 0, p1_scorll_bk);
		puimage_alpha(scorll_line_x, 0,
			p1_scorll_bk->getwidth() - scorll_line_x, 0,
			p1_scorll_bk, 0, 0);

		puimage_alpha(getwidth() - p2_scorll_bk->getwidth(), 0, p2_scorll_bk->getwidth() - scorll_line_x, 0,
			p2_scorll_bk, scorll_line_x, 0);

		puimage_alpha(getwidth() - scorll_line_x, 0, p2_scorll_bk);

		//渲染静态素材

		puimage_alpha(pos_img_VS.x, pos_img_VS.y, &img_VS);

		puimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		puimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);
		puimage_alpha(pos_img_3P.x, pos_img_3P.y, &img_3P);
		puimage_alpha(pos_img_4P.x, pos_img_4P.y, &img_4P);

		puimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		puimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

		//pos_animation_3P
		animation_player3.on_draw(pos_animation_3P.x, pos_animation_3P.y);
		animation_player4.on_draw(pos_animation_4P.x, pos_animation_4P.y);
		puimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		puimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);
		puimage_alpha(pos_img_3P_gravestone.x, pos_img_3P_gravestone.y, &img_gravestone_3);
		puimage_alpha(pos_img_4P_gravestone.x, pos_img_4P_gravestone.y, &img_gravestone_4);

		puimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);



		//渲染1p 2p角色动画
		animation_P1.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);
		animation_P2.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);
		
	   //渲染角色1p 2p名字
		pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_P1_name)) / 2;
		outtexy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_P1_name);
		
		pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_P2_name)) / 2;
		outtexy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_P2_name);
		

		
	}
	void on_input(const ExMessage& msg) {            //加上派生的新角色类后修改
		//角色选取 场景跳转
		if (msg.message != WM_KEYUP) return;

		switch (msg.vkcode)
		{
		case 39://->
			//选定角色类型
			if ((int)player_type_2== Num)player_type_2 = (PlayerType)0;//此处的2代表已经有3个角色
			else
			{
				player_type_2 = PlayerType(((int)player_type_2 + 1));
			}
			
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//为选定的角色设定动画和名字
			switch (player_type_2)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P2_name, L"信息学院-普雷");
				animation_P2.set_atlas(&atlas_computer_run_left);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P2_name, L"理学院-珺珂");
				animation_P2.set_atlas(&atlas_math_idle_left);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P2_name, L"经管学院-思丽普");
				animation_P2.set_atlas(&EAM_idle_left);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P2_name, L"建筑学院-伊特");
				animation_P2.set_atlas(&atlas_archi_idle_left);
				break;
			}

			break;

		case 37://<-
			//选定角色类型
			if ((int)player_type_2 ==0 )player_type_2 = (PlayerType)Num;//此处的2代表已经有3个角色
			else
			{
				player_type_2 = PlayerType(((int)player_type_2 -1));
			}
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//为选定的角色设定动画
			//为选定的角色设定动画和名字
			switch (player_type_2)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P2_name, L"信息学院-普雷");
				animation_P2.set_atlas(&atlas_computer_run_left);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P2_name, L"理学院-珺珂");
				animation_P2.set_atlas(&atlas_math_idle_left);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P2_name, L"经管学院-思丽普");
				animation_P2.set_atlas(&EAM_idle_left);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P2_name, L"建筑学院-伊特");
				animation_P2.set_atlas(&atlas_archi_idle_left);
				break;

			}

			break;
		case 68://D
			//选定角色类型
			if ((int)player_type_1 == Num)player_type_1= (PlayerType)0;//此处的2代表已经有3个角色
			else
			{
				player_type_1 = PlayerType(((int)player_type_1 + 1));
			}

			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//为选定的角色设定动画和名字
			switch (player_type_1)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P1_name, L"信息学院-普雷");
				animation_P1.set_atlas(&atlas_computer_run_right);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P1_name, L"理学院-珺珂");
				animation_P1.set_atlas(&atlas_math_idle_right);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P1_name, L"经管学院-思丽普");
				animation_P1.set_atlas(&EAM_idle_right);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P1_name, L"建筑学院-伊特");
				animation_P1.set_atlas(&atlas_archi_idle_right);
				break;
			}


			break;

		case 65://A
			//选定角色类型
			if ((int)player_type_1 == 0)player_type_1 = (PlayerType)Num;//此处的2代表已经有3个角色
			else
			{
				player_type_1 = PlayerType(((int)player_type_1 - 1));
			}

			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			//为选定的角色设定动画和名字
			switch (player_type_1)
			{
			case SelectorScene::PlayerType::Computer:
				_stprintf_s(str_P1_name, L"信息学院-普雷");
				animation_P1.set_atlas(&atlas_computer_run_right);
				break;
			case SelectorScene::PlayerType::Math:
				_stprintf_s(str_P1_name, L"理学院-珺珂");
				animation_P1.set_atlas(&atlas_math_idle_right);
				break;
			case SelectorScene::PlayerType::Eam:
				_stprintf_s(str_P1_name, L"经管学院-思丽普");
				animation_P1.set_atlas(&EAM_idle_right);
				break;
			case SelectorScene::PlayerType::Archi:
				_stprintf_s(str_P1_name, L"建筑学院-伊特");
				animation_P1.set_atlas(&atlas_archi_idle_right);
				break;
			}


			break;
		case 13://回车
			mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			scene_manager->switch_to(SceneManager::SceneType::Game);

		}

	


	};
	void exit() {
		//根据选角类型赋值玩家对象
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Computer:
			player_1P = new ComputerPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Math:
			player_1P = new MathPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Eam:
			player_1P = new EAMPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Archi:
			player_1P = new ArchiPlayer();
			player_1P->id = PlayerID::P1;
			break;

		}
		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Computer:
			player_2P = new ComputerPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Math:
			player_2P = new MathPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Eam:
			player_2P = new EAMPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Archi:
			player_2P = new ArchiPlayer();
			player_2P->id = PlayerID::P2;
			break;
		}

		//设置身份标识 用于选角场景的切换
		player_1P->setIdentity(identity_1p);
		player_2P->setIdentity(identity_1p);

		
	}

private:
	POINT pos_img_VS = { 0 };// Vs 艺术字图片位置
	POINT pos_img_tip = { 0 };// 提示信息文本图片位置
	POINT pos_img_1P = { 0 };// 1P 文本图片位置
	POINT pos_img_2P = { 0 };// 2P文本图片位置
	POINT pos_img_3P = { 0 };// 3P文本图片位置
	POINT pos_img_4P = { 0 };

	POINT pos_img_1P_desc = { 0 };//1P键位描述图片位置
	POINT pos_img_2P_desc = { 0 };// 2P键位描述图片位置
	POINT pos_img_1P_name = { 0 };//1P角色姓名文本位置
	POINT pos_img_2P_name = { 0 };//2P角色姓名文本位置
	POINT pos_animation_1P = { 0 };//1P角色动画位置
	POINT pos_animation_2P = { 0 };// 2P角色动画位置
	POINT pos_animation_3P = { 0 };
	POINT pos_animation_4P = { 0 };

	POINT pos_img_1P_gravestone = { 0 };// 1P墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };//2P墓碑图片位置
	POINT pos_img_3P_gravestone = { 0 };
	POINT pos_img_4P_gravestone = { 0 };

	POINT pos_1P_selector_btn_left = { 0 };//1P向左切换按钮位置
	POINT pos_1P_selector_btn_right = { 0 };// 1P向右切换按钮位置
	POINT pos_2P_selector_btn_left = { 0 };//2P向左切换按钮位置
	POINT pos_2P_selector_btn_right = { 0 };//2P 向右切换按钮位置

	Animation animation_P1; //1p动画
	Animation animation_P2;//2p动画
	Animation animation_player3;
	Animation animation_player4;


	PlayerType player_type_1 = PlayerType::Computer;//1p 2p角色类型 
	PlayerType player_type_2 = PlayerType::Computer;

	TCHAR str_P1_name[256] ;      //这里先用初始名字代替 人物补全后改
	TCHAR str_P2_name[256];

	int scorll_line_x = 0; //背景板滚动线
	int Num=3;//角色数量-1


private:
	void outtexy_shaded(int x, int y, LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};