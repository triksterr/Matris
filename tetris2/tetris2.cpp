// @file: tetris2.cpp

//Вот простейшая реализация **Тетриса **в консоли Windows на языке **C++ * *с использованием * *классов * *и * *много комментариев * *для понимания.Игра включает :
//
//-Вращение фигур
//- Перемещение влево / вправо
//- Падение фигур
//- Проверку столкновений
//- Удаление заполненных линий
//- Отображение в консоли
//
//> ⚠️ Требуется компиляция под Windows(т.к.используется `windows.h` для управления курсором и цветом).

#include <iostream>
#include <vector>
#include <conio.h>  // Для _kbhit() и _getch()
#include <windows.h> // Для управления консолью
#include <cstdlib>  // Для rand()
#include <ctime>    // Для srand()

using namespace std;

// Размеры игрового поля
const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 20;

// Фигуры тетрамино (всего 7, представлены как 4x4 массивы)
vector<vector<vector<vector<int>>>> SHAPES = {
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, // I
    {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}},                         // J
    {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}},                         // L
    {{1, 1}, {1, 1}},                                           // O
    {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}},                         // S
    {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}},                         // T
    {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}                          // Z
};

// Цвета для фигур (используется в SetConsoleTextAttribute)
vector<int> COLORS = {10, 11, 9, 14, 13, 12, 15}; // Green, Cyan, Blue, Yellow, Magenta, Red, White

class Tetromino
{
public:
    int shapeIndex;
    vector<vector<int>> shape;
    int x, y; // Позиция фигуры на поле

    Tetromino()
    {
        shapeIndex = rand() % SHAPES.size();
        shape = SHAPES[shapeIndex];
        x = FIELD_WIDTH / 2 - shape[0].size() / 2; // Центрируем по X
        y = 0; // Начальная позиция сверху
    }

    // Поворот фигуры (по часовой стрелке)
    void rotate()
    {
        int n = shape.size();
        vector<vector<int>> newShape(n, vector<int>(n, 0));

        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                newShape[j][n - 1 - i] = shape[i][j];
            }
        }
        shape = newShape;
    }
};

class Tetris
{
private:
    vector<vector<int>> field; // Игровое поле: 0 = пусто, 1+ = заполнено (номер цвета)
    Tetromino *currentPiece;
    bool gameOver;
    int score;

    // Установка курсора в нужную позицию в консоли
    void gotoXY(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Очистка консоли
    void clearScreen()
    {
        system("cls");
    }

    // Отображение игрового поля
    void drawField()
    {
        // Перемещаем курсор в начало поля
        gotoXY(0, 0);

        // Выводим верхнюю границу
        cout << string(FIELD_WIDTH * 2 + 2, '#') << endl;

        for(int i = 0; i < FIELD_HEIGHT; ++i)
        {
            cout << "#"; // Левая граница
            for(int j = 0; j < FIELD_WIDTH; ++j)
            {
                if(field[i][j] > 0)
                {
                    // Устанавливаем цвет для блока
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLORS[field[i][j] - 1]);
                    cout << "[]"; // Блок
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Сброс цвета
                }
                else
                {
                    cout << "  "; // Пустое место
                }
            }
            cout << "#" << endl; // Правая граница
        }

        // Нижняя граница
        cout << string(FIELD_WIDTH * 2 + 2, '#') << endl;

        // Вывод счёта
        cout << "Score: " << score << endl;
    }

    // Проверка, может ли фигура быть помещена в позицию (x, y)
    bool canPlace(int x, int y, const vector<vector<int>> &shape)
    {
        for(int i = 0; i < shape.size(); ++i)
        {
            for(int j = 0; j < shape[i].size(); ++j)
            {
                if(shape[i][j])
                { // Если клетка фигуры заполнена
                    int newX = x + j;
                    int newY = y + i;

                    // Проверяем границы и столкновение с другими фигурами
                    if(newX < 0 || newX >= FIELD_WIDTH || newY >= FIELD_HEIGHT)
                        return false;
                    if(newY >= 0 && field[newY][newX] != 0)
                        return false;
                }
            }
        }
        return true;
    }

