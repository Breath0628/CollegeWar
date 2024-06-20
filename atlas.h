#pragma once
#include <iostream>
#include <vector>
#include <graphics.h>
using namespace std;



class Atlas
{
public:

	Atlas() = default;
	~Atlas() = default;
	void load_from_file(LPCTSTR path_template, int num) {
		//从文件载入图集
		img_list.clear();
		img_list.resize(num);
		TCHAR path_file[256];
		for (int i = 0;i < num;i++) {
			_stprintf_s(path_file, path_template, i + 1); //拼接图片路径
			loadimage(&img_list[i], path_file);

		}
	}

	void clear() {
		img_list.clear();
	}

	int get_size() {
		return (int)img_list.size();
	}

	IMAGE* get_image(int idx) {
		//返回图集第i个图片的指针
		if (idx < 0 || idx >= img_list.size()) return nullptr;
		return &img_list[idx];
	}

	void add_image(const IMAGE& img){
		//为图集添加图片
		img_list.push_back(img);
	}


	
private:
	vector<IMAGE> img_list;
};