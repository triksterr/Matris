// file: test.cpp

#include <gtest/gtest.h>
//#include <gmock/gmock.h>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

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