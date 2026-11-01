#include "Enemy2.h"
#include "Car.h"
#include <iostream>
using namespace std;


Enemy2::Enemy2() {}

Enemy2::Enemy2(std::wstring name, long sdy) {
	Img = (HBITMAP)LoadImage(NULL, name.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	Sdy = sdy;
	dy = Sdy;

	BITMAP Imgbm;

	GetObject(Img, sizeof(BITMAP), &Imgbm);

	Rect.left = 0;
	Rect.top = 0;
	Rect.right = Imgbm.bmWidth;
	Rect.bottom = Imgbm.bmHeight;

}

Enemy2::~Enemy2() {
	DeleteObject(Img);
}

void Enemy2::Move(double dy, double P) { // сдвиг полоски при dy-шаг, P-предел

	double h = GetHeight();

	Rect.top += dy + this->dy;

	if (fReturn == true) {				// возвращение в исходное положение
		if (Rect.left < Rect0.left) MoveRight();
		else if (Rect.left > Rect0.left) MoveLeft();
	}

	if ((Rect.top > P) && (rMove)) {   // перескок наверх
		Rect.top = -10 * h;
		rMove = false;
		crash = false;
		fOver = false;
		fReturn = false;
		this->dy = this->Sdy;
	}

	if ((Rect.bottom + h < 0) && (rMove)) {
		Rect.top = P + 2 * h;
		rMove = false;
		crash = false;
		fOver = false;
		fReturn = false;
		this->dy = this->Sdy;
	}

	Rect.bottom = Rect.top + h;

	if (Rect.top > 10 * h) rMove = true;  // низ
	if (Rect.top < -10 * h) rMove = true; // верх
}
