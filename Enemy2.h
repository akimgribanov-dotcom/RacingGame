#pragma once
#include "Car.h"

class Enemy2 : public Car
{
private:
	bool rMove = true; // разрешение телепортации
	long Sdy = 0;
public:
	/*void Screen(HDC H);*/
	void Move(double dy, double P);
	Enemy2();
	Enemy2(std::wstring name, long sdy);
	~Enemy2();
};

