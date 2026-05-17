# Task Execution Checklist

## Purpose

Checklist используется для:
- deterministic execution;
- bounded task handling;
- mutation discipline;
- verification discipline.

---

## Usage Rule

Checklist:
- НЕ заменяет workflow policies;
- НЕ заменяет task files;
- используется как operational execution checklist.

---

## Перед началом задачи

- определить task scope;
- определить subsystem scope;
- загрузить только relevant contexts;
- загрузить только relevant source files;
- определить mutation boundaries;
- определить verification scope.

---

## Перед изменением кода

- проверить ownership/lifecycle implications;
- проверить invariants;
- проверить dependencies;
- проверить build impact;
- проверить pointer safety.

---

## Во время изменения

- делать minimal mutations;
- избегать unrelated edits;
- избегать speculative refactoring;
- сохранять deterministic behavior;
- сохранять reviewability diff;
- не расширять mutation scope uncontrolled;
- не выполнять nearby cleanup без необходимости.

---

## После изменения

- выполнить build verification;
- выполнить relevant tests;
- выполнить runtime verification;
- проверить affected behavior;
- проверить regressions в task scope.

---

## При обнаружении проблем

- остановить uncontrolled mutations;
- локализовать failure scope;
- reload relevant context при необходимости;
- не выполнять speculative fixes.

---

## Перед завершением задачи

- убедиться что scope не расширился;
- убедиться что build стабилен;
- убедиться что verification выполнен;
- подготовить блок `Manual Check For USER` с шагами ручной проверки;
- подготовить блок `Manual Check Accents` с дополнительными действиями и зонами внимания;
- обновить history/task results;
- зафиксировать known issues.

---

## Запрещено

- silently rewrite architecture;
- silently expand scope;
- rewrite unrelated code;
- rewrite history;
- выполнять mass refactoring;
- загружать unnecessary context.

---

## Основной workflow principle

subsystem-first
+
task-oriented
+
bounded context
+
minimal mutation
+
human governance

Checklist должен:
- оставаться compact;
- быстро читаться;
- использоваться как quick operational reference.

