#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "animation.h"
#include "peashooter_player.h"
#include "sunflower_player.h"

extern SceneManager* scene_manager; //场景管理器
extern Player* player_1P;//1p对象
extern Player* player_2P;//2p对象
//引用资源
extern IMAGE img_VS;//vs艺术字图片
extern IMAGE img_1P;//1p文本图
extern IMAGE img_2P;//2p文本图
extern IMAGE img_1P_desc;//1p键位描述图
extern IMAGE img_2P_desc;//2p键位描述图
extern IMAGE img_gravestone_left;//朝向左的墓碑图
extern IMAGE img_gravestone_right;//墓碑朝右
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

extern IMAGE img_peashooter_selector_background_left;  // 选角界面朝向左的婉逗射手背景图片
extern IMAGE img_peashooter_selector_background_right; // 选角界面朝向右的婉逗射手背景图片

extern IMAGE img_sunflower_selector_background_left;   // 选角界面朝向左的龙日葵背景图片
extern IMAGE img_sunflower_selector_background_right;  // 选角界面朝向右的龙日葵背景图片

extern Atlas atlas_peashooter_idle_left;               // 婉逗射手朝向左的默认动画图集
extern Atlas atlas_sunflower_idle_right;              
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_sunflower_idle_left; 

class SelectorScene :public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;
private:
	enum class PlayerType {
		Peashooter = 0,
		Sunflower, 
		Invalid
	};


