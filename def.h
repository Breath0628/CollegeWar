#pragma once
#include <graphics.h>
#include "utli.h"
#include "atlas.h"
#include <vector>
#pragma comment(lib,"Winmm.lib")
/*
为载入的资源定义全局变量
命名规则:
img_:图片资源
atlas_:图集资源

*/
//建筑
IMAGE img_archi_bullet;
IMAGE img_tower;
Atlas atlas_archi_idle_left;
Atlas atlas_archi_idle_right;
Atlas atlas_archi_run_left;
Atlas atlas_archi_run_right;
Atlas atlas_archi_attack_ex_left;             //
Atlas atlas_archi_attack_ex_right;
Atlas atlas_archi_die_left;
Atlas atlas_archi_die_right;
IMAGE img_archi_selector_background_left;       /////////
IMAGE img_archi_selector_background_right;
Atlas atlas_archi_break;

//经管
Atlas EAM_idle_left;
Atlas EAM_idle_right;
Atlas EAM_attack_left;
Atlas EAM_attack_right;
Atlas EAM_attack_ex_left;
Atlas EAM_attack_ex_right;

//数学
IMAGE img_math_selector_background_left;        // 选角界面朝向左的理学院背景图片
IMAGE img_math_selector_background_right;  // 选角界面朝向右的理学院背景图片
Atlas atlas_math_idle_left;                     // 理学院朝向左的默认动画图集
Atlas atlas_math_idle_right;                    // 理学院朝向右的默认动画图集
Atlas atlas_math_run_left;                      // 理学院朝向左的跑步动画图集
Atlas atlas_math_run_right;                     // 理学院朝向右的跑步动画图集
Atlas atlas_math_attack_ex_left;                // 理学院朝向左的攻击动画图集
Atlas atlas_math_attack_ex_right;               // 理学院朝向右的攻击动画图集
Atlas atlas_math_die_left;                      // 理学院朝向左的死亡动画图集
Atlas atlas_math_die_right;                     // 理学院朝向右的死亡动画图集
Atlas atlas_player3_idle;
Atlas atlas_player4_idle;
Atlas atlas_math_break;                         // 数分破碎动画图集
IMAGE img_math;                                 // 数分图片
IMAGE img_player3;
IMAGE img_player4;


//计算机角色
Atlas atlas_computer_idle_left;               // 向左的默认动画图集
Atlas atlas_computer_idle_right;              // 向右的默认动画图集
Atlas atlas_computer_run_left;                // 朝向左的跑步动画图集
Atlas atlas_computer_run_right;               // 朝向右的跑步动画图集
Atlas atlas_computer_attack_left;             // 朝向左的攻击动画图集     
Atlas atlas_computer_attack_right;	// 向右的攻击动画图集
Atlas atlas_computer_attack_ex_left;             // 朝向左的特殊攻击动画图集     
Atlas atlas_computer_attack_ex_right;	// 向右的特殊攻击动画图集
Atlas atlas_computer_bullet;//子弹
Atlas atlas_computer_bullet_break;//子弹破碎
Atlas atlas_computer_ex;//释放技能特效


IMAGE img_menu_background;//主菜单背景

//选角界面素材
IMAGE img_VS;//vs艺术字图片
IMAGE img_1P;//1p文本图
IMAGE img_2P;//2p文本图
IMAGE img_3P;
IMAGE img_4P;

IMAGE img_1P_desc;//1p键位描述图
IMAGE img_2P_desc;//2p键位描述图
IMAGE img_gravestone_left;//朝向左的墓碑图
IMAGE img_gravestone_right;//墓碑朝右
IMAGE img_gravestone_3;
IMAGE img_gravestone_4;

IMAGE img_selector_background;//选角界面背景图
IMAGE img_selector_tip;//选角界面提示信息文本图

IMAGE img_1P_selector_btn_idle_left;            // 1P 向左选择按钮默认状态图片
IMAGE img_1P_selector_btn_idle_right;           // 1P 向右选择按钮默认状态图片
IMAGE img_1P_selector_btn_down_left;            // 1P 向左选择按钮按下状态图片
IMAGE img_1P_selector_btn_down_right;           // 1P 向右选择按钮按下状态图片

