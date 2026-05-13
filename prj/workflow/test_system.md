# Test System

## Purpose

Файл фиксирует практические правила работы с системой unit-тестов.

---

## Framework

- GoogleTest (gtest)
- dependency manager: vcpkg

---

## Repository Structure

- solution: `matris.sln`
- production project: `cons_test`
- test project: `matris_tests`
- test sources: `matris/test/*.cpp`

---

## Mandatory Rules

- Новые unit-тесты добавлять только в `matris_tests`.
- Не добавлять test-only runtime branches в `cons_test.cpp`.
- Каждый bugfix по core logic по возможности покрывать regression-тестом.
- Тесты должны быть deterministic и повторяемыми.

---

## Build / Run

Install:
- `C:\Users\Alex\Documents\prog\vcpkg\vcpkg.exe install gtest:x64-windows`

Build:
- `MSBuild test\matris_tests.vcxproj /p:Configuration=Debug /p:Platform=x64`

Run:
- `x64\Debug\matris_tests.exe --gtest_color=no`

---

## Scope Discipline

- Тесты не должны требовать ручной ввод.
- Тесты не должны зависеть от rendering output.
- Тесты не должны ломать production startup flow.

---

## Current Baseline Test

- `FigureNumSync.MatchesCubeVectorSizeAfterConstruction`
