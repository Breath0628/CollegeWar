#pragma once
#include "scene.h"
#include "scene_manager.h"
#include "camera.h"
#include "utli.h"
#include "platform.h"
#include "player.h"
#include "eam_player.h"

extern SceneManager* scene_manager;
extern Player* player_1P;//1p����
extern Player* player_2P;//2p����
extern Camera main_camera;
extern IMAGE img_sky;                                  // ���ͼƬ
extern IMAGE img_hills;                                // ɽ��ͼƬ
extern IMAGE img_platform_large;                       //����ƽ̨ͼƬ
extern IMAGE img_platform_small;                       //С��ƽ̨ͼƬ
extern std::vector<Platform> platform_list;
;
class GameScene :public Scene
{
public:
	GameScene() = default;
	~GameScene() = default;

	void on_enter() {
		//����ͼƬ��Դ
		CHUAtlas.load_from_file(L"resources/game/CHU%d.png", 3);
		CHU = CHUAtlas.get_image(rand() % 3);
		loadimage(&stone, L"resources/game/stone.png");
		loadimage(&stone2, L"resources/game/stone2.png");

		//����ͼ��λ
		pos_img_sky.x = (getwidth() - img_sky.getwidth()) / 2;
		pos_img_sky.y = (getheight() - img_sky.getheight()) / 2;

		pos_img_CHU.x = (getwidth() - CHU->getwidth()) / 2;
		pos_img_CHU.y = (getheight() - CHU->getheight()) / 2;

		//�������¶�ʱ��
		ChangeBkTimer.set_wait_time(5000);
		ChangeBkTimer.set_callback([&]() {
			CHU = CHUAtlas.get_image(rand() % 3);
			});

		//��4��ƽ̨λ�ö�λ
		platform_list.resize(3);

		Platform& now_platform = platform_list[0];
		now_platform.img = &stone;
		now_platform.render_pos = { 0,500 };
		now_platform.shape = {
			(float)now_platform.render_pos.y + 30 ,//��shape.y��ֵ
			(float)now_platform.render_pos.x,//left
			(float)now_platform.render_pos.x + stone.getwidth()//right
		};

		Platform& now_platform1 = platform_list[1];
		now_platform1.img = &stone2;
		now_platform1.render_pos = { 115,300 };
		now_platform1.shape = {
			(float)now_platform1.render_pos.y + stone2.getheight() / 2 - 20,//��shape.y��ֵ
			(float)now_platform1.render_pos.x + 40,//left
			(float)now_platform1.render_pos.x + stone2.getwidth() - 40//right
		};

		Platform& now_platform2 = platform_list[2];
		now_platform2.img = &stone2;
		now_platform2.render_pos = { 805,300 };
		now_platform2.shape = {
			(float)now_platform2.render_pos.y + stone2.getheight() / 2 - 20,//��shape.y��ֵ
			(float)now_platform2.render_pos.x + 40,//left
			(float)now_platform2.render_pos.x + stone2.getwidth() - 40//right
		};

		//����Ҷ�λ
		player_1P->pos = { 200,50 };
		player_2P->pos = { 975,50 };
	}
	void on_update(int delta) {
		//����ͼ����
		ChangeBkTimer.on_update(delta);
		//����ͼ�ƶ�
		pos_img_CHU.x -= toRight * 1;
		if (getwidth() >= CHU->getwidth() + pos_img_CHU.x || pos_img_CHU.x >= 0)
			toRight = -1 * toRight;
		//ƽ̨����
		if (move)
		{
			platform_list[1].move(0, 640);
			platform_list[2].move(640, 1280);
		}
		//��Ҹ���
		player_1P->on_update(delta);
		player_2P->on_update(delta);
		main_camera.on_update(delta);
		//�ӵ�����
		for (Bullet* bullet : bullet_list)
		{
			bullet->on_update(delta);
		}
	}

	void on_draw(const Camera& camera) {

		//���Ʊ���ͼ
		puimage_alpha(camera, pos_img_sky, &img_sky);
		puimage_alpha(camera, pos_img_CHU, CHU);

		//����ƽ̨ͼ
		for (const Platform& platform : platform_list)
		{
			platform.on_draw(camera);
		}
		//������Ҷ���
		player_1P->on_draw(camera);
		player_2P->on_draw(camera);

		for (Bullet* bullet : bullet_list)
		{
			bullet->on_draw(main_camera);
		}

		if (is_debug)
		{
			settextcolor(RGB(255, 0, 0));
			outtextxy(15, 15, _T("����ģʽ,Q���ر�"));

		}


	}
	void on_input(const ExMessage& msg) {
		//����Ϣ���������Ϣ������
		player_1P->on_input(msg);
		player_2P->on_input(msg);

		switch (msg.message)
		{
		case WM_KEYUP:
			//'q'��������
			if (msg.vkcode == 0x51)is_debug = !is_debug;
			break;
		
		default:
			break;
		}
		switch (msg.vkcode) {
		case 32:
			if (msg.message == WM_KEYUP) {
				scene_manager->switch_to(SceneManager::SceneType::Menu);
				mciSendString(_T("play ui_confirm from 0"), NULL, 0, NULL);
			}
			break;
		}

	};
	void on_exit() {

	}

private:
	Atlas CHUAtlas;
	IMAGE* CHU;
	IMAGE stone;
	IMAGE stone2;
	POINT pos_img_sky = { 0 }; //���λ��
	POINT pos_img_CHU = { 0 };//CHUλ��
	Timer ChangeBkTimer;
	int toRight = 1;
	bool move = 1;

};