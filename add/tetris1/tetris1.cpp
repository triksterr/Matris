// @file: tetris1.cpp 

// Простой тетрис на C++ для консоли Windows
#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <cstdlib>

using namespace std;

// Константы игры
const int FIELD_WIDTH = 10;
const int FIELD_HEIGHT = 20;
const int SHAPES_COUNT = 7;

// Коды клавиш
const int KEY_LEFT = 75;
const int KEY_RIGHT = 77;
const int KEY_DOWN = 80;
const int KEY_UP = 72;
const int KEY_SPACE = 32;
const int KEY_ESC = 27;

// Класс для представления точки (координаты)
class Point
{
public:
    int x, y;

    Point(int x = 0, int y = 0): x(x), y(y) {}
};

// Класс для представления фигуры тетриса
class Tetromino
{
private:
    vector<vector<Point>> shapes;  // Все возможные формы фигуры (разные вращения)
    int currentRotation;           // Текущее вращение фигуры

public:
    int x, y;                      // Позиция фигуры на поле
    int type;                      // Тип фигуры (0-6)
    int color;                     // Цвет фигуры

    // Конструктор
    Tetromino()
    {
        // Инициализация всех 7 типов тетромино
        initShapes();
        currentRotation = 0;
        x = FIELD_WIDTH / 2 - 1;  // Начинаем примерно по центру
        y = 0;
    }

    // Инициализация всех возможных фигур
    void initShapes()
    {
        // Каждая фигура представлена как массив точек относительно центра
        shapes.clear();

        // I-фигура (длинная палка)
        vector<Point> shapeI;
        shapeI.push_back(Point(-1, 0));
        shapeI.push_back(Point(0, 0));
        shapeI.push_back(Point(1, 0));
        shapeI.push_back(Point(2, 0));
        shapes.push_back(shapeI);

        // O-фигура (квадрат)
        vector<Point> shapeO;
        shapeO.push_back(Point(0, 0));
        shapeO.push_back(Point(1, 0));
        shapeO.push_back(Point(0, 1));
        shapeO.push_back(Point(1, 1));
        shapes.push_back(shapeO);

        // T-фигура
        vector<Point> shapeT;
        shapeT.push_back(Point(-1, 0));
        shapeT.push_back(Point(0, 0));
        shapeT.push_back(Point(1, 0));
        shapeT.push_back(Point(0, 1));
        shapes.push_back(shapeT);

        // S-фигура
        vector<Point> shapeS;
        shapeS.push_back(Point(-1, 0));
        shapeS.push_back(Point(0, 0));
        shapeS.push_back(Point(0, 1));
        shapeS.push_back(Point(1, 1));
        shapes.push_back(shapeS);

        // Z-фигура
        vector<Point> shapeZ;
        shapeZ.push_back(Point(-1, 1));
        shapeZ.push_back(Point(0, 1));
        shapeZ.push_back(Point(0, 0));
        shapeZ.push_back(Point(1, 0));
        shapes.push_back(shapeZ);

        // J-фигура
        vector<Point> shapeJ;
        shapeJ.push_back(Point(-1, 0));
        shapeJ.push_back(Point(0, 0));
        shapeJ.push_back(Point(1, 0));
        shapeJ.push_back(Point(-1, 1));
        shapes.push_back(shapeJ);

        // L-фигура
        vector<Point> shapeL;
        shapeL.push_back(Point(-1, 0));
        shapeL.push_back(Point(0, 0));
        shapeL.push_back(Point(1, 0));
        shapeL.push_back(Point(1, 1));
        shapes.push_back(shapeL);
    }

