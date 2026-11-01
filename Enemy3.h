#pragma once
#include "Car.h"
#include <time.h>

class Enemy3 :  public Car
{
private:
	bool rMove = true; // разрешение телепортации
	long Sdy = 0;
public:
	void Move(double dy, double P);
	Enemy3();
	Enemy3(std::wstring name, long sdy);
	~Enemy3();

	/*
	void MoveRight();
	void MoveLeft();
	void Autopilot();
	*/
};

