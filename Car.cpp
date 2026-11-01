#pragma comment(lib, "Msimg32.lib")

#include "Car.h"
#include "Quad.h"
#include <iostream>
#include <string>
using namespace std;


Car::Car() {}

Car::Car(std::wstring name, long sdy) {
	Img = (HBITMAP)LoadImage(NULL, name.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	BITMAP Imgbm;

	GetObject(Img, sizeof(BITMAP), &Imgbm);

	Rect.left = 0;
	Rect.top = 0;
	Rect.right = Imgbm.bmWidth;
	Rect.bottom = Imgbm.bmHeight;

	Sdy = sdy;
	dy = Sdy;
}


Car::~Car() {
	DeleteObject(Img);	
}

void Car::Move(double dy, double P) {} // сдвиг машины при dy-шаг, P-предел

void Car::Screen(HDC H) {  // отрисовка

	BITMAP Imgbm;
	
	HDC hdcImg;
	hdcImg = CreateCompatibleDC(H);
	
	SelectObject(hdcImg, Img);	
	GetObject(Img, sizeof(BITMAP), &Imgbm);
	
	int w = Imgbm.bmWidth;
	int h = Imgbm.bmHeight;

	COLORREF transparentColor = RGB(0, 0, 0);
	
	TransparentBlt(H, Rect.left, Rect.top, w, h, hdcImg, 0, 0, w, h, transparentColor);  // Imgbm.bmWidth, Imgbm.bmHeight

	if (crash && !mainCar) {
		HBRUSH    BW = CreateSolidBrush(0x0000FFFF);
		RECT R;
		int m = 5;

		R.left = Rect.left; // левый верхний
		R.right = R.left + m;
		R.top = Rect.top;
		R.bottom = R.top + m;
		FillRect(H, &R, BW);

		R.left = Rect.right - m; // правый верхний
		R.right = R.left + m;
		R.top = Rect.top;
		R.bottom = R.top + m;
		FillRect(H, &R, BW);

		R.left = Rect.right - m; // правый нижний
		R.right = R.left + m;
		R.top = Rect.bottom - m;
		R.bottom = R.top + m;
		FillRect(H, &R, BW);

		R.left = Rect.left; // левый нижний
		R.right = R.left + m;
		R.top = Rect.bottom - m;
		R.bottom = R.top + m;
		FillRect(H, &R, BW);

		DeleteObject(BW);
	}
	
	DeleteDC(hdcImg);
}

void Car::MoveRight() { // перемещение направо
	
	Rect.left += dx;
	Rect.right += dx;
}

void Car::MoveLeft() { // перемещение налево
	
	Rect.left -= dx;
	Rect.right -= dx;
}

void Car::MoveUp() { // газ

	dy = Sdy;
}

void Car::MoveDown() { // тормоз

	dy = 0;
}