    // Получить точки текущей фигуры с учетом вращения
    vector<Point> getPoints()
    {
        vector<Point> points;
        vector<Point> &shape = shapes[type];

        for(const Point &p : shape)
        {
            // Применяем текущее вращение (простой поворот на 90 градусов)
            Point rotated;
            switch(currentRotation % 4)
            {
                case 0: // 0 градусов
                    rotated.x = p.x;
                    rotated.y = p.y;
                    break;
                case 1: // 90 градусов
                    rotated.x = -p.y;
                    rotated.y = p.x;
                    break;
                case 2: // 180 градусов
                    rotated.x = -p.x;
                    rotated.y = -p.y;
                    break;
                case 3: // 270 градусов
                    rotated.x = p.y;
                    rotated.y = -p.x;
                    break;
            }

            // Добавляем смещение (позицию фигуры на поле)
            points.push_back(Point(rotated.x + x, rotated.y + y));
        }

        return points;
    }

    // Вращение фигуры
    void rotate()
    {
        currentRotation++;
    }

    // Случайная инициализация фигуры
    void randomize()
    {
        type = rand() % SHAPES_COUNT;
        color = 1 + rand() % 6;  // Цвета от 1 до 6
        currentRotation = 0;
        x = FIELD_WIDTH / 2 - 1;
        y = 0;
    }
};

// Класс игрового поля
class GameField
{
private:
    vector<vector<int>> field;  // Игровое поле (0 - пусто, >0 - цвет блока)
    int score;                  // Счет игрока
    int linesCleared;           // Количество очищенных линий

public:
    // Конструктор
    GameField()
    {
        // Инициализация поля нулями (пустое поле)
        field.resize(FIELD_HEIGHT, vector<int>(FIELD_WIDTH, 0));
        score = 0;
        linesCleared = 0;
    }

    // Проверка столкновения фигуры с границами поля или другими блоками
    bool checkCollision(const Tetromino &tetromino)
    {
        vector<Point> points = tetromino.getPoints();

        for(const Point &p : points)
        {
            // Проверка выхода за границы поля
            if(p.x < 0 || p.x >= FIELD_WIDTH || p.y >= FIELD_HEIGHT)
            {
                return true;
            }

            // Проверка столкновения с уже установленными блоками
            if(p.y >= 0 && field[p.y][p.x] != 0)
            {
                return true;
            }
        }

        return false;
    }

    // "Закрепление" фигуры на поле после падения
    void mergeTetromino(const Tetromino &tetromino)
    {
        vector<Point> points = tetromino.getPoints();

        for(const Point &p : points)
        {
            if(p.y >= 0)
            {  // Игнорируем блоки выше поля
                field[p.y][p.x] = tetromino.color;
            }
        }

        // Проверяем и очищаем заполненные линии
        checkLines();
    }

    // Проверка и очистка заполненных линий
    void checkLines()
    {
        int linesToClear = 0;

        // Проверяем каждую линию снизу вверх
        for(int y = FIELD_HEIGHT - 1; y >= 0; y--)
        {
            bool lineFull = true;

            // Проверяем, заполнена ли вся линия
            for(int x = 0; x < FIELD_WIDTH; x++)
            {
                if(field[y][x] == 0)
                {
                    lineFull = false;
                    break;
                }
            }

            // Если линия заполнена
            if(lineFull)
            {
                linesToClear++;
                linesCleared++;

                // Удаляем линию, сдвигая все линии выше вниз
                for(int yy = y; yy > 0; yy--)
                {
                    for(int x = 0; x < FIELD_WIDTH; x++)
                    {
                        field[yy][x] = field[yy - 1][x];
                    }
                }

                // Верхнюю линию очищаем
                for(int x = 0; x < FIELD_WIDTH; x++)
                {
                    field[0][x] = 0;
                }

                // Проверяем ту же позицию снова, так как туда сдвинулась новая линия
                y++;
            }
        }

        // Начисляем очки за очищенные линии
        if(linesToClear > 0)
        {
            score += (linesToClear * linesToClear * 100);  // Больше очков за несколько линий сразу
        }
    }

    // Получить значение ячейки поля
    int getCell(int x, int y) const
    {
        if(x >= 0 && x < FIELD_WIDTH && y >= 0 && y < FIELD_HEIGHT)
        {
            return field[y][x];
        }
        return 0;
    }

