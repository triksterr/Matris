// @file: cons_test.cpp
//
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "c_render.h"
#include "cube.h"
#include "round.h"
#include "figure.h"
#include "game.h"



// Тест #0001 синхронизации поля Figure::num с фактическим количеством кубиков.
// Проверка запускается через переменную окружения MATRIS_TEST_FIGURE_NUM_SYNC=1.
bool testFigureNumSync()
{
	Round &round = Round::getInstance();

	round.reset();
	round.setGlass(10, 15);

	for(int i = 0; i < 100; ++i)
	{
		Figure fig;
		const int realCount = static_cast<int>(fig.getCubes().size());

		if(fig.getNum() != realCount)
			return false;
	}

	return true;
}

// Функция определения необходимости запуска теста
bool needRunFigureNumSyncTest()
{
	char *envValue = nullptr;
	size_t envValueLen = 0;

	if(_dupenv_s(&envValue, &envValueLen, "MATRIS_TEST_FIGURE_NUM_SYNC") != 0 || envValue == nullptr)
		return false;

	const bool needRun = (envValue[0] == '1');
	free(envValue);
	return needRun;
}
////_______________________________________________________________________________________________________

int main()
{
	if(needRunFigureNumSyncTest())
	{
		const bool testOk = testFigureNumSync();
		std::cout << (testOk ? "TEST Figure::num sync: OK" : "TEST Figure::num sync: FAIL") << std::endl;
		return testOk ? 0 : 1;
	}

    Round &round = Round::getInstance(); // получаем раунд

	round.reset(); // инициализируем раунд

	round.setGlass(10, 15); // размер стакана

    IRender *render;
    render = new(CRender);

    render->Init();

    render->DrawGlass();

    // Фигура
    Figure fig;

    render->DrawFigure(fig);

    //________________________________________________________________
    int i = _getch();
	return 0;
}

//А еще палка вся может провалиться и провзаимодействовать со слоями
//
//Правила раунда включают в себя диапазон чисел и правила по которому производится вычисление а также размеры стакана скорость падения, правила раскраски кубиков, бонусы
//
//Настройка случайного генератора для игры.
//
//Нужно реализовать интерфейс
//Такт перерисовки
//
//Структура классов ?
//
//Возможность пользователю самому вводить правила!
//
//Кубик
//- число
//- поззиция в палке или в матрице
//- виден / не виден
//Палка
//- id кубиков
//- порядок
//Слои внизу
//- матрица всего стакана - id кубиков или указатели
//
//Для данного раунда игры
//- размеры стакана
//- скорость падения
//- разрядность чисел
//- правило
//- количество палок
//
//
//Создание палки
//Движение палки
//Удаление палки - переход в матрицу слоев
//Создание кубика
//Удаление кубика.
//
//
//Можно даже так :
//Есть внизу один(два, три) ряда.
//Генерируются по одному кубику
//Есть либо общее правило на раунд, либо на каждый новый кубик - свое правило
//При этом кубик может быть либо совсем случайным, либо имеющим ответку внизу.
//_____________________________________________
