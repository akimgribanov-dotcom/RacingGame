#include "Mark.h"
#include "Quad.h"

void Mark::Screen(HDC H) { // отрисовка 
	HBRUSH    BW = CreateSolidBrush(0x00FFFFFF);
	FillRect(H, &Rect, BW);
	DeleteObject(BW);
}


void Mark::StripesMove(double dy, double P) { // сдвиг полоски при dy-шаг, P-предел
	double h = GetHeight();
	if (fMove) {
		Rect.top += dy;
		if (Rect.top > P) Rect.top -= h * 9;
		Rect.bottom = Rect.top + h;		
	}
	
}