    // Геттеры
    int getScore() const { return score; }
    int getLinesCleared() const { return linesCleared; }

    // Отрисовка поля
    void draw()
    {
        // Очищаем консоль
        system("cls");

        // Рисуем верхнюю границу
        cout << "Score: " << score << " | Lines: " << linesCleared << endl;
        cout << "+";
        for(int x = 0; x < FIELD_WIDTH; x++) cout << "--";
        cout << "+" << endl;

        // Рисуем поле
        for(int y = 0; y < FIELD_HEIGHT; y++)
        {
            cout << "|";
            for(int x = 0; x < FIELD_WIDTH; x++)
            {
                if(field[y][x] == 0)
                {
                    cout << "  ";
                }
                else
                {
                             // Используем разные символы для разных цветов
                    char block = 219;  // Символ сплошного блока
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), field[y][x]);
                    cout << block << block;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Возвращаем белый цвет
                }
            }
            cout << "|" << endl;
        }

        // Рисуем нижнюю границу
        cout << "+";
        for(int x = 0; x < FIELD_WIDTH; x++) cout << "--";
        cout << "+" << endl;

        // Инструкции
        cout << "\nControls:" << endl;
        cout << "Arrow Left/Right - Move" << endl;
        cout << "Arrow Up - Rotate" << endl;
        cout << "Arrow Down - Fast drop" << endl;
        cout << "ESC - Exit" << endl;
    }
};

// Основной класс игры
class TetrisGame
{
private:
    GameField field;           // Игровое поле
    Tetromino currentPiece;    // Текущая падающая фигура
    Tetromino nextPiece;       // Следующая фигура
    bool gameOver;             // Флаг окончания игры
    int gameSpeed;             // Скорость игры (пауза между кадрами)

public:
    // Конструктор
    TetrisGame()
    {
        srand(time(0));  // Инициализация генератора случайных чисел
        gameOver = false;
        gameSpeed = 200;  // Начальная скорость (меньше = быстрее)

        // Создаем первую и следующую фигуры
        currentPiece.randomize();
        nextPiece.randomize();
    }

    // Отрисовка всей игры
    void draw()
    {
        // Создаем временную копию поля для отрисовки
        GameField tempField = field;

        // Добавляем текущую фигуру к отрисовке
        vector<Point> points = currentPiece.getPoints();
        for(const Point &p : points)
        {
            if(p.y >= 0)
            {
                // Временно изменяем поле для отрисовки
                // (в реальной реализации нужно переписать отрисовку)
            }
        }

        // Рисуем поле
        field.draw();

        // Рисуем текущую фигуру поверх поля
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;

        SetConsoleTextAttribute(console, currentPiece.color);
        for(const Point &p : points)
        {
            if(p.y >= 0)
            {
                pos.X = p.x * 2 + 1;  // *2 потому что каждый блок занимает 2 символа
                pos.Y = p.y + 2;      // +2 чтобы учесть заголовок и верхнюю границу
                SetConsoleCursorPosition(console, pos);
                cout << (char)219 << (char)219;
            }
        }
        SetConsoleTextAttribute(console, 7); // Возвращаем белый цвет

        // Показываем следующую фигуру
        pos.X = FIELD_WIDTH * 2 + 5;
        pos.Y = 2;
        SetConsoleCursorPosition(console, pos);
        cout << "Next piece:";

        vector<Point> nextPoints = nextPiece.getPoints();
        for(const Point &p : nextPoints)
        {
            pos.X = (FIELD_WIDTH + 3) * 2 + p.x * 2;
            pos.Y = 4 + p.y;
            SetConsoleCursorPosition(console, pos);
            SetConsoleTextAttribute(console, nextPiece.color);
            cout << (char)219 << (char)219;
        }
        SetConsoleTextAttribute(console, 7);
    }

