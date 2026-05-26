# Backlog

## Authority

Medium-authority planning and backlog management file.

---

## Active Stage

WIN_CONSOLE_V1

---

## Priority Model

- P0 - critical/blocking
- P1 - important current-stage
- P2 - deferred/future-stage

---

## Current Backlog

## CORE

### P0

- [DONE] TASK-0001 - Реализовать каркас Figure (данные, конструктор, базовые операции)
- TASK-0003 - Реализовать минимальный Round loop (spawn -> move -> lock -> cleanup)
- TASK-0004 - Реализовать минимальный Game loop (инициализация и последовательность раундов)

---

## ROUND LOGIC

### P1

- TASK-0002 - Проверки границ и коллизий (cube/figure/layers)
- TASK-0005 - Поворот Figure + валидация после поворота
- TASK-0006 - Переход Figure -> Layers (без утечек и double delete)
- TASK-0007 - Минимальные правила удаления в слоях + стабилизация

---

## PLATFORM

### P1

- TASK-0008 - Минимальный консольный ввод/вывод для debug-прогона цикла
- TASK-0009 - Проверить вывод состояния игры и диагностических сообщений

---

## DOCUMENTATION / WORKFLOW

### P1

- TASK-0010 - Поддерживать task-файлы и backlog в актуальном состоянии
- TASK-0011 - Минимизировать workflow: единый формат статусов, проверок и отчетов

---

## TESTING

### P1

- TASK-0012 - Smoke-сценарии на базовый цикл (spawn/fall/lock/destroy)

---

## Deferred

- Пентамино beyond текущего минимального ядра
- Вариативные правила сравнения кубиков (только число / число+цвет)
- Динамическое изменение размеров стакана между раундами

---

## Backlog Rules

- Backlog не является execution history.
- Детали реализации хранятся в task-файлах.
- В ACTIVE одновременно переводится только одна задача без отдельного согласования.