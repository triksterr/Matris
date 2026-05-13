# Task Naming Rules

## Назначение

Файл определяет:
- naming conventions;
- task lifecycle naming;
- task file structure;
- task identifiers.

Цель:
- deterministic navigation;
- predictable task loading;
- bounded operational context.

---

# Task ID Format

Формат:
TASK-XXXX

Примеры:
- TASK-0010
- TASK-0011
- TASK-0100

---

## Number Allocation Policy

- TASK-0001...0099:
  current stage operational tasks

- TASK-0100...0999:
  future stage tasks

- TASK-1000+:
  reserved for large future expansions
  
---

# Task File Naming

Формат файла:
TASK-XXXX-short-name.md

Примеры:
- TASK-0010-figure-rotation.md
- TASK-0014-layers-nullptr-guards.md
- TASK-0016-remove-cube-copies.md

---

# Naming Rules

Имя должно:
- быть коротким;
- быть deterministic;
- отражать subsystem/goal;
- использовать kebab-case.

Избегать:
- длинных имен;
- vague names;
- generic words без смысла.

Запрещено:
- temp-task.md
- fix.md
- misc-fix.md
- test2.md
- vague abbreviations без established meaning.

---

# Recommended Structure

Рекомендуемая структура:
TASK-XXXX-subsystem-action.md

Примеры:
- TASK-0021-round-gravity-fix.md
- TASK-0030-console-input-loop.md

---

## Preferred Naming Semantics

Предпочитать:
- subsystem-first naming;
- action-oriented naming;
- deterministic wording.

Примеры:
- TASK-0021-layers-gravity-fix.md
- TASK-0022-figure-rotation-validation.md

---

# Task Lifecycle

## READY

Task:
- определена;
- имеет bounded scope;
- готова к execution.

---

## IN_PROGRESS

Task:
- активна;
- является current execution task.

Одновременно:
- только одна active task.

---

## BLOCKED

Task:
- требует external decision;
- требует architecture approval;
- зависит от другой task.

---

## DONE

Task:
- implementation completed;
- verification completed;
- history appended.

---

# Task File Lifecycle

После создания task file:
1. task becomes operational context;
2. relevant subsystem files loaded;
3. relevant source files loaded;
4. execution starts.

После completion:
- task file сохраняется;
- history append выполняется;
- active task moves out of execution focus.

---

# Mutation Scope Rule

Каждый task file должен содержать:
- explicit mutation scope;
- explicit source file list;
- explicit verification steps.

---

# Recommended Granularity

Предпочитать:
- one subsystem;
- one feature;
- one bugfix;
- one stabilization target.

Избегать:
- multi-subsystem refactoring;
- broad architecture rewrites;
- mixed unrelated goals.

---

# Context Loading Rule

Во время task execution:
не загружать:
- unrelated tasks;
- entire backlog;
- unrelated subsystem docs.

---

# History Link Rule

Каждая completed task:
- должна иметь history record;
- может иметь ADR reference;
- может иметь related risk references.

---

# Human Reviewability

Task должна:
- быть reviewable;
- иметь bounded diff;
- иметь understandable intent;
- быть locally verifiable.

---

# AI Workflow Goal

Task structure должна:
- минимизировать token usage;
- минимизировать context reload;
- поддерживать deterministic execution;
- поддерживать scalable AI-assisted development.
