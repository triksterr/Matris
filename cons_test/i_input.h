#pragma once
// @file: i_input.h

#include <functional>

// Интерфейс ввода
class IInput
{
public:
	virtual ~IInput() = default;

    // Обновление состояния ввода
    virtual void Update() = 0;

    // Проверка нажатия клавиши
    virtual bool IsKeyPressed(int keyCode) const = 0;

    // Регистрация обработчика для конкретной клавиши
    virtual void RegisterKeyHandler(int keyCode, std::function<void()> callback) = 0;

    // Очистка всех обработчиков
    virtual void ClearHandlers() = 0;

};


//### Ввод:
//- влево
//- вправо
//- вниз
//- поворот по часовой
//- поворот против часовой
//- сброс
//- Показать/скрыть следующую фигуру
//- применение бонуса
//- пауза
//- повышение уровня
//- завершение игры



// стрелки и пробел
// ASDW
// цифры


// Если окно не активно - клаву не опрашиааем.