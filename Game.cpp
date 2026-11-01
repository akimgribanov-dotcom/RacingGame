#include "Game.h"
#include <stdio.h>
#include "Parameters.h"
#include <iostream>
#include <string>
using namespace std;

Game::Game() {
    cars = new Car * [count];

    cars[0] = new Car(L"Car.bmp", 0);
    cars[1] = new Enemy1(L"Truck.bmp", -5);
    cars[2] = new Enemy2(L"Bike.bmp", 15);
    cars[3] = new Enemy3(L"SilverCar.bmp", 10);
    cars[4] = new Enemy2(L"Orange.bmp", -30); 
}

Game::Game(int player) {
    cars = new Car * [count];

    if (player == 1) cars[0] = new Car(L"Car.bmp", 0);
    else  cars[0] = new Car(L"YellowCar.bmp", 0);

    cars[1] = new Enemy1(L"Truck.bmp", -5);   
    cars[2] = new Enemy2(L"Bike.bmp", 15);
    cars[3] = new Enemy3(L"SilverCar.bmp", 10);
    cars[4] = new Enemy2(L"Orange.bmp", -30); 
}

Game::~Game() {
    for (int i = 0; i < count; i++) delete(cars[i]);
    delete[] cars;
}

long Game::Cross1(Car* car1, Car* car2) {   // коды взаимного расположения car1 и car2
    long res = 0;   // результат для car1

    if (car1->Rect.left > car2->Rect.left) res += l2l1;      // левая сторона car1 правее левой стороны car2
    if (car1->Rect.left < car2->Rect.right) res += l1r2;     // левый сторона car1 левее правой стороны car2
    if (car1->Rect.top > car2->Rect.top) res += t2t1;        // верх car1 ниже верха car2
    if (car1->Rect.top < car2->Rect.bottom) res += t1b2;     // верх car1 выше низа car2
    if (car1->Rect.right > car2->Rect.left)  res += l2r1;    // правая сторона car1 правее левой стороны car2
    if (car1->Rect.right < car2->Rect.right) res += r1r2;    // правая сторона car1 левее правой стороны car2
    if (car1->Rect.bottom > car2->Rect.top) res += t2b1;     // низ car1 ниже верха car2
    if (car1->Rect.bottom < car2->Rect.bottom) res += b1b2;  // низ car1 выше низа car2

    return res;
}

long Direction(long dy1, long dy2)        // определение направления движения
{
    long res = 0;                         // едут в разных направлениях
    if ((dy1 < 0) && (dy2 < 0)) res = 1;  // оба едут вверх
    if ((dy1 > 0) && (dy2 > 0)) res = 2;  // оба едут вниз
    return res;
}

long Game::Cross(Car* car1, Car* car2) { // ситуация на дороге
    long res = 0;

    long res1 = Cross1(car1, car2);              // результат для car1

    // авария:
    if (Test(res1, lt)) res |= stAccident;       // левый верхний угол car1
    if (Test(res1, rt)) res |= stAccident;       // правый верхний угол car1
    if (Test(res1, rb)) res |= stAccident;       // правый нижний угол car1
    if (Test(res1, lb)) res |= stAccident;       // левый нижний угол car1

    // обгон:
    long d = Direction(car1->dy, car2->dy);      // направление машин: 0 - в разные стороны, 1 - вверх, 2 - вниз
    if (abs(car1->dy) > abs(car2->dy)) {
        if ((car1->Rect.bottom + car1->GetHeight() < car2->Rect.top) && (d == 1)) res |= stOvertaking;   // car1 обгоняет car2   
        if ((car1->Rect.top - car1->GetHeight() > car2->Rect.bottom) && (d == 2)) res |= stOvertaking;   // car2 обгоняет car1        
    }

    // зона приближения:
    if (abs(car1->dy) > abs(car2->dy)) {
        if ((car1->Rect.top > car2->Rect.bottom) && (car1->Rect.top - car1->GetHeight() < car2->Rect.bottom) && (d == 1) && (car1->Rect.right > car2->Rect.left) && (car1->Rect.left < car2->Rect.right)) res |= stConvergence;   // сближение едущих вверх
        if (car1->Rect.bottom < car2->Rect.top && car1->Rect.bottom + car1->GetHeight() > car2->Rect.top && (d == 2) && (car1->Rect.right > car2->Rect.left) && (car1->Rect.left < car2->Rect.right)) res |= stConvergence;   // сближение едущих вниз
    }

    return res;
}
 
 

void Game::AllMove() {

    int dy = round(V * ((double)stepShow / 1000.0));
    road.Move(dy);                                                      // сдвиг дороги
    for (int i = 1; i < count; i++) cars[i]->Move(dy, GetHeight());     // сдвиг машин

    for (int i = 0; i < count; i++) 
        for (int j = 0; j < count; j++) {

            if (i == j) continue;

            long Situations1 = Cross(cars[i], cars[j]);

            if (Test(Situations1,stAccident)) {                        // авария
                if (!cars[j]->crash) {
                    if (i == 0) { mes.code = 8;    mes.key = -100;    Execution(mes); }    // смена счёта при аварии
                    mes.code = 7;    mes.key = i;       Execution(mes);                    // авария машины i npc
                    mes.code = 7;    mes.key = j;       Execution(mes);                    // авария машины j npc
                }
            }

            if (Test(Situations1, stOvertaking)) {                    // i обгоняет j
              
                cars[i]->fReturn = true;
                if (cars[j]->fOver == false) {                    
                    if (i == 0) {
                        mes.code = 8;    mes.key = 100;     Execution(mes);               // смена счёта при обгоне
                        mes.code = 9;    mes.key = j;       Execution(mes);               // обгон машины j npc 
                    }                      
                }
            }
            
            if (Test(Situations1, stConvergence)) {                  // сближение cars[i] c cars[j]
                //mes.code = 10; mes.key = i; mes.key2 = j; Execution(mes);
                mes.code = 10; mes.key = i; Execution(mes);
            }
        }
}

