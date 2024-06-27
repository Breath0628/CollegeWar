#pragma once
#include <graphics.h>
#include "utli.h"
#include "atlas.h"
#include <vector>
#pragma comment(lib,"Winmm.lib")
/*
Ϊ�������Դ����ȫ�ֱ���
��������:
img_:ͼƬ��Դ
atlas_:ͼ����Դ

*/
//����
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

//����
Atlas EAM_idle_left;
Atlas EAM_idle_right;
Atlas EAM_attack_left;
Atlas EAM_attack_right;
Atlas EAM_attack_ex_left;
Atlas EAM_attack_ex_right;

//��ѧ
IMAGE img_math_selector_background_left;        // ѡ�ǽ��泯�������ѧԺ����ͼƬ
IMAGE img_math_selector_background_right;  // ѡ�ǽ��泯���ҵ���ѧԺ����ͼƬ
Atlas atlas_math_idle_left;                     // ��ѧԺ�������Ĭ�϶���ͼ��
Atlas atlas_math_idle_right;                    // ��ѧԺ�����ҵ�Ĭ�϶���ͼ��
Atlas atlas_math_run_left;                      // ��ѧԺ��������ܲ�����ͼ��
Atlas atlas_math_run_right;                     // ��ѧԺ�����ҵ��ܲ�����ͼ��
Atlas atlas_math_attack_ex_left;                // ��ѧԺ������Ĺ�������ͼ��
Atlas atlas_math_attack_ex_right;               // ��ѧԺ�����ҵĹ�������ͼ��
Atlas atlas_math_die_left;                      // ��ѧԺ���������������ͼ��
Atlas atlas_math_die_right;                     // ��ѧԺ�����ҵ���������ͼ��
Atlas atlas_player3_idle;
Atlas atlas_player4_idle;
Atlas atlas_math_break;                         // �������鶯��ͼ��
IMAGE img_math;                                 // ����ͼƬ
IMAGE img_player3;
IMAGE img_player4;


//�������ɫ
Atlas atlas_computer_idle_left;               // �����Ĭ�϶���ͼ��
Atlas atlas_computer_idle_right;              // ���ҵ�Ĭ�϶���ͼ��
Atlas atlas_computer_run_left;                // ��������ܲ�����ͼ��
Atlas atlas_computer_run_right;               // �����ҵ��ܲ�����ͼ��
Atlas atlas_computer_attack_left;             // ������Ĺ�������ͼ��     
Atlas atlas_computer_attack_right;	// ���ҵĹ�������ͼ��
Atlas atlas_computer_attack_ex_left;             // ����������⹥������ͼ��     
Atlas atlas_computer_attack_ex_right;	// ���ҵ����⹥������ͼ��
Atlas atlas_computer_bullet;//�ӵ�
Atlas atlas_computer_bullet_break;//�ӵ�����
Atlas atlas_computer_ex;//�ͷż�����Ч


IMAGE img_menu_background;//���˵�����

//ѡ�ǽ����ز�
IMAGE img_VS;//vs������ͼƬ
IMAGE img_1P;//1p�ı�ͼ
IMAGE img_2P;//2p�ı�ͼ
IMAGE img_3P;
IMAGE img_4P;

IMAGE img_1P_desc;//1p��λ����ͼ
IMAGE img_2P_desc;//2p��λ����ͼ
IMAGE img_gravestone_left;//�������Ĺ��ͼ
IMAGE img_gravestone_right;//Ĺ������
IMAGE img_gravestone_3;
IMAGE img_gravestone_4;

IMAGE img_selector_background;//ѡ�ǽ��汳��ͼ
IMAGE img_selector_tip;//ѡ�ǽ�����ʾ��Ϣ�ı�ͼ

IMAGE img_1P_selector_btn_idle_left;            // 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_idle_right;           // 1P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_1P_selector_btn_down_left;            // 1P ����ѡ��ť����״̬ͼƬ
IMAGE img_1P_selector_btn_down_right;           // 1P ����ѡ��ť����״̬ͼƬ