IMAGE img_2P_selector_btn_idle_left;            // 2P 向左选择按钮默认状态图片
IMAGE img_2P_selector_btn_idle_right;           // 2P 向右选择按钮默认状态图片
IMAGE img_2P_selector_btn_down_left;            // 2P 向左选择按钮按下状态图片
IMAGE img_2P_selector_btn_down_right;           // 2P 向右选择按钮按下状态图片

IMAGE img_peashooter_selector_background_left;  // 选角界面朝向左的背景图片
IMAGE img_peashooter_selector_background_right; // 选角界面朝向右的背景图片

IMAGE img_sunflower_selector_background_left;   // 选角界面朝向左的背景图片
IMAGE img_sunflower_selector_background_right;  // 选角界面朝向右的背景图片


//游戏界面素材
IMAGE img_sky;                                  // 天空图片
IMAGE img_hills;                                // 山脉图片
IMAGE img_platform_large;                       //大型平台图片
IMAGE img_platform_small;                       //小型平台图片

IMAGE img_1P_cursor;                            // 1P 指示光标图片
IMAGE img_2P_cursor;                            // 2P 指示光标图片



IMAGE img_pea;                                  // 豌豆图片

Atlas atlas_pea_break;                          // 豌豆破碎动画图集


Atlas atlas_run_effect;                         // 奔跑特效动画图集
Atlas atlas_jump_effect;                        // 跳跃特效动画图集
Atlas atlas_land_effect;                        // 落地特效动画图集

IMAGE img_1P_winner;                            // 1P 获胜文本图片
IMAGE img_2P_winner;                            // 2P 获胜文本图片
IMAGE img_winner_bar;                           // 获胜玩家背景文本图片

IMAGE img_avatar_peashooter;                    // 婉逗射手头像图片
IMAGE img_avatar_sunflower;                     // 龙日葵头像图片

//选角场景身份资源
Atlas atlas_angel;
Atlas atlas_demon;

//角色仓库的资源加载 300*300大小
Atlas atla_com_repo;
Atlas atla_eam_repo;
Atlas atla_math_repo;
Atlas atla_arch_repo;


