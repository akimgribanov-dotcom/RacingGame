#include "Road.h"

void Road::Screen(HDC H) { // отрисовка
	HBRUSH    BB = CreateSolidBrush(0x00000000);   // черная кисть
	FillRect(H, &Rect, BB);
    DeleteObject(BB);

    // нанесение разметки
    for (int i = 0; i < 14; i++) marks[i].Screen(H);
    
}

void Road::Move(int S) {
    for (int i = 0; i < 14; i++) marks[i].StripesMove(S, GetHeight());   

}

void Road::AddMark(int i, double x, double y, double h, bool move) {
    marks[i].Rect.left = x;
    marks[i].SetWidth(10);
    marks[i].Rect.top = y;
    if (move) marks[i].Rect.top -= h;
    marks[i].SetHeight(h);
    marks[i].fMove = move;
}

void Road::MakeMarks() {  // создание разметки
    // крайние полосы:
    AddMark(0, Rect.left + 5, 0, GetHeight(), false);
    AddMark(1, Rect.right - 15, 0, GetHeight(), false);

    // полосы в центре:
    AddMark(2, Rect.left + GetWidth() / 2 - 15, 0, GetHeight(), false);
    AddMark(3, Rect.right - GetWidth() / 2 + 5, 0, GetHeight(), false);

    // пунктирные линии:
    double h = GetHeight() / 9;
    double x = Rect.left + GetWidth() / 4 - 5;
    AddMark(4, x, h * 0, GetHeight() / 8, true);
    AddMark(5, x, h * 2, GetHeight() / 8, true);
    AddMark(6, x, h * 4, GetHeight() / 8, true);
    AddMark(7, x, h * 6, GetHeight() / 8, true);
    AddMark(8, x, h * 8, GetHeight() / 8, true);

    x = Rect.left + GetWidth() / 4 * 3 - 5;
    AddMark(9, x, h * 0, GetHeight() / 8, true);
    AddMark(10, x, h * 2, GetHeight() / 8, true);
    AddMark(11, x, h * 4, GetHeight() / 8, true);
    AddMark(12, x, h * 6, GetHeight() / 8, true);
    AddMark(13, x, h * 8, GetHeight() / 8, true);
}
