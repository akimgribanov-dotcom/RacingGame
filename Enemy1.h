#pragma once
#include "Car.h"

class Enemy1 : public Car
{
private:

	bool rMove = false; // разрешение телепортации
	
public:

	void Move(double dy, double P);
	Enemy1();
	Enemy1(std::wstring name, long sdy);
	~Enemy1();

	/////
	//void Autopilot(int side, long dist); // полоса side: 1 - левая, 2 - правая  
	/////
};

