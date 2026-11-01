#include "Score.h"
#include <string>
using namespace std;

void Score::Screen(HDC H) { // отрисовка
	HBRUSH    BW = CreateSolidBrush(0x00FFFFFF);
	FillRect(H, &Rect, BW);
	DeleteObject(BW);
	
	std::wstring scoreText = L"—чЄт: " + std::to_wstring(currentScore);

	DrawText(H, scoreText.c_str(), scoreText.length(), &Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	
}; 

void Score::Change(int k) {
	currentScore += k;
}
