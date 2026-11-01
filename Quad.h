#pragma once

#include <Windows.h>
#include <conio.h>


class Quad // четырёхугольник
{
protected:
	
public:
	
	RECT Rect = { 0 };    // координаты прямоугольника текущие
	RECT Rect0 = { 0 };    // координаты прямоугольника исходные

	char color = 0; // цвет

	long GetWidth();          // вычисление ширины
	void SetWidth(long W);    // установка ширины
	long GetHeight();         // вычисление длины
	void SetHeight(long H);   // установка длины
	void SetSize(long x, long y, long w, long h); // установка размеров

	virtual void Screen(HDC H); // отрисовка
};