IMAGE img_2P_selector_btn_idle_left;            // 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_idle_right;           // 2P ����ѡ��ťĬ��״̬ͼƬ
IMAGE img_2P_selector_btn_down_left;            // 2P ����ѡ��ť����״̬ͼƬ
IMAGE img_2P_selector_btn_down_right;           // 2P ����ѡ��ť����״̬ͼƬ

IMAGE img_peashooter_selector_background_left;  // ѡ�ǽ��泯����ı���ͼƬ
IMAGE img_peashooter_selector_background_right; // ѡ�ǽ��泯���ҵı���ͼƬ

IMAGE img_sunflower_selector_background_left;   // ѡ�ǽ��泯����ı���ͼƬ
IMAGE img_sunflower_selector_background_right;  // ѡ�ǽ��泯���ҵı���ͼƬ


//��Ϸ�����ز�
IMAGE img_sky;                                  // ���ͼƬ
IMAGE img_hills;                                // ɽ��ͼƬ
IMAGE img_platform_large;                       //����ƽ̨ͼƬ
IMAGE img_platform_small;                       //С��ƽ̨ͼƬ

IMAGE img_1P_cursor;                            // 1P ָʾ���ͼƬ
IMAGE img_2P_cursor;                            // 2P ָʾ���ͼƬ



IMAGE img_pea;                                  // �㶹ͼƬ

Atlas atlas_pea_break;                          // �㶹���鶯��ͼ��


Atlas atlas_run_effect;                         // ������Ч����ͼ��
Atlas atlas_jump_effect;                        // ��Ծ��Ч����ͼ��
Atlas atlas_land_effect;                        // �����Ч����ͼ��

IMAGE img_1P_winner;                            // 1P ��ʤ�ı�ͼƬ
IMAGE img_2P_winner;                            // 2P ��ʤ�ı�ͼƬ
IMAGE img_winner_bar;                           // ��ʤ��ұ����ı�ͼƬ

IMAGE img_avatar_peashooter;                    // ������ͷ��ͼƬ
IMAGE img_avatar_sunflower;                     // ���տ�ͷ��ͼƬ

//ѡ�ǳ��������Դ
Atlas atlas_angel;
Atlas atlas_demon;

//��ɫ�ֿ����Դ���� 300*300��С
Atlas atla_com_repo;
Atlas atla_eam_repo;
Atlas atla_math_repo;
Atlas atla_arch_repo;


