#pragma once
// file: cube_rules.h

// ѕравила дл€ Cube

#include "rules.h"

// --- √енераторы типов кубиков:

// обычный числовой кубик (0)
int genType0(void* param = nullptr);

// --- √енераторы цвета кубика:

// белый
RGBcolor genWhiteColor(void* param = nullptr);

// случайный светлый
RGBcolor genLightColor(void* param = nullptr);

// --- √енераторы чисел в кубике:

//! 0-9 - диапазон - можно в параметры! (либо nullptr, либо Point (пара)) 
//! но адрес константы или пары мы сможем передать?????
int genNum0_9(void* param = nullptr);

// 1-9
int genNum1_9(void* param = nullptr);
