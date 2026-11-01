#pragma once
#include "Quad.h"
class Score :  public Quad
{
private:
public:
	int currentScore = 0;

	void Screen(HDC H); // отрисовка
	void Change(int k); // изменение очков
};

