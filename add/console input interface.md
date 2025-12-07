Давайте разработаем более гибкий интерфейс ввода для игры Тетрис, используя концепцию чистого интерфейса. Это позволит легко менять реализацию ввода в будущем.

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>

// Интерфейс ввода
class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    // Обновление состояния ввода
    virtual void Update() = 0;

    // Проверка нажатия клавиши
    virtual bool IsKeyPressed(int keyCode) const = 0;

    // Регистрация обработчика для конкретной клавиши
    virtual void RegisterKeyHandler(int keyCode, std::function<void()> callback) = 0;

    // Очистка всех обработчиков
    virtual void ClearHandlers() = 0;
};

// Конкретная реализация для консоли
class ConsoleInputHandler : public IInputHandler {
private:
    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, std::function<void()>> keyCallbacks;

public:
    ConsoleInputHandler() {
        // Инициализация состояний клавиш
        keyStates.clear();
        keyCallbacks.clear();
    }

    void Update() override {
        while (_kbhit()) {
            int key = _getch();
            keyStates[key] = true;
        }
    }

    bool IsKeyPressed(int keyCode) const override {
        return keyStates.count(keyCode) > 0 && keyStates.at(keyCode);
    }

    void RegisterKeyHandler(int keyCode, std::function<void()> callback) override {
        keyCallbacks[keyCode] = callback;
    }

    void ClearHandlers() override {
        keyStates.clear();
        keyCallbacks.clear();
    }

    // Вызов всех зарегистрированных обработчиков
    void ProcessCallbacks() {
        for (auto& pair : keyStates) {
            if (pair.second && keyCallbacks.count(pair.first) > 0) {
                keyCallbacks[pair.first]();
                pair.second = false; // Сброс состояния после обработки
            }
        }
    }
};

// Пример использования
class TetrisGame {
private:
    IInputHandler* inputHandler;

public:
    TetrisGame(IInputHandler* handler) : inputHandler(handler) {
        // Регистрация обработчиков клавиш
        inputHandler->RegisterKeyHandler('A', [this]() { MoveLeft(); });
        inputHandler->RegisterKeyHandler('D', [this]() { MoveRight(); });
        inputHandler->RegisterKeyHandler('S', [this]() { MoveDown(); });
        inputHandler->RegisterKeyHandler('W', [this]() { Rotate(); });
        inputHandler->RegisterKeyHandler(VK_SPACE, [this]() { Drop(); });
    }

    void Run() {
        while (true) {
            inputHandler->Update();
            inputHandler->ProcessCallbacks();
            // Здесь основная логика игры
            Sleep(100);
        }
    }

private:
    void MoveLeft() { /* Логика движения влево */ }
    void MoveRight() { /* Логика движения вправо */ }
    void MoveDown() { /* Логика движения вниз */ }
    void Rotate() { /* Логика поворота */ }
    void Drop() { /* Логика падения */ }
};

int main() {
    // Создание конкретной реализации ввода
    ConsoleInputHandler inputHandler;
    
    // Создание игры с использованием интерфейса ввода
    TetrisGame game(&inputHandler);
    
    game.Run();
    
    return 0;
}
```

### Основные преимущества данного подхода:

1. **Гибкость реализации**:
* Можно легко заменить реализацию ввода без изменения основной логики игры
* Поддерживает разные источники ввода (консоль, GUI, геймпад)

2. **Модульная архитектура**:
* Четкое разделение ответственности между компонентами
* Легкая поддержка и расширение функционала

3. **Удобство использования**:
* Система обратных вызовов для обработки нажатий
* Централизованное управление состояниями клавиш

### Ключевые компоненты:

1. **Интерфейс IInputHandler**:
* Базовый контракт для всех реализаций ввода
* Методы для обновления состояния, проверки нажатий и регистрации обработчиков

2. **Конкретная реализация ConsoleInputHandler**:
* Работает с консольным вводом
* Хранит состояния клавиш и обратные вызовы
* Обрабатывает нажатия через `_kbhit()` и