private:
	void on_enter() {
	
		//为角色动画设置图集和帧间隔
	
		animation_peashooter.set_atlas(&atlas_peashooter_idle_right);
		animation_sunflower.set_atlas(&atlas_sunflower_idle_right);

		animation_peashooter.set_interval(100);
		animation_sunflower.set_interval(100);

		//设置静态元素位置 爆炸
		static const int OFFSET_X=50;
		pos_img_VS.x= (getwidth() - img_VS.getwidth())/2;
		pos_img_VS.y = (getheight() - img_VS.getheight()) / 2;
		pos_img_tip.x = (getwidth() - img_selector_tip.getwidth()) / 2;
		pos_img_tip.y = getheight() - 125;
		pos_img_1P.x = (getwidth() / 2 - img_1P.getwidth()) / 2 - OFFSET_X;
		pos_img_1P.y = 35;
		pos_img_2P.x = getwidth() / 2 + (getwidth() / 2 - img_2P.getwidth()) / 2 + OFFSET_X;
		pos_img_2P.y = pos_img_1P.y;
		pos_img_1P_desc.x = (getwidth() / 2 - img_1P_desc.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_desc.y = getheight() - 150;
		pos_img_2P_desc.x= getwidth() / 2 + (getwidth() / 2 - img_2P_desc.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_desc.y = pos_img_1P_desc.y;
		pos_img_1P_gravestone.x = (getwidth() / 2 - img_gravestone_right.getwidth()) / 2 - OFFSET_X;
		pos_img_1P_gravestone.y = pos_img_1P.y + img_1P.getheight() + 35;
		pos_img_2P_gravestone.x = getwidth() / 2 + (getwidth()/ 2 - img_gravestone_left.getwidth()) / 2 + OFFSET_X;
		pos_img_2P_gravestone.y = pos_img_1P_gravestone.y;
		pos_animation_1P.x= (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth())/ 2 - OFFSET_X;
		pos_animation_1P.y = pos_img_1P_gravestone.y + 80;
		pos_animation_2P.x = getwidth() / 2 + (getwidth() / 2 - atlas_peashooter_idle_right.get_image(0)->getwidth()) / 2 + OFFSET_X;
		pos_animation_2P.y = pos_animation_1P.y;
		pos_img_1P_name.y = pos_animation_1P.y + 155;
		pos_img_2P_name.y = pos_img_1P_name.y;
		pos_1P_selector_btn_left.x = pos_img_1P_gravestone.x - img_1P_selector_btn_idle_left.getwidth();
		pos_1P_selector_btn_left.y = pos_img_1P_gravestone.y + (img_gravestone_right.getheight() - img_1P_selector_btn_idle_left.getheight())/ 2;
		pos_1P_selector_btn_right.x= pos_img_1P_gravestone.x + img_gravestone_right.getwidth();
		pos_1P_selector_btn_right.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_left.x = pos_img_2P_gravestone.x - img_2P_selector_btn_idle_left.getwidth();
		pos_2P_selector_btn_left.y = pos_1P_selector_btn_left.y;
		pos_2P_selector_btn_right.x = pos_img_2P_gravestone.x + img_gravestone_left.getwidth();
		pos_2P_selector_btn_right.y = pos_1P_selector_btn_left.y;


		//input_timer.set_one_shot(1);
		//input_timer.set_wait_time(500);
		
	}
	void on_update(int delta) {
		//角色动画更新
		animation_peashooter.on_update(delta);
		animation_sunflower.on_update(delta);

		scorll_line_x += 5;//基准线更新
		if (scorll_line_x >= img_peashooter_selector_background_left.getwidth()) scorll_line_x=0;
			
	}
	void on_draw(const Camera &camera) {
		
		putimage(0, 0, &img_selector_background);
		//渲染背景动态图

		IMAGE* p1_scorll_bk = nullptr;
		IMAGE* p2_scorll_bk = nullptr;

		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter:
			p1_scorll_bk = &img_peashooter_selector_background_right;
			break;
		case SelectorScene::PlayerType::Sunflower:
			p1_scorll_bk = &img_sunflower_selector_background_right;
			break;
		default:
			p1_scorll_bk = &img_peashooter_selector_background_right;
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			p2_scorll_bk = &img_peashooter_selector_background_left;
			break;
		case SelectorScene::PlayerType::Sunflower:
			p2_scorll_bk = &img_sunflower_selector_background_left;
			break;
		default:
			p2_scorll_bk = &img_peashooter_selector_background_left;
			break;
		}

		puimage_alpha(scorll_line_x - p1_scorll_bk->getwidth(), 0, p1_scorll_bk);
		puimage_alpha(scorll_line_x, 0,
			p1_scorll_bk->getwidth() - scorll_line_x, 0,
			p1_scorll_bk, 0, 0);

		puimage_alpha(getwidth() - p2_scorll_bk->getwidth(), 0, p2_scorll_bk->getwidth() - scorll_line_x, 0,
			p2_scorll_bk, scorll_line_x, 0);

		puimage_alpha(getwidth() - scorll_line_x, 0, p2_scorll_bk);

		//渲染静态素材
	
		puimage_alpha(pos_img_VS.x,pos_img_VS.y,&img_VS);

		puimage_alpha(pos_img_1P.x, pos_img_1P.y, &img_1P);
		puimage_alpha(pos_img_2P.x, pos_img_2P.y, &img_2P);

		puimage_alpha(pos_img_1P_desc.x, pos_img_1P_desc.y, &img_1P_desc);
		puimage_alpha(pos_img_2P_desc.x, pos_img_2P_desc.y, &img_2P_desc);

		puimage_alpha(pos_img_1P_gravestone.x, pos_img_1P_gravestone.y, &img_gravestone_right);
		puimage_alpha(pos_img_2P_gravestone.x, pos_img_2P_gravestone.y, &img_gravestone_left);

		puimage_alpha(pos_img_tip.x, pos_img_tip.y, &img_selector_tip);
		


		//渲染1p 2p角色动画
		animation_peashooter.on_draw(camera, pos_animation_1P.x, pos_animation_1P.y);

		animation_sunflower.on_draw(camera, pos_animation_2P.x, pos_animation_2P.y);

		//渲染名字
		switch (player_type_1)
		{
		case SelectorScene::PlayerType::Peashooter:
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtexy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::Sunflower:
			pos_img_1P_name.x = pos_img_1P_gravestone.x + (img_gravestone_right.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtexy_shaded(pos_img_1P_name.x, pos_img_1P_name.y, str_sunflower_name);
			break;
		}

		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_peashooter_name)) / 2;
			outtexy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_peashooter_name);
			break;
		case SelectorScene::PlayerType::Sunflower:
			pos_img_2P_name.x = pos_img_2P_gravestone.x + (img_gravestone_left.getwidth() - textwidth(str_sunflower_name)) / 2;
			outtexy_shaded(pos_img_2P_name.x, pos_img_2P_name.y, str_sunflower_name);
			break;

		}


	}
	void on_input(const ExMessage& msg) {
		//角色选取 场景跳转
		if (msg.message != WM_KEYUP) return;
		
		switch (msg.vkcode)
		{
		case 39://->
			if (player_type_2 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Peashooter;
				animation_sunflower.set_atlas(&atlas_peashooter_idle_left); //注意方向
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Sunflower;
				animation_sunflower.set_atlas(&atlas_sunflower_idle_left);
			}
			break;

		case 37://<-
			if (player_type_2 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Peashooter;
				animation_sunflower.set_atlas(&atlas_peashooter_idle_left); //注意方向
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_2 = PlayerType::Sunflower;
				animation_sunflower.set_atlas(&atlas_sunflower_idle_left);
			}

			break;
		case 68://D
			if (player_type_1 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Peashooter;
				animation_peashooter.set_atlas(&atlas_peashooter_idle_right); //注意方向
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Sunflower;
				animation_peashooter.set_atlas(&atlas_sunflower_idle_right);
			}

			break;
		case 65://A
			if (player_type_1 == PlayerType::Sunflower)
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Peashooter;
				animation_peashooter.set_atlas(&atlas_peashooter_idle_right); //注意方向
			}
			else
			{
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
				player_type_1 = PlayerType::Sunflower;
				animation_peashooter.set_atlas(&atlas_sunflower_idle_right);
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
		case SelectorScene::PlayerType::Peashooter:
			player_1P = new PeashooterPlayer();
			player_1P->id = PlayerID::P1;
			break;
		case SelectorScene::PlayerType::Sunflower:
			player_1P = new SunflowerPlayer();
			player_1P->id = PlayerID::P1;
			break;
	
		}
		switch (player_type_2)
		{
		case SelectorScene::PlayerType::Peashooter:
			player_2P = new PeashooterPlayer();
			player_2P->id = PlayerID::P2;
			break;
		case SelectorScene::PlayerType::Sunflower:
			player_2P = new SunflowerPlayer();
			player_2P->id = PlayerID::P2;
			break;

		}
	}

