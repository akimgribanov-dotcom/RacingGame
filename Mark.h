#pragma once
#include "Quad.h"

class Mark :  public Quad
{
public:
	bool fMove = false;
	void Screen(HDC H); // отрисовка
	void StripesMove(double dy, double P);   // сдвиг полоски при dy-шаг, P-предел
};

