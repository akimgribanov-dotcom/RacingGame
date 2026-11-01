#pragma once
#include "Quad.h"
#include <iostream>

class Car : public Quad
{
private:
	
protected:
	HBITMAP Img = NULL;

	long dx = 20;        // шаг по X	

	long Sdy = 0; // начальная скорость по Y 


	
public:
	bool fSub = false;
	bool fOver = false;   // флаг обгона нас
	bool fReturn = false; // флаг возврата на свое место/ свою полосу 
	bool fConv = false;   // флаг опасного сближения с переди едущей машиной
	long dy = 0;          // шаг по Y (скорость, + вниз, - вверх) 

	bool crash = false;  // флаг аварии  

	bool mainCar = false; // флаг машины игрока

	void Screen(HDC H); // отрисовка
	void MoveRight();   // перемещение направо
	void MoveLeft();    // перемещение налево
	void MoveUp();      // газ
	void MoveDown();    // тормоз
	
	virtual void Move(double dy, double P); // сдвиг машины при dy-шаг, P-предел
	
	
	//virtual void Autopilot(int side, long dist);
	

	Car();
	Car(std::wstring name, long sdy);
	~Car();		
};