void load_game_resources() {
    //�ֲ���˹��ȫ����Դ���� ��ը 


    //���ڴ������ҷ����imageͼƬ��atlasͼ����������Դֻ���ڷ������ҵ�ͼƬ��ͼ����Դ
    // �ֱ�ʹ��flip_image��flip_altas������ת�õ��������Դ��
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);
    //����
    atlas_archi_break.load_from_file(_T("resources/pea_break_%d.png"), 3);
    atlas_archi_idle_right.load_from_file(_T("resources/archi_static_%d.png"), 2); //////////////////////����
    flip_atlas(atlas_archi_idle_right, atlas_archi_idle_left);
    atlas_archi_run_right.load_from_file(_T("resources/archi_angery_%d.png"), 2); //////////////////////
    flip_atlas(atlas_archi_run_right, atlas_archi_run_left);
    atlas_archi_attack_ex_right.load_from_file(_T("resources/archi_angery_%d.png"), 2);  ////////////////////
    flip_atlas(atlas_archi_attack_ex_right, atlas_archi_attack_ex_left);
    atlas_archi_die_right.load_from_file(_T("resources/archi_die_%d.png"), 2);
    flip_atlas(atlas_archi_die_right, atlas_archi_die_left);
    loadimage(&img_archi_bullet, _T("resources/tower.png"));


    //����
    EAM_idle_left.load_from_file(_T("resources/economy/EAM_idle%d.png"), 2);
    flip_atlas(EAM_idle_left, EAM_idle_right);
    EAM_attack_left.load_from_file(_T("resources/economy/EAM_attack%d.png"), 2);
    flip_atlas(EAM_attack_left, EAM_attack_right);
    EAM_attack_ex_left.load_from_file(_T("resources/economy/EAM_attack%d.png"), 2);
    flip_atlas(EAM_attack_ex_left, EAM_attack_ex_right);
    
    //ѡ�ǳ��������Դ

    atlas_angel.load_from_file(L"resources/angel%d.jpg",3);
    atlas_demon.load_from_file(L"resources/demon%d.jpg", 3);

   
    //��ɫ�ֿ�
    atla_com_repo.load_from_file(_T("resources/repos/com/com%d.png"), 5);
    atla_eam_repo.load_from_file(_T("resources/repos/eam/eam%d.png"), 4);
    atla_math_repo.load_from_file(_T("resources/repos/math/math_show_%d.png"), 6);
    atla_arch_repo.load_from_file(_T("resources/repos/arch/archi_%d.png"),7);

    //��ѧ
    loadimage(&img_pea, _T("resources/tower.png")); //////////////////
    loadimage(&img_math, _T("resources/math.png")); ///�����ӵ�
    loadimage(&img_avatar_peashooter, _T("resources/avatar_peashooter.png"));
    loadimage(&img_avatar_sunflower, _T("resources/avatar_sunflower.png"));
    loadimage(&img_player3, _T("resources/player3"));
    loadimage(&img_player4, _T("resources/player4"));
    atlas_math_idle_right.load_from_file(_T("resources/math_idle_%d.png"), 2); //��ѧԺ��ֹ
    flip_atlas(atlas_math_idle_right, atlas_math_idle_left);
    atlas_math_run_right.load_from_file(_T("resources/math_run_%d.png"), 2);   //��ѧԺ����
    flip_atlas(atlas_math_run_right, atlas_math_run_left);
    atlas_math_attack_ex_right.load_from_file(_T("resources/math_attack_%d.png"), 2);  //��ѧԺ����
    flip_atlas(atlas_math_attack_ex_right, atlas_math_attack_ex_left);
    atlas_math_die_right.load_from_file(_T("resources/math_die_%d.png"), 8);           //��ѧԺ����
    flip_atlas(atlas_math_die_right, atlas_math_die_left);
    atlas_math_break.load_from_file(_T("resources/math_break_%d.png"), 3);             //��ѧԺ�ӵ�����

    //Ϊ�������ɫͼ��������Դ
    atlas_computer_attack_right.load_from_file(L"resources/computer/computer_attack_%d.png", 2);
    flip_atlas(atlas_computer_attack_right, atlas_computer_attack_left);
    atlas_computer_idle_right.load_from_file(L"resources/computer/computer_idle_%d.png", 2);
    flip_atlas(atlas_computer_idle_right, atlas_computer_idle_left);
    atlas_computer_run_right.load_from_file(L"resources/computer/computer_run_%d.png", 1);               // �����ҵ��ܲ�����ͼ��
    flip_atlas(atlas_computer_run_right, atlas_computer_run_left);
    atlas_computer_attack_ex_right.load_from_file(L"resources/computer/computer_attack_ex_%d.png", 2);
    flip_atlas(atlas_computer_attack_ex_right, atlas_computer_attack_ex_left);
    atlas_computer_bullet.load_from_file(L"resources/computer/bullet%d.png", 3);
    atlas_computer_bullet_break.load_from_file(L"resources/computer/break%d.png", 1);
    atlas_computer_ex.load_from_file(L"resources/computer/ex/%d.png", 9);
    mciSendString(_T("open resources/computer/bullet_hit.mp3 alias bgm_hit"), NULL, 0, NULL); //������Ч
    mciSendString(_T("open resources/computer/hit2.mp3 alias bgm_hit2"), NULL, 0, NULL); //������Ч
    mciSendString(_T("open resources/computer/computer_shoot.mp3 alias computer_shoot"), NULL, 0, NULL); //������Ч
    mciSendString(_T("open resources/computer/ex.mp3 alias computer_ex"), NULL, 0, NULL); //������Ч
    mciSendString(_T("open resources/game/upgrade.mp3 alias upgrade"), NULL, 0, NULL); //������Ч


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


    // ����MP3�ļ�
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