    // Размещение текущей фигуры на поле
    void placePiece()
    {
        for(int i = 0; i < currentPiece->shape.size(); ++i)
        {
            for(int j = 0; j < currentPiece->shape[i].size(); ++j)
            {
                if(currentPiece->shape[i][j])
                {
                    int x = currentPiece->x + j;
                    int y = currentPiece->y + i;
                    if(y >= 0) // Не размещаем выше поля
                        field[y][x] = currentPiece->shapeIndex + 1; // Сохраняем индекс + 1 как цвет
                }
            }
        }
    }

    // Удаление заполненных строк
    void clearLines()
    {
        int linesCleared = 0;
        for(int i = FIELD_HEIGHT - 1; i >= 0; --i)
        {
            bool full = true;
            for(int j = 0; j < FIELD_WIDTH; ++j)
            {
                if(field[i][j] == 0)
                {
                    full = false;
                    break;
                }
            }
            if(full)
            {
                field.erase(field.begin() + i);
                field.insert(field.begin(), vector<int>(FIELD_WIDTH, 0));
                ++linesCleared;
                ++i; // Проверяем ту же строку снова
            }
        }
        score += linesCleared * 100;
    }

    // Проверка окончания игры
    void checkGameOver()
    {
        for(int j = 0; j < FIELD_WIDTH; ++j)
        {
            if(field[0][j] != 0)
            {
                gameOver = true;
                return;
            }
        }
    }

public:
    Tetris()
    {
        field = vector<vector<int>>(FIELD_HEIGHT, vector<int>(FIELD_WIDTH, 0));
        currentPiece = new Tetromino();
        gameOver = false;
        score = 0;
        srand(time(0)); // Инициализация генератора случайных чисел
    }

    ~Tetris()
    {
        delete currentPiece;
    }

    // Основной игровой цикл
    void run()
    {
        while(!gameOver)
        {
            // Обработка ввода
            if(_kbhit())
            {
                char key = _getch();
                switch(key)
                {
                    case 'a':
                    case 'A':
                        if(canPlace(currentPiece->x - 1, currentPiece->y, currentPiece->shape))
                            --currentPiece->x;
                        break;
                    case 'd':
                    case 'D':
                        if(canPlace(currentPiece->x + 1, currentPiece->y, currentPiece->shape))
                            ++currentPiece->x;
                        break;
                    case 's':
                    case 'S':
                        if(canPlace(currentPiece->x, currentPiece->y + 1, currentPiece->shape))
                            ++currentPiece->y;
                        else
                        {
                            placePiece();
                            clearLines();
                            delete currentPiece;
                            currentPiece = new Tetromino();
                            checkGameOver();
                        }
                        break;
                    case 'w':
                    case 'W':
                        Tetromino temp = *currentPiece;
                        temp.rotate();
                        if(canPlace(temp.x, temp.y, temp.shape))
                            *currentPiece = temp;
                        break;
                }
            }

            // Автоматическое падение
            if(canPlace(currentPiece->x, currentPiece->y + 1, currentPiece->shape))
            {
                ++currentPiece->y;
            }
            else
            {
                placePiece();
                clearLines();
                delete currentPiece;
                currentPiece = new Tetromino();
                checkGameOver();
            }

            drawField();
            Sleep(500); // Задержка для скорости падения
        }

        // Вывод сообщения о проигрыше
        gotoXY(0, FIELD_HEIGHT + 2);
        cout << "Game Over! Your score: " << score << endl;
    }
};

int main()
{
    Tetris game;
    game.run();
    return 0;
}



//### 🔧 Компиляция и запуск
//
//```bash
//g++ - o tetris.exe tetris.cpp
//tetris.exe
//```
//
//-- -
//
//### 🎮 Управление
//
//- `A` — влево
//- `D` — вправо
//- `S` — вниз(ускорить падение)
//- `W` — вращать
//
//-- -
//
//### 💡 Примечания
//
//- Используется `system("cls")` — работает только в Windows.
//- Используется `windows.h` — не будет работать на Linux / macOS.
//- Для лучшего отображения используйте консоль с моноширинным шрифтом(например, Consolas).
//
//-- -
//
//Если хочешь версию под Linux или без `windows.h`, могу адаптировать!