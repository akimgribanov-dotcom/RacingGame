#include "Enemy1.h"
#include "Car.h"


Enemy1::Enemy1() {}

Enemy1::Enemy1(std::wstring name, long sdy) {
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

Enemy1::~Enemy1() {
	DeleteObject(Img);
}

void Enemy1::Move(double dy, double P) { // сдвиг машины при dy-шаг, P-предел
	double h = GetHeight();

	if (fReturn == true) {		// возвращение в исходное положение
		MoveUp();
	}

	if (fConv == true) {	    // возвращение в исходное положение
		MoveDown();
	}

	Rect.top += dy + this->dy;


	if ((Rect.top > P) && (rMove)) {		 // перескок наверх
		Rect.top = -5 * h;
		rMove = false;
		crash = false;
		fOver = false;
		this->dy = this->Sdy;
	}
	

	if ((Rect.bottom < 0) && (rMove)) {		// перескок вниз
		Rect.top = P + 2 * h;
		rMove = false;
		crash = false;
		fOver = false;
		this->dy = this->Sdy;
	}	

	Rect.bottom = Rect.top + h;

	if (Rect.top > 15 * h) rMove = true;  // низ
	if (Rect.top < -15 * h) rMove = true; // верх
	
}

