# Subsystem Index

## Назначение

Файл:
- описывает subsystem map проекта;
- определяет boundaries подсистем;
- определяет ownership responsibility;
- определяет связи между subsystem contexts.

---

## Architectural Role

Subsystem Index:
- navigation layer;
- subsystem discovery entry point;
- lightweight architecture routing document.

Файл НЕ является:
- полной architecture documentation;
- operational task context;
- detailed subsystem specification.

---

# Dependency Direction Rules

Допустимые направления:

platform
    ->
game loop
    ->
round rules
    ->
figure/layers
    ->
cube

Недопустимо:
- reverse gameplay dependencies;
- platform leakage into gameplay core;
- circular subsystem dependencies.

---

# Recommended Loading Priority

При gameplay task:

1. subsystem_index.md
2. relevant subsystem doc
3. task file
4. relevant source files

Не загружать:
- unrelated subsystem docs;
- entire subsystem layer.

---

# Subsystem Authority Model

Subsystem docs:
- authoritative для invariants;
- authoritative для ownership semantics;
- authoritative для subsystem boundaries.

Source code:
- authoritative implementation source.

---

# Core Gameplay Layer

## entity_cube.md

Ответственность:
- модель кубика;
- состояние кубика;
- координаты;
- числовые значения;
- базовые invariants Cube.

Связанные source files:
- cube.h
- cube.cpp

---

## entity_figure.md

Ответственность:
- модель фигуры;
- rotation logic;
- movement logic;
- ownership кубиков;
- lifecycle Figure.

Связанные source files:
- figure.h
- figure.cpp

Зависимости:
- entity_cube.md
- layers.md

---

## layers.md

Ответственность:
- матрица стакана;
- хранение fixed cubes;
- collision support;
- coordinate lookup;
- ownership rules для stored cubes.

Связанные source files:
- layers.h
- layers.cpp

Зависимости:
- entity_cube.md

---

## round_rules.md

Ответственность:
- gravity rules;
- destruction rules;
- stabilization cycle;
- round parameters;
- rule execution order.

Связанные source files:
- rules.h
- rules.cpp
- round.h
- round.cpp

Зависимости:
- entity_cube.md
- entity_figure.md
- layers.md

---

## game_loop.md

Ответственность:
- frame/update loop;
- timing;
- round lifecycle;
- game state transitions;
- spawn/update/fixation sequence.

Связанные source files:
- game loop related files
- round control files

Зависимости:
- entity_figure.md
- layers.md
- round_rules.md
- platform_console.md

---

# Platform Layer

## platform_console.md

Ответственность:
- console rendering;
- console input;
- Windows console specifics;
- platform adapters.

Связанные source files:
- c_render.h
- c_render.cpp
- console-specific files

Связанные interfaces:
- IRender
- IInput

---

# Interface Layer

## Render Interfaces

Ответственность:
- rendering abstraction;
- platform-independent rendering API.

Основные интерфейсы:
- IRender

---

## Input Interfaces

Ответственность:
- input abstraction;
- keyboard/mouse abstraction.

Основные интерфейсы:
- IInput

---

## Audio Interfaces

Ответственность:
- audio abstraction;
- sound playback abstraction.

Основные интерфейсы:
- IAudio

---

## File Interfaces

Ответственность:
- filesystem abstraction;
- save/load abstraction.

Основные интерфейсы:
- IFiles

---

# Workflow Rules

Каждая subsystem doc:
- описывает invariants;
- описывает ownership;
- описывает lifecycle;
- не дублирует implementation details.

---

# Context Loading Rules

При работе:
1. определить subsystem;
2. загрузить subsystem doc;
3. загрузить task file;
4. загрузить только relevant source files.

---

# Scaling Rules

Новые subsystems:
- добавляются incremental;
- должны иметь bounded responsibility;
- должны иметь explicit ownership boundaries.

---

# Current Active Stage

Текущий активный этап:
WIN_CONSOLE_V1

Основной focus:
- gameplay core;
- console platform layer;
- deterministic stabilization ядра.

---

# Future Subsystem Policy

Новые subsystems должны:
- иметь bounded responsibility;
- иметь explicit ownership boundaries;
- иметь deterministic interaction model;
- избегать speculative abstraction.

---

# Known Risks

- subsystem boundary drift;
- circular dependency growth;
- platform leakage into gameplay core;
- duplicated responsibilities;
- oversized subsystem contexts.