private:
	POINT pos_img_VS = { 0 };// Vs 艺术字图片位置
	POINT pos_img_tip = { 0 };// 提示信息文本图片位置
	POINT pos_img_1P = { 0 };// 1P 文本图片位置
	POINT pos_img_2P = { 0 };// 2P文本图片位置
	POINT pos_img_1P_desc = { 0 };//1P键位描述图片位置
	POINT pos_img_2P_desc = { 0 };// 2P键位描述图片位置
	POINT pos_img_1P_name = { 0 };//1P角色姓名文本位置
	POINT pos_img_2P_name = { 0 };//2P角色姓名文本位置
	POINT pos_animation_1P = { 0 };//1P角色动画位置
	POINT pos_animation_2P = { 0 };// 2P角色动画位置
	POINT pos_img_1P_gravestone = { 0 };// 1P墓碑图片位置
	POINT pos_img_2P_gravestone = { 0 };//2P墓碑图片位置
	POINT pos_1P_selector_btn_left = { 0 };//1P向左切换按钮位置
	POINT pos_1P_selector_btn_right = { 0 };// 1P向右切换按钮位置
	POINT pos_2P_selector_btn_left = { 0 };//2P向左切换按钮位置
	POINT pos_2P_selector_btn_right = { 0 };//2P 向右切换按钮位置
	
	Animation animation_peashooter; //豌豆动画 -->1p动画
	Animation animation_sunflower;//向日葵动画-->2p动画


	PlayerType player_type_1 = PlayerType::Peashooter;//1p 2p角色类型
	PlayerType player_type_2 = PlayerType::Sunflower;

	LPCTSTR str_peashooter_name = _T("豌豆射手");
	LPCTSTR str_sunflower_name = _T("向日葵");

	int scorll_line_x= 0; //背景板滚动线

	

private:
	void outtexy_shaded(int x,int y ,LPCTSTR str) {
		settextcolor(RGB(45, 45, 45));
		outtextxy(x + 3, y + 3, str);
		settextcolor(RGB(255, 255, 255));
		outtextxy(x, y, str);
	}
};