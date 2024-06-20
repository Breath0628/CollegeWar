#pragma once
#include <graphics.h>
#include "camera.h"
class Scene
{
public:

	Scene()=default;
	~Scene()=default;

	virtual void on_enter() {}; //进入场景
	virtual void on_update(int delta) { };//数据处理
	virtual void on_draw(const Camera& camera) {};//渲染
	virtual void on_input(const ExMessage& msg) {};//输入处理
   	virtual void exit() {};//场景退出

private:


};