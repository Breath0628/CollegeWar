#pragma once
#include <graphics.h>
#pragma comment(lib,"MSIMG32.LIB")
#include "camera.h"
#include "vector2.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>


inline void flip_image(IMAGE* src,IMAGE* dst){
	//图片翻转
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (size_t y = 0;y< h;y++) {
		for (size_t x = 0; x < w; x++)
		{
			int idx_src = y * w + x;
			int idx_dst = y * w + (w - x - 1); //对源图片的某像素获取其翻转后对应的索引值
			dst_buffer[idx_dst] = src_buffer[idx_src]; 
		}
	}
}

void flip_atlas(Atlas& src, Atlas& dst) {
	//由图集得到翻转图集
	dst.clear();
	for (size_t i = 0; i < src.get_size(); i++)
	{
		IMAGE img_flpipped;
		flip_image(src.get_image(i), &img_flpipped);
		dst.add_image(img_flpipped);
	}
}

inline void puimage_alpha(int dst_x, int dst_y, IMAGE* img) {
//消除空白背景的图片加载
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}
inline void puimage_alpha(const Camera camera,int dst_x, int dst_y, IMAGE* img) {
	//无背景且针对摄像机的渲染
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2<float>& pos_camera = camera.getPos();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x- pos_camera.x), (int)(dst_y-pos_camera.y), //针对摄像机的坐标转化
		w, h,GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void puimage_alpha(int dst_x, int dst_y,int width,int height, IMAGE* img,int src_x,int src_y) {
	//消除空白背景的图片加载 超出规定长宽裁剪
	int w = width>0?width:img->getwidth();
	int h = height>0?height:img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void puimage_alpha(const Camera camera,POINT pos, IMAGE* img) {
	//无背景且针对摄像机的渲染
	int dst_x = pos.x; 
	int dst_y = pos.y;
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2<float>& pos_camera = camera.getPos();
	AlphaBlend(GetImageHDC(GetWorkingImage()), (int)(dst_x - pos_camera.x), (int)(dst_y - pos_camera.y), //针对摄像机的坐标转化
		w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void line(const Camera& camera, int x1, int y1, int x2, int y2) 
{//针对摄像机的线绘制

	const Vector2<float>& pos_camera = camera.getPos();
	line((int)(x1 - pos_camera.x), (int)(y1 - pos_camera.y),
		(int)(x2 - pos_camera.x), (int)(y2 - pos_camera.y)
	);
}


// 获取当前时间的字符串表示
std::string getCurrentTime() {
	std::time_t now = std::time(nullptr);
	char buf[80];
	std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
	return std::string(buf);
}

// 将字符串和当前时间写入文件
void writeStringAndTimeToFile(const std::string & filename, const std::string & text) {
	std::ofstream outFile(filename, std::ios::app);
	if (!outFile) {
		throw std::runtime_error("无法打开文件进行写入: " + filename);
	}

	// 写入字符串
	outFile << text;

	// 获取当前时间字符串
	std::string currentTime = getCurrentTime();

	
	// 写入时间
	outFile << currentTime<<endl;

	if (!outFile) {
		throw std::runtime_error("写入文件失败: " + filename);
	}

	outFile.close();
}

// 从文件中读出时间
std::string readTimeFromFile(const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile) {
		throw std::runtime_error("无法打开文件进行读取: " + filename);
	}

	std::string content;
	std::getline(inFile, content);
	if (!inFile) {
		throw std::runtime_error("读取文件失败: " + filename);
	}

	inFile.close();
	return content;
}