#include <stdio.h>
#include <Windows.h>
#include "Game.h"

HWND    HW = GetConsoleWindow();

HDC     H1 = GetDC(HW);
HDC     H2 = CreateCompatibleDC(H1);
HBITMAP BM;

RECT R; // рамка окна
int  W; // ширина окна
int  H; // высота окна

int numUser = 1; // число игроков

Game game(1);
Game game2(2);


// Главное меню

void CursorOff() {  // отключение курсора
    CONSOLE_CURSOR_INFO curs = { 0 };
    curs.dwSize = sizeof(curs);
    curs.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void CursorOn() {  // включение курсора
    CONSOLE_CURSOR_INFO curs = { 0 };
    curs.dwSize = sizeof(curs);
    curs.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}

void GraphInit()  // инициализация графики
{
    GetClientRect(HW, &R);     // размеры рамки
    W = R.right - R.left;      // ширина окна
    H = R.bottom - R.top;      // высота окна

    BM = CreateCompatibleBitmap(H1, W, H);
    SelectObject(H2, BM);

    CursorOff();               // отключение курсора
}

void GraphFree()  // закрытие графики
{
    ReleaseDC(HW, H1);
    DeleteDC(H2);
    DeleteObject(BM);
}

void Start() {
    running = true;
    int adr = 0; // адресат: 0 - никто, 1 - гейм1, 2 - гейм2, 3 - оба

    while (running) {

        // Проверяем, была ли нажата клавиша
        if (_kbhit()) {
            int key = _getch();
            if (key == 0) key = _getch();
            adr = 0;
            switch (key)
            {
            case 27: { mes.code = 1; adr = 3; break; }                  // Escape

            case 75: { mes.code = 2; mes.key = 20; adr = 1; break; }   // влево
            case 77: { mes.code = 3; mes.key = 20; adr = 1; break; }   // вправо
            case 72: { mes.code = 4; mes.key = 100; adr = 1; break; }  // увеличиваем скорость
            case 80: { mes.code = 5; mes.key = 100; adr = 1; break; }  // уменьшаем скорость

            case 97: case 65: case 244: case 212: { mes.code = 2; mes.key = 20; adr = 2; break; }   // влево aAфФ
            case 100: case 68: case 226: case 194: { mes.code = 3; mes.key = 20; adr = 2; break; }   // вправо dDвВ
            case 119: case 87: case 246: case 214: { mes.code = 4; mes.key = 100; adr = 2; break; }  // увеличиваем скорость wWцЦ
            case 115: case 83: case 251: case 219: { mes.code = 5; mes.key = 100; adr = 2; break; }  // уменьшаем скорость sSыЫ
            }

            if ((adr & 1) == 1) game.Execution(mes);
            if ((numUser == 2) && ((adr & 2) == 2)) game2.Execution(mes);
        }

        game.AllMove();             // сдвиг всех
        game.Screen(H1, H2);        // отрисовка картинки
        
        if (numUser == 2) {
            game2.AllMove();        // сдвиг всех
            game2.Screen(H1, H2);   // отрисовка картинки
        }
        
        Sleep(stepShow);            // пауза
    }
}


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    SetConsoleTitle(L"Гонки");

    RECT RR, RRpz;
    GetClientRect(GetDesktopWindow(), &RR);                         // разворот окна

    HWND Shell_TrayWnd = FindWindow(L"Shell_TrayWnd", NULL);
    GetWindowRect(Shell_TrayWnd, &RRpz);

    int screenWidth = RR.right - RR.left;  
    int screenHeight = (RR.bottom - RR.top) - (RRpz.bottom - RRpz.top); 

    MoveWindow(HW, 0, 0, screenWidth, screenHeight, TRUE);


    int p = 0; // пункт меню

    const int kp = 6; // количество пунктов меню
    COORD position[kp];

    char names[kp][100] = { "Старт1", "Старт2", "Настройки", "Справка",  "О программе", "Выход" };
    char abt[4][100] = {"(с) Сидорова Юлия Сергеевна", "группа 2 - 41, кафедра ПОКС, ИГЭУ","e-mail: jssidorova@mail.ru", "2025"};

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    PCONSOLE_SCREEN_BUFFER_INFO pwi = new CONSOLE_SCREEN_BUFFER_INFO;
    GetConsoleScreenBufferInfo(hConsole, pwi);
    

    GraphInit();          // инициализация графики

    do
    {
        int xmax, ymax;
        xmax = pwi->srWindow.Right;
        ymax = pwi->srWindow.Bottom;
        int y0 = ymax / 2 - 2;

        for (int i = 0; i < kp; i++)
        {
            position[i].X = (xmax - strlen(names[i])) / 2;
            position[i].Y = y0 + i;
        }

        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
        system("cls");
        SetConsoleTextAttribute(hConsole, 15 | BACKGROUND_BLUE);

        for (int i = 0; i < kp; i++)
        {
            SetConsoleCursorPosition(hConsole, position[i]);
            puts(names[i]);
        }
        SetConsoleTextAttribute(hConsole, 15 | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
        SetConsoleCursorPosition(hConsole, position[p]);
        puts(names[p]);

        unsigned char ch;
        do
        {
            ch = _getch();
            if (ch == 224)
            {
                ch = _getch();
                switch (ch)
                {
                case 72: // вверх
                    SetConsoleCursorPosition(hConsole, position[p]);
                    SetConsoleTextAttribute(hConsole, 15 | BACKGROUND_BLUE);
                    puts(names[p]);
                    p--;
                    if (p < 0) p = kp-1;
                    SetConsoleTextAttribute(hConsole, 15 | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
                    SetConsoleCursorPosition(hConsole, position[p]);
                    puts(names[p]); break;
                case 80: // вниз
                    SetConsoleCursorPosition(hConsole, position[p]);
                    SetConsoleTextAttribute(hConsole, 15 | BACKGROUND_BLUE);
                    puts(names[p]);
                    p++;
                    if (p > kp-1) p = 0;
                    SetConsoleTextAttribute(hConsole, 15 | FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE);
                    SetConsoleCursorPosition(hConsole, position[p]);
                    puts(names[p]); break;
                }
            }
        } while (ch != 13);
        switch (p)
        {
        case 0:      // Игра 1 пользователь
        {
            game.~Game();
            new (&game) Game(1);

            numUser = 1;
            game.SetSize(0, 0, W, H);

            int ww = W / 3;         // ширина дороги
            int z = (W - ww) / 2;   // ширина одной обочины
            game.road.SetSize(z, 0, ww, H);

            game.Run(H1, H2);

            game.GetScore().SetSize(game.Rect.left, game.Rect.top, game.GetWidth() / 10, game.GetHeight() / 10);

            Start();
            break;
        }

        case 1:      // Игра 2 пользователя
        {
            game.~Game();
            new (&game) Game(1);
            game2.~Game();
            new (&game2) Game(2);

            numUser = 2;

            game2.SetSize(0, 0, W / 2, H);
            game.SetSize(W / 2, 0, W / 2, H);

            int ww = W / 3;
            int z = (W - 2 * ww) / 4;
            game2.road.SetSize(z, 0, ww, H);
            game.road.SetSize(3 * z + ww, 0, ww, H);

            game2.Run(H1, H2);
            game.Run(H1, H2);

            game2.GetScore().SetSize(game2.Rect.left, game2.Rect.top, game2.GetWidth() / 10, game2.GetHeight() / 20);
            game.GetScore().SetSize(game.Rect.left, game.Rect.top, game.GetWidth() / 10, game.GetHeight() / 20);

            Start();
            break;
        }

        case 2:      // Настройки
            
            break;
        case 3:      // Справка
       
            break;
        case 4:      // О программе
            SetConsoleTextAttribute(hConsole, 15 | BACKGROUND_BLUE);
            system("cls");
            for (int i = 0; i < 4; i++)
            {
                position[i].X = (xmax - strlen(abt[i])) / 2;
                position[i].Y = y0 + i;
            }

            SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
            system("cls");
            SetConsoleTextAttribute(hConsole, 15 | BACKGROUND_BLUE);

            for (int i = 0; i < 4; i++)
            {
                SetConsoleCursorPosition(hConsole, position[i]);
                puts(abt[i]);
            }
            ch = _getch();
            break;
        }
    } while (p != kp-1);

    GraphFree();  // закрытие графики
    return 0;
}
