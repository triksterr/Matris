// @file: tetris3.cpp

// реализация консольной версии игры «Тетрис» на C++ с использованием классов.Код содержит подробные комментарии для лучшего понимания.

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

// Константы для размеров поля
const int FIELD_WIDTH = 12;    // Ширина игрового поля
const int FIELD_HEIGHT = 22;   // Высота игрового поля

// Класс для работы с игровым полем
class Field
{
private:
    bool field[FIELD_HEIGHT][FIELD_WIDTH];  // Массив для хранения состояния поля

public:
    // Конструктор
    Field()
    {
// Инициализация поля нулями
        for(int i = 0; i < FIELD_HEIGHT; i++)
        {
            for(int j = 0; j < FIELD_WIDTH; j++)
            {
                field[i][j] = false;
            }
        }
    }

    // Метод для проверки столкновения
    bool checkCollision(int x, int y, const bool shape[4][4])
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(shape[i][j])
                {
                    if(x + j >= FIELD_WIDTH || x + j < 0 || y + i >= FIELD_HEIGHT ||
                       (y + i < FIELD_HEIGHT && field[y + i][x + j]))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // Метод для добавления фигуры в поле
    void addShape(int x, int y, const bool shape[4][4])
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
            {
                if(shape[i][j])
                {
                    field[y + i][x + j] = true;
                }
            }
        }
    }

    // Метод для проверки и удаления полных строк
    void checkLines()
    {
        for(int i = 0; i < FIELD_HEIGHT; i++)
        {
            bool fullLine = true;
            for(int j = 0; j < FIELD_WIDTH; j++)
            {
                if(!field[i][j])
                {
                    fullLine = false;
                    break;
                }
            }
            if(fullLine)
            {
 // Удаляем строку
                for(int k = i; k > 0; k--)
                {
                    for(int j = 0; j < FIELD_WIDTH; j++)
                    {
                        field[k][j] = field[k - 1][j];
                    }
                }
                i--;  // Проверяем эту же строку снова
            }
        }
    }

    // Метод для отрисовки поля
    void draw()
    {
        system("cls");  // Очищаем консоль
        cout << "Тетрис\n\n";
        for(int i = 0; i < FIELD_HEIGHT; i++)
        {
            for(int j = 0; j < FIELD_WIDTH; j++)
            {
                if(field[i][j])
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
};

// Класс для работы с фигурами
class Shape
{
private:
    bool shapes[7][4][4];  // Массивы для хранения форм фигур
    int currentShape;      // Текущая фигура
    int rotation;         // Текущий поворот

public:
    // Конструктор
    Shape()
    {
// Инициализация форм фигур
// I-фигура
        shapes[0][0][1] = shapes[0][1][1] = shapes[0][2][1] = shapes[0][3][1] = true;
        // J-фигура
        shapes[1][0][0] = shapes[1][0][1] = shapes[1][1][1] = shapes[1][2][1] = true;
        // L-фигура
        shapes[2][0][1] = shapes[2][1][1] = shapes[2][2

////__________________________________________________________________________________________________

Давайте продолжим реализацию класса Shape и добавим основной игровой цикл.

```cpp
// Продолжение класса Shape
class Shape
        {
        private:
            bool shapes[7][4][4];  // Массивы для хранения форм фигур
            int currentShape;      // Текущая фигура
            int rotation;         // Текущий поворот

        public:
            // Конструктор
            Shape()
            {
       // Инициализация форм фигур
       // I-фигура
                shapes[0][0][1] = shapes[0][1][1] = shapes[0][2][1] = shapes[0][3][1] = true;
                // J-фигура
                shapes[1][0][0] = shapes[1][0][1] = shapes[1][1][1] = shapes[1][2][1] = true;
                // L-фигура
                shapes[2][0][1] = shapes[2][0][2] = shapes[2][1][1] = shapes[2][2][1] = true;
                // O-фигура
                shapes[3][0][1] = shapes[3][0][2] = shapes[3][1][1] = shapes[3][1][2] = true;
                // S-фигура
                shapes[4][0][2] = shapes[4][1][1] = shapes[4][1][2] = shapes[4][2][1] = true;
                // T-фигура
                shapes[5][0][1] = shapes[5][1][0] = shapes[5][1][1] = shapes[5][1][2] = true;
                // Z-фигура
                shapes[6][0][1] = shapes[6][1][1] = shapes[6][1][2] = shapes[6][2][2] = true;

                // Случайная начальная фигура
                srand(time(0));
                currentShape = rand() % 7;
                rotation = 0;
            }

            // Метод для получения текущей фигуры
            bool getShape(bool shape[4][4])
            {
                for(int i = 0; i < 4; i++)
                {
                    for(int j = 0; j < 4; j++)
                    {
                        shape[i][j] = shapes[currentShape][rotation][i][j];
                    }
                }
            }

            // Метод для поворота фигуры
            void rotate()
            {
                rotation = (rotation + 1) % 4;
            }

            // Метод для получения новой фигуры
            void newShape()
            {
                currentShape = rand() % 7;
                rotation = 0;
            }
        };

        // Основной класс игры
        class Tetris
        {
        private:
            Field gameField;      // Игровое поле
            Shape currentShape;   // Текущая фигура
            int score;           // Счет
            int level;           // Уровень
            int delay;           // Задержка падения

        public:
            // Конструктор
            Tetris(): score(0), level(1), delay(500)
            {
// Инициализация игры
            }

            // Метод для запуска игры
            void start()
            {
                bool gameOver = false;
                int x = FIELD_WIDTH / 2;  // Начальная позиция по X
                int y = 0;                // Начальная позиция по Y

                while(!gameOver)
                {
                    bool shape[4][4];
                    currentShape.getShape(shape);

                    // Отрисовка поля
                    gameField.draw();

                    // Обработка ввода
                    if(_kbhit())
                    {
                        char key = _getch();
                        switch(key)
                        {
                            case 'a':  // Движение влево
                                if(!gameField.checkCollision(x - 1, y, shape))
                                    x--;
                                break;
                            case 'd':  // Движение вправо
                                if(!gameField.checkCollision(x + 1, y, shape))
                                    x++;
                                break;
                            case 's':  // Ускоренное падение
                                if(!gameField.checkCollision(x, y + 1, shape))
                                    y++;
                                break;
                            case 'w':  // Поворот фигуры
                                currentShape.rotate();
                                currentShape.getShape(shape);
                                if(gameField.checkCollision(x, y, shape))
                                    currentShape.

////_______________________________________________________________________________________


```cpp
// Продолжение метода start() класса Tetris

currentShape.rotate();  // Возвращаем фигуру в исходное положение
                                break;
                            case 'r':  // Сброс игры
                                gameOver = true;
                                break;
                        }
                    }

                    // Падение фигуры
                    if(!gameField.checkCollision(x, y + 1, shape))
                    {
                        y++;
                    }
                    else
                    {
                             // Если фигура не может упасть дальше
                        gameField.addShape(x, y, shape);
                        gameField.checkLines();  // Проверяем полные строки
                        currentShape.newShape();  // Генерируем новую фигуру
                        x = FIELD_WIDTH / 2;  // Возвращаем начальную позицию
                        y = 0;

                        // Проверка на проигрыш
                        if(gameField.checkCollision(x, y, shape))
                        {
                            gameOver = true;
                        }
                    }

                    // Задержка для управления скоростью падения
                    Sleep(delay);
                }

                // Вывод результата игры
                cout << "\nИгра окончена! Ваш счет: " << score << endl;
            }
        };

        int main()
        {
            //! Отключаем буферизацию консоли
            setvbuf(stdout, NULL, _IONBF, 0);

            // Создаем и запускаем игру
            Tetris game;
            game.start();

            return 0;
        }

        //    ### Объяснение добавленного кода :

        //1. * *Обработка клавиш управления : **
        //    *Клавиша `a` — движение фигуры влево
        //    * Клавиша `d` — движение фигуры вправо
        //    * Клавиша `s` — ускорение падения
        //    * Клавиша `w` — поворот фигуры
        //    * Клавиша `r` — перезапуск игры

        //    2. * *Логика падения фигуры : **
        //    *Проверяем возможность падения фигуры вниз
        //    * Если падение невозможно :
        //*Добавляем фигуру к полю
        //    * Проверяем и удаляем полные строки
        //    * Генерируем новую фигуру
        //    * Проверяем условие проигрыша

        //    3. * *Задержка падения : **
        //    *Используем функцию `Sleep()` для контроля скорости падения фигур
        //    *Задержка может быть изменена для регулировки сложности

        //    4. * *Завершение игры : **
        //    *При проигрыше выводится финальный счет
        //    * Игра завершается

        //    ### Дополнительные улучшения :

        //*Можно добавить систему подсчета очков в зависимости от количества удаленных линий
        //    * Реализовать отображение следующей фигуры
        //    * Добавить звуковые эффекты
        //    * Улучшить визуальное оформление поля

        //    Для запуска игры достаточно скомпилировать код и выполнить исполняемый файл.Управление осуществляется с помощью клавиш `a`, `d`, `s`, `w` и `r`.