void load_game_resources() {
    //恐怖如斯的全体资源加载 爆炸 


    //对于存在左右方向的image图片和atlas图集，本地资源只存在方向向右的图片和图集资源
    // 分别使用flip_image和flip_altas函数翻转得到向左的资源，
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);
    //建筑
    atlas_archi_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
    atlas_archi_idle_right.load_from_file(_T("resources/archi_static_%d.png"), 2); //////////////////////建筑
    flip_atlas(atlas_archi_idle_right, atlas_archi_idle_left);
    atlas_archi_run_right.load_from_file(_T("resources/archi_angery_%d.png"), 2); //////////////////////
    flip_atlas(atlas_archi_run_right, atlas_archi_run_left);
    atlas_archi_attack_ex_right.load_from_file(_T("resources/archi_angery_%d.png"), 2);  ////////////////////
    flip_atlas(atlas_archi_attack_ex_right, atlas_archi_attack_ex_left);
    atlas_archi_die_right.load_from_file(_T("resources/archi_die_%d.png"), 2);
    flip_atlas(atlas_archi_die_right, atlas_archi_die_left);
    loadimage(&img_archi_bullet, _T("resources/tower.png"));


    //经管
    EAM_idle_left.load_from_file(_T("resources/economy/EAM_idle%d.png"), 2);
    flip_atlas(EAM_idle_left, EAM_idle_right);
    EAM_attack_left.load_from_file(_T("resources/economy/EAM_attack%d.png"), 2);
    flip_atlas(EAM_attack_left, EAM_attack_right);
    EAM_attack_ex_left.load_from_file(_T("resources/economy/EAM_attack%d.png"), 2);
    flip_atlas(EAM_attack_ex_left, EAM_attack_ex_right);
    
    //选角场景身份资源

    atlas_angel.load_from_file(L"resources/angel%d.jpg",3);
    atlas_demon.load_from_file(L"resources/demon%d.jpg", 3);

   
    //角色仓库
    atla_com_repo.load_from_file(_T("resources/repos/com/com%d.png"), 5);
    atla_eam_repo.load_from_file(_T("resources/repos/eam/eam%d.png"), 4);
    atla_math_repo.load_from_file(_T("resources/repos/math/math_show_%d.png"), 6);
    atla_arch_repo.load_from_file(_T("resources/repos/arch/archi_%d.png"),7);

    //数学
    loadimage(&img_pea, _T("resources/tower.png")); //////////////////
    loadimage(&img_math, _T("resources/math.png")); ///数分子弹
    loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
    loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));
    loadimage(&img_player3, _T("resources/player3"));
    loadimage(&img_player4, _T("resources/player4"));
    atlas_math_idle_right.load_from_file(_T("resources/math_idle_%d.png"), 2); //理学院静止
    flip_atlas(atlas_math_idle_right, atlas_math_idle_left);
    atlas_math_run_right.load_from_file(_T("resources/math_run_%d.png"), 2);   //理学院奔跑
    flip_atlas(atlas_math_run_right, atlas_math_run_left);
    atlas_math_attack_ex_right.load_from_file(_T("resources/math_attack_%d.png"), 2);  //理学院攻击
    flip_atlas(atlas_math_attack_ex_right, atlas_math_attack_ex_left);
    atlas_math_die_right.load_from_file(_T("resources/math_die_%d.png"), 8);           //理学院死亡
    flip_atlas(atlas_math_die_right, atlas_math_die_left);
    atlas_math_break.load_from_file(_T("resources/math_break_%d.png"), 3);             //理学院子弹破碎

    //为计算机角色图集载入资源
    atlas_computer_attack_right.load_from_file(L"resources/computer/computer_attack_%d.png", 2);
    flip_atlas(atlas_computer_attack_right, atlas_computer_attack_left);
    atlas_computer_idle_right.load_from_file(L"resources/computer/computer_idle_%d.png", 2);
    flip_atlas(atlas_computer_idle_right, atlas_computer_idle_left);
    atlas_computer_run_right.load_from_file(L"resources/computer/computer_run_%d.png", 1);               // 朝向右的跑步动画图集
    flip_atlas(atlas_computer_run_right, atlas_computer_run_left);
    atlas_computer_attack_ex_right.load_from_file(L"resources/computer/computer_attack_ex_%d.png", 2);
    flip_atlas(atlas_computer_attack_ex_right, atlas_computer_attack_ex_left);
    atlas_computer_bullet.load_from_file(L"resources/computer/bullet%d.png", 3);
    atlas_computer_bullet_break.load_from_file(L"resources/computer/break%d.png", 1);
    atlas_computer_ex.load_from_file(L"resources/computer/ex/%d.png", 9);
    mciSendString(_T("open resources/computer/bullet_hit.mp3 alias bgm_hit"), NULL, 0, NULL); //击中音效
    mciSendString(_T("open resources/computer/hit2.mp3 alias bgm_hit2"), NULL, 0, NULL); //击中音效
    mciSendString(_T("open resources/computer/computer_shoot.mp3 alias computer_shoot"), NULL, 0, NULL); //发射音效
    mciSendString(_T("open resources/computer/ex.mp3 alias computer_ex"), NULL, 0, NULL); //发射音效
    mciSendString(_T("open resources/game/upgrade.mp3 alias upgrade"), NULL, 0, NULL); //考研音效


    loadimage(&img_menu_background, _T("resources/menu_background.png"));
    loadimage(&img_VS, _T("resources/VS.png"));
    loadimage(&img_1P, _T("resources/1P.png"));
    loadimage(&img_2P, _T("resources/2P.png"));
    loadimage(&img_3P, _T("resources/3P.png"));
    loadimage(&img_4P, _T("resources/4P.png"));

    loadimage(&img_1P_desc, _T("resources/1P_desc.png"));
    loadimage(&img_2P_desc, _T("resources/2P_desc.png"));

    loadimage(&img_gravestone_right, _T("resources/gravestone.png"));
    flip_image(&img_gravestone_right, &img_gravestone_left);
    loadimage(&img_gravestone_4, _T("resources/gravestone.png"));
    flip_image(&img_gravestone_4, &img_gravestone_3);
    loadimage(&img_selector_tip, _T("resources/selector_tip.png"));
    loadimage(&img_selector_background, _T("resources/selector_background.png"));

    loadimage(&img_1P_selector_btn_idle_right, _T("resources/1P_selector_btn_idle.png"));
    flip_image(&img_1P_selector_btn_idle_right, &img_1P_selector_btn_idle_left);
    loadimage(&img_1P_selector_btn_down_right, _T("resources/1P_selector_btn_down.png"));
    flip_image(&img_1P_selector_btn_down_right, &img_1P_selector_btn_down_left);

    loadimage(&img_2P_selector_btn_idle_right, _T("resources/2P_selector_btn_idle.png"));
    flip_image(&img_2P_selector_btn_idle_right, &img_2P_selector_btn_idle_left);
    loadimage(&img_2P_selector_btn_down_right, _T("resources/2P_selector_btn_down.png"));
    flip_image(&img_2P_selector_btn_down_right, &img_2P_selector_btn_down_left);

    loadimage(&img_peashooter_selector_background_right, _T("resources/peashooter_selector_background.png"));
    flip_image(&img_peashooter_selector_background_right, &img_peashooter_selector_background_left);
    loadimage(&img_sunflower_selector_background_right, _T("resources/sunflower_selector_background.png"));
    flip_image(&img_sunflower_selector_background_right, &img_sunflower_selector_background_left);

    loadimage(&img_sky, _T("resources/sky.png"));
    loadimage(&img_hills, _T("resources/hills.png"));
    loadimage(&img_platform_large, _T("resources/platform_large.png"));
    loadimage(&img_platform_small, _T("resources/platform_small.png"));

    loadimage(&img_1P_cursor, _T("resources/1P_cursor.png"));
    loadimage(&img_2P_cursor, _T("resources/2P_cursor.png"));

    loadimage(&img_1P_winner, _T("resources/1P_winner.png"));
    loadimage(&img_2P_winner, _T("resources/2P_winner.png"));
    loadimage(&img_winner_bar, _T("resources/winner_bar.png"));

    loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
    loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));
    loadimage(&img_player3, _T("resources/player3"));
    loadimage(&img_player4, _T("resources/player4"));

    loadimage(&img_pea, _T("resources/tower.png")); //////////////////

   

    atlas_player3_idle.load_from_file(_T("resources/player3_%d.png"), 2);
    atlas_player4_idle.load_from_file(_T("resources/player4_%d.png"), 2);

    atlas_pea_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
    

    atlas_run_effect.load_from_file(_T("resources/run_effect_%d.png"), 4);
    atlas_jump_effect.load_from_file(_T("resources/jump_effect_%d.png"), 5);
    atlas_land_effect.load_from_file(_T("resources/land_effect_%d.png"), 2);


    // 加载MP3文件
    mciSendString(_T("open resources/bgm_game.mp3 alias bgm_game"), NULL, 0, NULL);
    mciSendString(_T("open resources/bgm_game.mp3 alias bgm_menu"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_1.mp3 alias pea_break_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_2.mp3 alias pea_break_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_break_3.mp3 alias pea_break_3"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_1.mp3 alias pea_shoot_1"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_2.mp3 alias pea_shoot_2"), NULL, 0, NULL);
    mciSendString(_T("open resources/pea_shoot_ex.mp3 alias pea_shoot_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode.mp3 alias sun_explode"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_explode_ex.mp3 alias sun_explode_ex"), NULL, 0, NULL);
    mciSendString(_T("open resources/sun_text.mp3 alias sun_text"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_confirm.wav alias ui_confirm"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_switch.wav alias ui_switch"), NULL, 0, NULL);
    mciSendString(_T("open resources/ui_win.wav alias ui_win"), NULL, 0, NULL);
}