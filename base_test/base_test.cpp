// file: base_test.cpp

#include <iostream>

#include "application.h"

int main()
{
    std::cout << "Test!\n"; // просто вывод

    //Application& app = Application::get(); 
    int r = Application::get().start(); // Запускаем game

    if(r!=0) // какая-то ошибка
    {
        ;
    }

    system("pause"); // чтобы не закрывалась консоль
}
