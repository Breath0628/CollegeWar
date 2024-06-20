#pragma once
#include <cmath>
template<class T>

class Vector2
{
public:
	T x = 0;
	T y = 0;

public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(T x, T y) :x(x), y(y) {}

	Vector2<T> operator+(const Vector2<T>& vec)const {
		return Vector2<T>(x + vec.x, y + vec.y);
	}

	Vector2<T> operator-(const Vector2<T>& vec)const {
		return Vector2<T>(x - vec.x, y - vec.y);
	}

	T operator*(const Vector2<T>& vec)const//向量相乘 返回值为数值
	{
		return x * vec.x + y * vec.y;
	}


	Vector2<T> operator*(T val)const//向量乘数值 返回值为向量
	{
		return  Vector2<T>(val * x, val * y);
	}

	void operator+=(const Vector2<T>& vec) {
		x += vec.x;
		y += vec.y;
	}


	void operator-=(const Vector2<T>& vec) {
		x -= vec.x;
		y -= vec.y;
	}

	
	float length() //返回向量长度
	{
		return sqrt(x * x + y * y);
	}

	Vector2<T> normalize()//向量标准化
	{
		float len = length();
		if (len == 0) return Vector2<T>(0, 0);
		return Vector2<T>(x / len, y / len);
	}

private:

};
