#pragma once
#include <iostream>
using namespace std;

const long l2l1 = 1;    // левая сторона car1 правее левой стороны car2
const long l1r2 = 2;    // левая сторона car1 левее правой стороны car2
const long t2t1 = 4;    // верх car1 ниже верха car2
const long t1b2 = 8;    // верх car1 выше низа car2
const long l2r1 = 16;   // правая сторона car1 правее левой стороны car2
const long r1r2 = 32;   // правая сторона car1 левее правой стороны car2
const long t2b1 = 64;   // низ car1 ниже верха car2
const long b1b2 = 128;  // низ car1 выше низа car2

const long lt = l2l1 + l1r2 + t2t1 + t1b2;   // левый верхний угол
const long rt = l2r1 + r1r2 + t2t1 + t1b2;   // правый верхний угол
const long rb = l2r1 + r1r2 + t2b1 + b1b2;   // правый нижний угол
const long lb = l2l1 + l1r2 + t2b1 + b1b2;   // левый нижний угол


// ситуации
const long stAccident   = 1;   // авария
const long stOvertaking = 2;   // обгон
const long stConvergence = 4;   // сближение с впереди едущей машиной


struct message  // структура сообщения
{
	int code;  // код сообщения
	int key;   // параметр (на сколько смещаться)
	int key2;
};


extern message mes;

extern bool running;            // флаг игры
extern int stepShow;            // пауза между кадрами, в мс  


bool Test(long Code, long Mask);  // проверка наличия Mask в Code
