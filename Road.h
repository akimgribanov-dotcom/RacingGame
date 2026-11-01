#pragma once
#include "Quad.h"
#include "Mark.h"


class Road : public Quad
{
private:
	void AddMark(int i, double x, double y, double h, bool move);
public:
	
	Mark marks[14];  // разметка

	void Screen(HDC H);
	void Move(int a);	
	void MakeMarks();

	
	

};

