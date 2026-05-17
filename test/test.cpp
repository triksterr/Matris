// file: test.cpp

#include <gtest/gtest.h>
//#include <gmock/gmock.h> - после включения сразу 137 ошибок

// Простейший тест для проверки GTest
TEST(BasicTestForGtest, SanityCheck)
{
    EXPECT_TRUE(true);
    EXPECT_EQ(1 + 1, 2);
}

// Тест с использованием простых assert'ов
TEST(BasicTestForGtest, ArithmeticOperations)
{
    int a = 5;
    int b = 3;

    EXPECT_EQ(a + b, 8);
    EXPECT_GT(a, b);
    EXPECT_LT(b, a);
    EXPECT_NE(a, b);
}

////_______________________________________________________________________

//! Не работает gmock!!!
//#include <gmock/gmock.h> - после включения сразу 137 ошибок
// при включённом в свойствах проекта:
// Zc : preprocessor
// permissive -
// C++17 +
// Visual Studio 2022 (v143)
// Windows SDK 10.0.26100
// Link:test.cpp#L76

//! Для восстановления надо сначала сохранить все настройки!

//// Простейший mock класс для проверки GMock
//class MockCalculator 
//{
//public:
//    MOCK_METHOD(int, Add, (int a, int b));
//    MOCK_METHOD(int, Subtract, (int a, int b));
//};
//
//// Тест с использованием GMock
//TEST(MockTest, CalculatorMock)
//{
//    MockCalculator mockCalc;
//
//    EXPECT_CALL(mockCalc, Add(2, 3))
//        .WillOnce(testing::Return(5));
//
//    EXPECT_EQ(mockCalc.Add(2, 3), 5);
//}
//
//class IService
//{
//public:
//    virtual ~IService() = default;
//
//    virtual int Sum(int a, int b) = 0;
//};
//
//class MockService : public IService
//{
//public:
//    MOCK_METHOD(int, Sum, (int a, int b), (override));
//};
//
//TEST(MockTest, Basic)
//{
//    MockService mock;
//
//    EXPECT_CALL(mock, Sum(1, 2))
//        .WillOnce(testing::Return(3));
//
//    EXPECT_EQ(mock.Sum(1, 2), 3);
//}



//Тогда уже похоже не на GMock, а на конфликт / поломку toolchain или include environment.
//
//Ключевой симптом :
//
//```text
//gmock - internal - utils.h(...) : ElemFromList
//```
//
//при включённом :
//
//*`/Zc : preprocessor`
//* `/permissive - `
//* C++17 +
//
//обычно возникает ещё в двух случаях :
//
//---
//
//# 1. Повреждён / сломался include path STL / MSVC
//
//GoogleMock активно использует :
//
//*`<tuple > `
//* `<type_traits > `
//* `<utility > `
//* variadic templates
//
//Если VS подтягивает не тот STL — появляются сотни ошибок внутри gmock.
//
//-- -
//
//# 2. Проект компилируется не MSVC compiler'ом
//
//Очень часто :
//
//*clang - cl
//* Intel compiler
//* старый SDK
//
//-- -
//
//# Что проверить сейчас
//
//## A.Какой compiler реально используется
//
//В Build Output должна быть строка типа :
//
//```text
//cl.exe / c ...
//```
//
//или:
//
//```text
//clang - cl.exe
//```
//
//Если `clang-cl` —
//это очень вероятная причина.
//
//-- -
//
//# B.Минимальный isolated test
//
//Создай НОВЫЙ проект :
//
//```text
//Console App
//```
//
//без:
//
//*старых props
//* cmake
//* custom include dirs
//* shared property sheets
//
//И вставь только :
//
//```cpp
//#include <gmock/gmock.h>
//
//int main()
//{
//    return 0;
//}
//```
//
//-- -
//
//# C.Подключи GTest правильно через vcpkg
//
//В новом проекте НЕ добавляй include вручную.
//
//Вообще убери :
//
//```text
//Additional Include Directories
//```
//
//с путями vcpkg.
//
//Используй только :
//
//```bash
//vcpkg integrate install
//```
//
//-- -
//
//# D.Очень важно : убери ручные include path
//
//Сейчас у тебя почти наверняка есть :
//
//```text
//C : \Users\Alex\Documents\prog\vcpkg\installed\x64 - windows\include
//```
//
//в:
//
//```text
//Additional Include Directories
//```
//
//ЭТО НЕ НУЖНО при `vcpkg integrate install`.
//
//И иногда ломает порядок include / STL.
//
//Удалить полностью.
//
//-- -
//
//# E.Проверь toolset
//
//Нужно :
//
//```text
//Platform Toolset = v143
//```
//
//-- -
//
//# F.Проверь Windows SDK
//
//Нормально :
//
//*10.0.22621 +
//*10.0.26100 +
//
//-- -
//
//# G.Попробуй include order
//
//Иногда MSVC / gmock ломается если включать только gmock.
//
//Попробуй:
//
//```cpp
//#include <tuple>
//#include <type_traits>
//#include <gtest/gtest.h>
//#include <gmock/gmock.h>
//
//int main()
//{
//}
//```
//
//-- -
//
//# H.Если не поможет — почти гарантирован broken VS installation
//
//Тогда :
//
//*Visual Studio Installer
//* Repair
//
//особенно :
//
//*MSVC v143 build tools
//* Windows SDK
//* C++ ATL / MFC(иногда влияет)
//* CMake tools
//
//-- -
//
//# Самое подозрительное сейчас
//
//С высокой вероятностью у тебя :
//
//* ручные include paths из vcpkg,
//* плюс интеграция vcpkg,
//* и MSVC смешивает headers.
//
//Это очень типично для лавины ошибок внутри gmock templates.
//
//! Начни именно с :
//
//1. удалить manual include dirs,
//2. новый чистый console project,
//3. только `vcpkg integrate install`.
