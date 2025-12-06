// @file: cons_test.cpp
//
#include <iostream>
#include <conio.h>
#include "c_render.h"
#include "cube.h"
#include "round.h"
#include "game.h"

int main()
{
    Round &round = Round::getInstance();

	round.setGlass(10, 15); // размер стакана

    IRender *render;
    render = new(CRender);

    render->Init();

    render->DrawGlass();

    render->DrawTxt("Hello", 9, 18);

    Cube cube(9, 2, 9, 255, 255, 0); //! нет проверки на вылет за стакан!!!
    //! Беда с преобразованием цвета!
    // Нет серого!
    //link:c_render.h#93
    //C:\Users\Alex\Documents\prog\matris\cons_test

    render->DrawCube(cube);

    //________________________________________________________________
    int i = _getch();
	return 0;
}

