#include "Parameters.h"


message mes = { 0, 0 };


bool running = true;          // флаг игры
int stepShow = 50;            // пауза между кадрами, в мс  


bool Test(long Code, long Mask)  // проверка наличия Mask в Code
{
	return ((Code & Mask) == Mask);
}
