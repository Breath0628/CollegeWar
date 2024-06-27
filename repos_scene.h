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
		//��Դ����
		loadimage(&bk, L"resources/repos/bk.png");
		loadimage(&hand, L"resources/repos/hand.png");
		loadimage(&computerRoleImg, L"resources/repos/computer2.png");
		loadimage(&border, L"resources/repos/showBorder2.png");
		nowRolePos = { 30,10 };

		for (size_t i = 0; i < 4; i++)
		{
			aniList[i].set_interval(500);
			
		}
		//��������
		aniList[0].set_atlas(&atla_com_repo);
		aniList[1].set_atlas(&atla_math_repo);
		aniList[2].set_atlas(&atla_arch_repo);
		aniList[3].set_atlas(&atla_eam_repo);

	}
	void on_update(int delta) {
	//�������λ��
		cam.x += (right_down - left_down)  * delta*0.5;
	//��������
		for (size_t i = 0; i < 4; i++)
		{
			aniList[i].on_update(delta);
		}
		
	}
	void on_draw(const Camera& camera) {
		//��̬��Դ��Ⱦ
		putimage(0, 0, &bk);
		
		for (size_t i = 0; i < num; i++)
		{
			settextstyle(30, 0, _T("IPix"));
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			puimage_alpha(nowRolePos.x+480*i- cam.x, nowRolePos.y, &border);//��ɫ���

			aniList[i].on_draw(nowRolePos.x +50+ 480 * i + offset.x - cam.x, nowRolePos.y +50+ offset.y);
			//puimage_alpha(nowRolePos.x + 480 * i+offset.x- cam.x, nowRolePos.y+offset.y, &computerRoleImg);//��ɫͷ��
			outtextxy(nowRolePos.x + 480 * i +110- cam.x, nowRolePos.y + offset.y + 290,nameList[i]);//����
			settextstyle(25, 0, _T("IPix"));


			for (size_t j = 0; j < 8; j++)
			{
				outtextxy(nowRolePos.x + 480 * i + 40 - cam.x, nowRolePos.y + offset.y + 350+j*40, textList[i][j]);//����
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
	IMAGE bk,hand,border,showBorder;//���� ָ�� ͷ���
	IMAGE* nowRole;//���Ҳ�չʾ�Ľ�ɫ
	IMAGE computerRoleImg;//��ɫͷ��
	int num = 4;//��ɫ����
	Vector2<int> nowRolePos;//�Ҳ��ɫ��̬ͼչʾ��λ��
	Vector2<int> offset = {70,-15};//��ɫͷ��ƫ����
	Animation* nowRoleAnimation;//��ǰչʾ�Ľ�ɫ����
	Vector2<int> nowTextPos;//�Ҳ��ɫ�����ı���λ��
	RECT  rectList[4];//�����ı��ľ���λ��
	TCHAR textList[4][8][256] = {
		{
			_T("�����Ѿ��������Լ�����ξ�����"),
			_T("��ս����,��ֻ�Ǹ����ô����,��"),
			_T("��ƽ�Ķ����õ�Ҳ����ô����ս��"),
			_T("��ʼ,��ֻ�Ǵ��ŵ��Ա�ͷ���,ֱ"),
			_T("����һ���������Լ��Ĵ����Ȼ��"),
			_T("�Է����ȥ��֪ʶ��������,������"),
			_T("��ʶ����,��˵��")
			
		},
		{
			_T("�B�����Ǵ���һ�����صĺڿ��۾�,"),
			_T("��������һ������ѧ����������ͷ"),
			_T("��ֻ������ͷ������������ơ���"),
			_T("΢Ц����Ȼ����������˼������"),
			_T("ͷ��Ϊʲôֻ������,���������"),
			_T("����Ȱ�ˡ����¡�")

		},
		{

		    _T("���ǽ���ѧԺ��СС����������,��"),
			_T("�ʺ͵�ɫ��������õ����ѣ�����"),
			_T("��ͷ���ͺ�����ôƮ����ʫ��,���"),
			_T("��֪�������������׾��Ժܰ�����"),
			_T("��ѧ������Ƶ�.�ǻ�ͼ��,���ǽ�"),
			_T("����ˢ��ģ����������˵���Ƿ�"),
			_T("ˢ�����������Ҫ�����ˣ�����һ"),
			_T("��������һ�ţ�����һ¥��")

		},
		{
			

		    _T("˼���գ�һ�����԰������ĸ��š�ÿ"),
			_T("��,������չʾ�Լ�����䣬����Χ"),
			_T("����Ϊ֮��Ľ����������֪������Ǯ"),
			_T("�����������Ƕ�ô��Ȥ������������"),
			_T(",һ�����ⶼ����ͨ����Ǯ�������"),
			_T("������ʶ�����Ƹ�����Ψһ���Ҹ�Դ"),
			_T("Ȫ�����������ݻ���������ʵ֮��ҡ"),
			_T("�ڣ���ͼѰ����������С�"),
		}

	
	};
	//��ɫ�����б�
	TCHAR nameList[4][256] = {
			_T("��ϢѧԺ-����"),
			_T("��ѧԺ-�B��"),
			_T("����ѧԺ-����"),
			_T("����ѧԺ-˼����")

	};
	Vector2<int> cam = {0,0};//�����
	bool right_down=0,left_down=0;
	

	Animation aniList[4];//�����б� ��ֹ�������˶�
	Animation* nowAni[4];//���ŵĶ���ָ��
};