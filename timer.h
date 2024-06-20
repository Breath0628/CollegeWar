#pragma once
#include <functional>

class Timer
{
public:
	Timer()=default;
	~Timer() = default;

	void restart() {
		pass_time = 0;
		shotted = 0;
	}
	void set_wait_time(int val) {
		wait_time = val;
	}
	void set_one_shot(bool flag) {
		one_shot = flag;
	}
	void set_callback(std::function<void()> callback){
		this->callback = callback;
	}
	void pause() {
		paused = 1;
	}
	void resume() {
		paused = 0;

	}
	void on_update(int delta){
		if (paused) return;
		pass_time += delta;
		if (pass_time>=wait_time)
		{
			if ((!one_shot || (one_shot && !shotted)) && callback) 
			//若（单次触发且未触发）或（循环触发）并有回调函数 则执行
			{ 
				callback();
			}
			shotted = 1;
			pass_time = 0;
		}
	}

private:
	int pass_time = 0;//已过时间
	int wait_time = 0;//等待时间
	bool paused = 0;//是否暂停
	bool shotted = 0;//是否已触发
	bool one_shot = 0;//是否单次触发
	std::function<void()>callback;//定时器结束后触发的回调函数
};
