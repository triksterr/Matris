// file: rules_test.cpp

#include <iostream>
#include <random>
#include <cstdint>

// RNG

// Обычный генератор случайных чисел.
// В реальном проекте можно заменить на:
// pcg32
// xoroshiro
// splitmix64
// и т.д.
using RNG = std::mt19937;

// RULE CONTEXT

// Контекст, передаваемый правилам.
//
// Здесь может быть:
//
// - RNG
// - global config
// - references на другие системы
// - difficulty
// - environment
// - profiler
//
struct RuleContext
{
    RNG& rng;
};

// RULE FUNCTION TYPE
// Универсальный тип функции-правила, возвращающий int.
// @param void* userdata - Указатель на данные правила.
// @param RuleContext& - Контекст выполнения.
// @return сгенерированное значение.
using iRuleFn = int(*)(void*, RuleContext&);

//using testRuleFn = int(*)(void*); // fn - возвращающий int, при этом можно передать указатель на параметры, которые могут быть любого типа, например, Point {min, max}

// Универсальный тип функции-правила, возвращающий bool.
//using bRuleFn = bool(*)(void*, RuleContext&);

// Универсальный тип функции-правила, возвращающий float.
//using fRuleFn = float(*)(void*, RuleContext&);

// Универсальный тип функции-правила, возвращающий RGBcolor.
//using cRuleFn = RGBcolor(*)(void*, RuleContext&);

// Универсальный тип функции-правила, возвращающий Point.
//using cRuleFn = Point(*)(void*, RuleContext&);

// Универсальный тип функции-правила, возвращающий string.
//using sRuleFn = std::string(*)(void*, RuleContext&);

// RULE METADATA
// Descriptor правила.
// Это и есть:
// DATA + FUNCTION POINTER + METADATA
struct RuleDesc
{
    // Человекочитаемое имя правила.
    const char* name;

    // Указатель на исполняемую функцию.
    iRuleFn fn;

    // Данные правила.
    //
    // Например:
    // диапазоны
    // веса
    // параметры генерации
    //
    void* userdata;
};

// RULE EXECUTION
// Унифицированный вызов любого правила. (Cube вообще не знает, какая конкретно логика находится внутри)
// @param RuleDesc& - Правило, которое нужно выполнить
// @param RuleContext& - Контекст выполнения правила
// @return сгенерированное значение
int executeRule(const RuleDesc& rule, RuleContext& ctx)
{
    return rule.fn(rule.userdata, ctx);
}

// NUMBER RULES
namespace number_rules
{
    // RULE DATA
 
    // Данные правила генерации числа.
    struct RangeData
    {
        int min;
        int max;
    };

    // RULE IMPLEMENTATION
 
    // Генерация случайного числа в диапазоне.
    // userdata -> RangeData
    int random_range(
        void* userdata,
        RuleContext& ctx)
    {
        auto* data =
            static_cast<RangeData*>(userdata);

        std::uniform_int_distribution<int> dist(
            data->min,
            data->max);

        int value = dist(ctx.rng);

        // Проверка результата.
        //
        // Правило полностью отвечает
        // за корректность результата.

        if(value < data->min)
            value = data->min;

        if(value > data->max)
            value = data->max;

        return value;
    }

    // ANOTHER RULE
 
    // Генерация только чётных чисел.
    int random_even(
        void* userdata,
        RuleContext& ctx)
    {
        auto* data = static_cast<RangeData*>(userdata);

        std::uniform_int_distribution<int> dist(data->min / 2, data->max / 2);

        return dist(ctx.rng) * 2;
    }
}


// COLOR RULES
namespace color_rules
{
 
    // RULE DATA

    struct ColorData
    {
        int minColor;
        int maxColor;
    };

    // RULE IMPLEMENTATION
 
    // Случайный цвет.
    int random_color(void* userdata, RuleContext& ctx)
    {
        auto* data = static_cast<ColorData*>(userdata);

        std::uniform_int_distribution<int> dist(data->minColor, data->maxColor);

        return dist(ctx.rng);
    }

    // Только "тёплые" цвета - Просто пример другой логики
    int warm_color(void*, RuleContext& ctx)
    {
        // Набор допустимых цветов.
        static const int colors[] =
        {
            1,
            2,
            3,
            7,
            8,
            12
        };

        std::uniform_int_distribution<int> dist(0, 5);

        return colors[dist(ctx.rng)];
    }
}


// CUBE
class Cube
{
public:
    int number;
    int color;

    // CONSTRUCTOR
    // Cube получает descriptors правил.
    Cube(RuleContext& ctx, const RuleDesc& numberRule, const RuleDesc& colorRule)
    {
        // Генерация значений через правила.
        number = executeRule(numberRule, ctx);
        color = executeRule(colorRule, ctx);
    }
};

////_______________________________________________________________________________________ 


int main()
{
    // RNG
    RNG rng(std::random_device {}());

    RuleContext ctx { rng };

    // RULE DATA

    // Число: 0..9
    number_rules::RangeData digitRange
    {
        0,
        9
    };

    // Цвет: 0..16
    color_rules::ColorData colorRange
    {
        0,
        16
    };

    // RULE DESCRIPTORS

    RuleDesc numberRule
    {
        "random digit",
        number_rules::random_range,
        &digitRange
    };

    RuleDesc colorRule
    {
        "random color",
        color_rules::random_color,
        &colorRange
    };

    // CREATE CUBE
    Cube cube(ctx, numberRule, colorRule);
 
    // OUTPUT
    std::cout << "Cube generated:\n";
    std::cout << "number = " << cube.number << "\n";
    std::cout << "color = " << cube.color << "\n";

    // Теперь используем ДРУГОЕ правило числа.
    // Cube менять не нужно вообще.

    RuleDesc evenNumberRule
    {
        "even numbers",
        number_rules::random_even,
        &digitRange
    };

    RuleDesc warmColorRule
    {
        "warm colors",
        color_rules::warm_color,
        nullptr
    };

    Cube cube2(ctx, evenNumberRule, warmColorRule);

    std::cout << "\nCube2 generated:\n";     
    std::cout << "number = " << cube2.number << "\n";
    std::cout << "color = " << cube2.color << "\n";
}
