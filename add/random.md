Для генерации случайных чисел с **диагональным распределением** (обычно подразумевается линейное убывание вероятности от центра к краям), можно использовать несколько подходов. Вот основные варианты:

## 1. **Треугольное распределение** (простейший случай)

Самый простой способ - использовать сумму двух равномерных распределений:

```cpp
#include <iostream>
#include <random>
#include <cmath>

class DiagonalDistribution {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<double> dist;
    
public:
    DiagonalDistribution() : gen(std::random_device{}()), dist(0.0, 1.0) {}
    
    // Треугольное распределение на интервале [a, b]
    double triangular(double a, double b) {
        double u1 = dist(gen);
        double u2 = dist(gen);
        return a + (b - a) * (u1 + u2) / 2.0;
    }
    
    // Треугольное распределение с модой в центре
    double triangular_centered(double a, double b) {
        double u = dist(gen);
        double v = dist(gen);
        return a + (b - a) * (u + v) / 2.0;
    }
};
```

## 2. **Линейно убывающее распределение**

Более точная реализация с линейным убыванием плотности вероятности:

```cpp
#include <iostream>
#include <random>
#include <cmath>
#include <functional>

class LinearDecreasingDistribution {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<double> uniform;
    
public:
    LinearDecreasingDistribution() : gen(std::random_device{}()), uniform(0.0, 1.0) {}
    
    // Линейно убывающее распределение на [a, b] с максимумом в center
    double sample(double a, double b, double center) {
        // Нормализуем центр к диапазону [0, 1]
        double t = (center - a) / (b - a);
        
        // Генерируем случайную величину
        double u = uniform(gen);
        
        // Инвертируем функцию распределения для линейного убывания
        if (u < t) {
            return a + (center - a) * std::sqrt(u / t);
        } else {
            return center + (b - center) * (1 - std::sqrt((1 - u) / (1 - t)));
        }
    }
    
    // Симметричное линейное распределение (центр посередине)
    double symmetric_sample(double a, double b) {
        double center = (a + b) / 2.0;
        return sample(a, b, center);
    }
};
```

## 3. **Распределение "шапки" (еще один вариант)**

```cpp
#include <iostream>
#include <random>
#include <cmath>

class HatDistribution {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<double> uniform;
    
public:
    HatDistribution() : gen(std::random_device{}()), uniform(0.0, 1.0) {}
    
    // Распределение вида f(x) = 1 - |2x - 1| на [0, 1]
    double sample_unit() {
        double u = uniform(gen);
        double v = uniform(gen);
        
        // Метод отбора
        double x = uniform(gen);
        double y = uniform(gen) * 1.0; // максимальное значение плотности = 1
        
        // Принимаем точку, если она под кривой
        if (y <= (1.0 - std::abs(2.0 * x - 1.0))) {
            return x;
        }
        // Иначе пробуем снова (рекурсивно, лучше использовать цикл)
        return sample_unit();
    }
    
    // Масштабирование на произвольный интервал
    double sample(double a, double b) {
        return a + (b - a) * sample_unit();
    }
};
```

## 4. **Универсальная реализация с выбором формы**

```cpp
#include <iostream>
#include <random>
#include <cmath>
#include <functional>

class DiagonalRandomGenerator {
private:
    std::mt19937 gen;
    std::uniform_real_distribution<double> uniform;
    
public:
    DiagonalDistribution() : gen(std::random_device{}()), uniform(0.0, 1.0) {}
    
    // Метод обратного преобразования для линейной плотности
    double linearDensity(double a, double b, double peak) {
        // peak - точка максимума (от a до b)
        double u = uniform(gen);
        
        // Площади двух треугольников
        double area_left = (peak - a) / 2.0;
        double area_right = (b - peak) / 2.0;
        double total_area = area_left + area_right;
        
        // Нормализованная случайная величина
        double r = u * total_area;
        
        if (r <= area_left) {
            // Левая часть
            return a + std::sqrt(2.0 * r * (peak - a));
        } else {
            // Правая часть
            r -= area_left;
            return peak + (b - peak) - std::sqrt(2.0 * r * (b - peak));
        }
    }
    
    // Квадратичное распределение (более резкий спад)
    double quadraticDensity(double a, double b) {
        double u = uniform(gen);
        // f(x) = 1 - (2x-1)^2
        return 0.5 + std::sqrt(u) * (uniform(gen) > 0.5 ? 1.0 : -1.0) / 2.0;
    }
    
    // Экспоненциальное затухание от центра
    double exponentialDecay(double a, double b, double lambda) {
        double center = (a + b) / 2.0;
        double u = uniform(gen) * 2.0 - 1.0; // [-1, 1]
        
        // Экспоненциальное распределение с отражением
        double exponential = -std::log(1.0 - uniform(gen)) / lambda;
        double sign = u >= 0 ? 1.0 : -1.0;
        
        double result = center + sign * exponential * (b - a) / 2.0;
        
        // Ограничиваем диапазоном
        if (result < a) return a;
        if (result > b) return b;
        return result;
    }
};
```

## 5. **Пример использования**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

int main() {
    // Создаем генератор
    LinearDecreasingDistribution rng;
    
    // Генерируем выборку
    std::vector<double> samples;
    int n_samples = 10000;
    
    for (int i = 0; i < n_samples; ++i) {
        samples.push_back(rng.symmetric_sample(-1.0, 1.0));
    }
    
    // Анализируем распределение
    std::vector<int> histogram(20, 0);
    for (double val : samples) {
        int bin = static_cast<int>((val + 1.0) * 10); // [-1, 1] -> [0, 20]
        if (bin >= 0 && bin < 20) {
            histogram[bin]++;
        }
    }
    
    // Выводим гистограмму
    std::cout << "Гистограмма распределения:\n";
    for (int i = 0; i < 20; ++i) {
        std::cout << "Бин " << i << ": " << std::string(histogram[i] / 50, '*') << "\n";
    }
    
    // Сохраняем данные для построения графика
    std::ofstream file("distribution.csv");
    for (double val : samples) {
        file << val << "\n";
    }
    file.close();
    
    return 0;
}
```

## **Выбор реализации зависит от ваших потребностей:**

1. **Треугольное распределение** - самое простое и быстрое
2. **Линейно убывающее** - более точное соответствие "диагональному" распределению
3. **Метод отбора** - универсальный, но может быть медленнее
4. **Экспоненциальное затухание** - если нужен более резкий спад от центра

Для большинства задач подойдет `LinearDecreasingDistribution` или `DiagonalRandomGenerator::linearDensity()`.