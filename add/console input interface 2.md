Вот пример реализации класса для ввода в игре Тетрис на C++:

```cpp
#include <iostream>
#include <conio.h> // для работы с клавиатурой
#include <windows.h> // для Windows-специфичных функций

class InputHandler {
private:
    bool keyPressed;
    int lastKey;

public:
    // Конструктор
    InputHandler() : keyPressed(false), lastKey(0) {}

    // Проверка нажатия клавиши
    bool isKeyPressed() const {
        return keyPressed;
    }

    // Получение последней нажатой клавиши
    int getLastKey() const {
        return lastKey;
    }

    // Обработка ввода
    void processInput() {
        if (_kbhit()) {
            lastKey = _getch();
            keyPressed = true;
        } else {
            keyPressed = false;
        }
    }

    // Обработка специальных клавиш (стрелки, пробел)
    void handleSpecialKeys(int key, int& direction, bool& rotate, bool& drop) {
        switch (key) {
            case 'a': case 'A': case 75: // влево
                direction = -1;
                break;
            case 'd': case 'D': case 77: // вправо
                direction = 1;
                break;
            case 's': case 'S': case 80: // вниз
                drop = true;
                break;
            case 'w': case 'W': case 72: // поворот
                rotate = true;
                break;
            case 32: // пробел
                drop = true;
                break;
            default:
                direction = 0;
                rotate = false;
                drop = false;
                break;
        }
    }

    // Очистка состояния клавиш
    void clearState() {
        keyPressed = false;
        lastKey = 0;
    }
};

// Пример использования
int main() {
    InputHandler input;
    int direction = 0;
    bool rotate = false;
    bool drop = false;

    while (true) {
        input.processInput();
        if (input.isKeyPressed()) {
            input.handleSpecialKeys(input.getLastKey(), direction, rotate, drop);
            // Здесь логика обработки движения фигуры
            std::cout << "Direction: " << direction << std::endl;
            std::cout << "Rotate: " << rotate << std::endl;
            std::cout << "Drop: " << drop << std::endl;
            input.clearState();
        }
        Sleep(100); // задержка для снижения нагрузки на процессор
    }

    return 0;
}
```

### Описание класса:

1. **Основные поля**:
* `keyPressed` - флаг нажатия клавиши
* `lastKey` - код последней нажатой клавиши

2. **Методы**:
* `isKeyPressed()` - проверка наличия нажатой клавиши
* `getLastKey()` - получение кода последней нажатой клавиши
* `processInput()` - обработка ввода с клавиатуры
* `handleSpecialKeys()` - обработка специальных клавиш (стрелки, пробел)
* `clearState()` - очистка состояния клавиш

### Особенности реализации:

* Класс использует функции `_kbhit()` и `_getch()` для неблокирующего чтения с клавиатуры
* Поддерживает как буквенные клавиши (a, s, d, w), так и стрелки
* Реализована обработка падения фигуры при нажатии пробела
* Предусмотрена очистка состояния после обработки ввода

Этот класс можно расширить дополнительными функциями для поддержки других клавиш или более сложной логики управления.