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

    Cube cube(9, 2, 9, 100, 100, 100); //! нет проверки на вылет за стакан!!!

    render->DrawCube(cube);

    //________________________________________________________________
    int i = _getch();
	return 0;
}

