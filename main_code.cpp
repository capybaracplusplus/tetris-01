#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctime>
#include <thread>


// пробел = 32
// вверх = 224 72
// Вниз = 224 80
// Влево = 224 75
// Вправо = 224 77


using namespace std;


bool game = true;

vector<vector<bool>> v(10, vector<bool>(10, 0));

int x = 4, y = 0;


void gotoxy(int xpos, int ypos) // тыкает курсором
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
}

int func() // отрисовывает игровое поле
{
    
    gotoxy(0, 0);
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; j++)
        {
            cout << v[i][j];
        }
        cout << endl;
    }
    gotoxy(0, 0);
    return 0;
}

void cub() // создание нового кубика
{

    if (v[4][0] == 0)
    {
        x = 4;
        y = 0;
    }
    else
    {
        game = false;
    }

}

void ded() // проверка
{
    for (int i = 0; i < v[0].size(); ++i)
    {
        bool isFilled = true;
        for (int j = 0; j < v.size(); ++j)
        {
            if (!v[j][i])
            {
                isFilled = false;
                break;
            }

        }
        if (isFilled)
        {
            for (int l = i; l > 0; --l)
            {
                for (int g = 0; g < v.size(); ++g)
                {
                    v[g][l] = v[g][l - 1];
                    gotoxy(g, l);
                    cout << (int)v[g][l];
                }
            }
            for (int g = 0; g < v.size(); ++g)
            {
                v[g][0] = 0;
            }
        }
    }



}


void look() // ставит "1" на выбранное место
{
    gotoxy(x, y);
    cout << 1;
    gotoxy(0, 0);
}

void pad() // отвечает за постоянное падение кубика
{
    gotoxy(x, y);
    cout << 0;
    if (y + 1 < v[0].size() && v[x][y + 1] != 1)
    {
        y += 1;
      
    }
    look();

    if (y == v.size() - 1 || (y<v[0].size() && v[x][y + 1] == 1))
    {   
        v[x][y] = 1;
        cub();
        ded();
    }

    gotoxy(0, 0);

}

void right() // двигать кубик вправо
{
    gotoxy(x, y);
    cout << 0;
    if (x + 1 < v.size() && v[x + 1][y] != 1)
    {
        x += 1;   
    }
    look();
    gotoxy(0, 0);
}


void left()  // двигать кубик влево
{
    gotoxy(x, y);
    cout << 0;
    if (x > 0 && v[x - 1][y] != 1)
    {
        x -= 1;
    }
    look();
    gotoxy(0, 0);
}

int main()
{
    func(); // сначала отрисовка поля
    // запуск считываний нажатия клавишь в отдельном потоке
    thread th1([] () {
        while(game) // игра идет пока можем добавить новый кубик
        {
                if (_kbhit())
            {
                int a, b; 
                b = _getch();
                a = _getch();
                // cout << b << " ";
                // cout << a << " ";
                if (b == 224)
                {
                    if (a == 77)
                    {
                        right();
                    }


                    if (a == 75)
                    {
                        left();
                    }
                    if (a == 80)
                    {
                        pad();
                    }
                }
            }
        }
        
        
        });


    while (game == true)
    {
        clock_t start_time = clock(); // задержка падения кубика
        while ((clock() - start_time) / CLOCKS_PER_SEC < 0.02) {}

        
        pad(); // кубик всегда падает на один вниз
        gotoxy(0, 0);

    }

    return 0;
}