void Game::Screen(HDC H1, HDC H2) {                       // отрисовка картинки

    // рисуем фон - зеленый
    HBRUSH    GB = CreateSolidBrush(0x0000FF00);          // зеленая кисть
    FillRect(H2, &Rect, GB);

    road.Screen(H2);                                      // рисуем дорогу

    for (int i = 0; i < count; i++) cars[i]->Screen(H2);  // рисуем машины
     
    score.Screen(H2);                                     // счёт


   // HBRUSH    BW = CreateSolidBrush(0x000000FF);        // контрольный вывод
   // FillRect(H2, &Rect, BW);
   // DeleteObject(BW);
   // std::wstring scoreText = L" fReturn" + std::to_wstring(cars[1]->fOver);
   // DrawText(H2, scoreText.c_str(), scoreText.length(), &Rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


    BitBlt(H1, Rect.left, Rect.top, Rect.right, Rect.bottom, H2, Rect.left, Rect.top, SRCCOPY);  // перенос на экран

    DeleteObject(GB);
}


int Game::Line(Car* car) {
    int line = 0;                       // полоса дороги одного направления: 1 - левая, 2 - правая
    if (((car->Rect.left > road.Rect.left) && (car->Rect.right < (road.Rect.left + road.GetHeight() / 4))) ||
        ((car->Rect.left > (road.Rect.left + road.GetWidth() / 2)) && (car->Rect.right < (road.Rect.left + road.GetWidth() * 0.75)))) line = 1;
    if (((car->Rect.left > (road.Rect.left + road.GetWidth() / 4)) && (car->Rect.right < (road.Rect.left + road.GetWidth() / 2))) ||
        ((car->Rect.left > (road.Rect.left + road.GetWidth() * 0.75)) && (car->Rect.right < road.Rect.right))) line = 2;

    return line;
}

void Game::Execution(message& mes) {

    switch (mes.code) {

    case 1:                             // выход из игры
        running = false;
        break;

    case 2:                             // влево  
        if ((cars[0]->Rect.left > Rect.left + mes.key) && (V != 0)) cars[0]->MoveLeft();
        break;

    case 3:                             // вправо 
        if ((cars[0]->Rect.right < Rect.right - mes.key) && (V != 0)) cars[0]->MoveRight();
        break;

    case 4:
        if (V < 1000) V += mes.key;     // увеличиваем скорость                          
        break;

    case 5:
        if (V > 0) V -= mes.key;        // уменьшаем скорость                          
        break;

    case 6:                             // авария машины игрока
        V = 0;
        break;

    case 7:                             // авария с машиной mes.key
        cars[mes.key]->crash = true;  cars[mes.key]->dy = 0.0;
        break;

    case 8:                             // смена счета на mes.key
        score.Change(mes.key);          // меняем счёт
        break;

    case 9:                             // обгон машины  mes.key
        cars[mes.key]->fOver = true;    // обогнали
        break;

    case 10:                            // сближение mes.key с mes.key2

        int line = Line(cars[mes.key]);

        cars[mes.key]->fReturn = false;
        cars[mes.key]->fConv = true;

        if (line == 1) cars[mes.key]->MoveRight();
        if (line == 2) cars[mes.key]->MoveLeft();

        break;
    }
    mes.code = 0;
    mes.key = 0;

}

void Game::Run(HDC H1, HDC H2) {        // стартовые координаты
    
    road.MakeMarks();
    
    cars[0]->SetSize(road.Rect.right, 0.8 * road.GetHeight(), cars[0]->GetWidth(), cars[0]->GetHeight());
    cars[0]->mainCar = true;
    cars[1]->SetSize(road.Rect.left + 0.75 * road.GetWidth() + (road.GetWidth() / 8 - cars[0]->GetWidth() / 2), 0.7 * road.GetHeight(), cars[1]->GetWidth(), cars[1]->GetHeight());
    //cars[2]->SetSize(road.Rect.left + (road.GetWidth() / 8 - cars[0]->GetWidth() / 2), road.Rect.top - 0.2 * road.GetHeight(), cars[2]->GetWidth(), cars[2]->GetHeight());
    cars[2]->SetSize(road.Rect.left + road.GetWidth() / 4 + (road.GetWidth() / 8 - cars[0]->GetWidth() / 2), road.Rect.top - 0.2 * road.GetHeight(), cars[2]->GetWidth(), cars[2]->GetHeight());
    cars[3]->SetSize(road.Rect.left + road.GetWidth() / 4 + (road.GetWidth() / 8 - cars[0]->GetWidth() / 2), road.GetHeight(), cars[3]->GetWidth(), cars[3]->GetHeight());
    //cars[4]->SetSize(road.Rect.left + 0.5 * road.GetWidth() + (road.GetWidth() / 8 - cars[4]->GetWidth() / 2), 0.7 * road.GetHeight(), cars[4]->GetWidth(), cars[4]->GetHeight());
    cars[4]->SetSize(road.Rect.left + 0.75 * road.GetWidth() + (road.GetWidth() / 8 - cars[4]->GetWidth() / 2), -0.7 * road.GetHeight(), cars[4]->GetWidth(), cars[4]->GetHeight());

}
   

Score& Game::GetScore() {            // доступ к счету 
    return score;
}