    // Обработка ввода пользователя
    void processInput()
    {
        if(_kbhit())
        {
            int key = _getch();

            // Стрелки требуют двух вызовов _getch
            if(key == 0 || key == 224)
            {
                key = _getch();

                Tetromino testPiece = currentPiece;

                switch(key)
                {
                    case KEY_LEFT:
                        testPiece.x--;
                        break;
                    case KEY_RIGHT:
                        testPiece.x++;
                        break;
                    case KEY_DOWN:
                        testPiece.y++;
                        break;
                    case KEY_UP:
                        testPiece.rotate();
                        break;
                }

                // Если после перемещения/вращения нет столкновения - применяем изменения
                if(!field.checkCollision(testPiece))
                {
                    currentPiece = testPiece;
                }
            }
            else if(key == KEY_ESC)
            {
                gameOver = true;
            }
        }
    }

    // Обновление состояния игры
    void update()
    {
        // Пытаемся опустить фигуру
        Tetromino testPiece = currentPiece;
        testPiece.y++;

        // Если фигура может опуститься
        if(!field.checkCollision(testPiece))
        {
            currentPiece = testPiece;
        }
        else
        {
             // Иначе фигура достигла дна или другой фигуры
            field.mergeTetromino(currentPiece);

            // Начинаем новую фигуру
            currentPiece = nextPiece;
            nextPiece.randomize();

            // Если новая фигура сразу сталкивается - игра окончена
            if(field.checkCollision(currentPiece))
            {
                gameOver = true;
            }

            // Увеличиваем скорость каждые 10 линий
            if(field.getLinesCleared() % 10 == 0 && gameSpeed > 50)
            {
                gameSpeed -= 10;
            }
        }
    }

    // Главный игровой цикл
    void run()
    {
        cout << "TETRIS GAME" << endl;
        cout << "Press any key to start..." << endl;
        _getch();

        while(!gameOver)
        {
            // Обработка ввода
            processInput();

            // Обновление состояния
            update();

            // Отрисовка
            draw();

            // Пауза для контроля скорости игры
            Sleep(gameSpeed);
        }

        // Игра окончена
        system("cls");
        cout << "GAME OVER!" << endl;
        cout << "Final Score: " << field.getScore() << endl;
        cout << "Lines Cleared: " << field.getLinesCleared() << endl;
        cout << "\nPress any key to exit..." << endl;
        _getch();
    }
};

// Точка входа в программу
int main()
{
// Настраиваем консоль для корректного отображения
    system("mode con cols=50 lines=30");
    system("title Tetris Game");

    // Создаем и запускаем игру
    TetrisGame game;
    game.run();

    return 0;
}


//## Описание основных компонентов :
//
//### 1. Класс `Point`
//Простой класс для хранения координат x и y.
//
//### 2. Класс `Tetromino`
//Представляет фигуру тетриса :
//-Хранит все возможные формы фигур
//- Управляет вращением
//- Содержит информацию о позиции, типе и цвете фигуры
//
//### 3. Класс `GameField`
//Представляет игровое поле :
//-Хранит состояние всех закрепленных блоков
//- Проверяет столкновения
//- Обрабатывает заполненные линии
//- Начисляет очки
//
//### 4. Класс `TetrisGame`
//Основной класс игры :
//-Управляет игровым циклом
//- Обрабатывает пользовательский ввод
//- Координирует взаимодействие между фигурами и полем
//- Управляет скоростью игры
//
//## Управление:
//-Стрелка влево / вправо - движение фигуры
//- Стрелка вверх - вращение фигуры
//- Стрелка вниз - ускоренное падение
//- ESC - выход из игры
//
//## Особенности:
//-Разноцветные фигуры
//- Подсчет очков
//- Увеличение скорости по мере прогресса
//- Отображение следующей фигуры
//- Простая графика в консоли
//
//Для компиляции используйте любой компилятор C++, поддерживающий стандарт C++11 или выше(например, g++ или Visual Studio).