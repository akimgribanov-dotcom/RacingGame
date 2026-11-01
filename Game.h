#pragma once
#include "Car.h"
#include "Road.h"
#include "Quad.h"
#include "Mark.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Parameters.h"
#include "Score.h"

class Game : public Quad

{
private:
	int count = 5;                // количество машинок   
	int V = 0;                    // скорость пикселей/сек
	bool fRL = false;			  // флаг возможности продолжать двигаться вправо и влево при сильном столкновении





	long Cross1(Car* car1, Car* car2);    // коды взаимного расположения car1 и car2
	
public :

	Road road;

	Car** cars;       // машинки

	Score score;

	Game();
	~Game();
	Game(int player);

	int Line(Car* car1);

	long Cross(Car *car1, Car *car2);
	void Execution(message& mes);
	void Run(HDC H1, HDC H2); // стартовые координаты
	void AllMove();
	void Screen(HDC H1, HDC H2);  // отрисовка картинки
	Score& GetScore(); // доступ к счету

};

