#include "Quad.h"

 long Quad::GetWidth() {        // вычисление ширины
	return (Rect.right - Rect.left);
}

void Quad::SetWidth(long W) {  // установка ширины
	Rect.right = Rect.left + W;
	
}

long Quad::GetHeight() {       // вычисление длины
	return (Rect.bottom - Rect.top);
}

void Quad::SetHeight(long H) { // установка длины
	Rect.bottom = Rect.top + H;
}

void Quad::SetSize(long x, long y, long w, long h) {
	Rect.left = x;
	Rect.top = y;
	SetWidth(w);
	SetHeight(h);
	Rect0 = Rect;
 }

void Quad::Screen(HDC H) {       // тут будет переопределена отрисовка
};



