# Backlog

## Authority

Medium-authority planning and backlog management file.

---

## Operational Role

Backlog является:
- planning layer;
- task reservoir;
- future execution source.

Backlog НЕ является:
- active execution context;
- architecture authority;
- detailed task specification.

---

## Назначение

Файл содержит:
- backlog задач этапа;
- задачи вне active execution;
- отложенные задачи;
- будущие subsystem tasks.

Файл НЕ является:
- execution log;
- history;
- architecture document.

History append-only хранится отдельно.

---

# Active Stage

WIN_CONSOLE_V1

---

# Priority Model

- P0 — critical/blocking
- P1 — important current-stage
- P2 — deferred/future-stage

---

# Current Backlog

## CORE

### P0

- TASK-0010
  Figure rotation/chkRotate stabilization

- TASK-0011 [DONE]
  Figure::num synchronization stabilization

- TASK-0012 [DONE]
  Cube default constructor stabilization

- TASK-0013
  IRender lifetime ownership stabilization

- TASK-0014 [DONE]
  Layers nullptr guard checks

- TASK-0015
  Cube copy operator unit tests

- TASK-0018 [DONE]
  rules.h self-contained includes stabilization

- TASK-0019
  Figure/Layers unique_ptr ownership + move transfer + copy elimination

---

## ROUND LOGIC

### P1

- TASK-0002
  Complete rotation logic

- TASK-0003
  Falling + lock delay

- TASK-0004
  Gravity + destroy rules

- TASK-0005
  Stabilization loop

---

## PLATFORM

### P1

- TASK-0006
  Minimal console + keyboard functionality

---

## TESTING

### P1

- TASK-0007 [DONE]
  GoogleTest coverage

- TASK-0008
  Manual QA workflow

---

# Deferred

Сюда переносятся:
- future-stage tasks;
- non-critical improvements;
- optimization tasks;
- speculative ideas после approval USER.

---

# Backlog Rules

Backlog:
- не является execution history;
- не содержит длинных обсуждений;
- не содержит detailed implementation notes.

Подробности:
- task files;
- subsystem contexts;
- history records.

---

# Backlog Hygiene

Backlog должен:
- оставаться compact;
- быть reviewable;
- минимизировать duplicated tasks;
- минимизировать obsolete entries.

---

# Workflow Rule

В execution:
- использовать bounded task scope;
- активировать только одну task;
- не загружать весь backlog без необходимости.

---

# Task Activation Policy

Перед переходом задачи в ACTIVE:
- создать bounded task file;
- определить subsystem scope;
- определить verification scope;
- freeze mutation boundaries.

---

# Backlog Scaling Goal

Backlog workflow должен:
- поддерживать predictable prioritization;
- поддерживать bounded execution planning;
- сохранять manageable operational complexity.

