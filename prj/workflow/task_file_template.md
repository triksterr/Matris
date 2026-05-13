# Task File Template

## Template Purpose

Шаблон используется для:
- bounded task execution;
- deterministic task lifecycle;
- task-scoped context loading;
- controllable mutations.

---

## Authority

Task file authoritative для:
- task scope;
- mutation boundaries;
- verification scope;
- completion criteria.

Source code authoritative для implementation details.

---

## Task ID

[TASK-XXXX]

---

## Title

Краткое название задачи.

---

## Status

TODO / IN_PROGRESS / BLOCKED / DONE

---

## Context Budget

SMALL | MEDIUM | LARGE

Target:
SMALL

LARGE tasks should preferably be decomposed into smaller bounded tasks.

---

## Priority

P0 / P1 / P2

---

## Stage

Например:
WIN_CONSOLE_V1

---

## Goal

Что должно быть достигнуто.

Только task-scoped цель.

---

## Task Scope

Scope должен оставаться:
- bounded;
- reviewable;
- locally verifiable.

Что входит в задачу:
- ...
- ...
- ...

Что НЕ входит:
- ...
- ...
- ...

---

## Subsystem

Основная subsystem:
- ...

Связанные subsystem:
- ...

---

## Relevant Context Files

Загружать только:
- task-relevant contexts;
- task-relevant subsystem files;
- minimal required workflow files.

---

## Relevant Source Files

Основные source files:
- ...
- ...

Дополнительные:
- ...
- ...

---

## Allowed Mutation Scope

Разрешено изменять:
- ...
- ...
- ...

Без approval нельзя изменять:
- ...
- ...
- ...

---

## Ownership / Lifecycle Notes

Task-specific ownership notes:
- ...
- ...
- ...

---

## Invariants

Инварианты, которые нельзя нарушать:
- ...
- ...
- ...

---

## Required Verification

Обязательные проверки:
- build;
- unit tests;
- runtime verification;
- smoke verification.

---

## Test Scope

Что тестируется:
- ...
- ...
- ...

Что НЕ тестируется:
- ...
- ...

---

## Risks

Известные риски:
- ...
- ...
- ...

---

## Dependencies

Task dependencies:
- ...
- ...

---

## Blockers

Текущие blockers:
- ...
- ...

---

## Expected Result

Ожидаемый observable result:
- ...
- ...
- ...

---

## Completion Criteria

Task считается завершенной только если:
- build проходит;
- tests проходят;
- runtime behavior корректен;
- verification выполнен;
- history обновлен.

---

## Completion Actions

After successful completion:
- update active_tasks.md
- update backlog.md if required
- append history record
- archive completed task file

---

## History Records

Связанные history records:
- ...
- ...

---

## Reporting

Required:
- concise mutation summary
- concise verification summary
- detected risks/issues if present

Avoid:
- long prose
- unrelated explanations
- duplicated workflow descriptions

---

## History Update

After successful completion:
- append history record
- follow append-only policy
- do not rewrite previous history entries

If task blocked:
- append blocking record if required

---

## Escalation Conditions

Требуется escalation к USER если:
- нужен architecture change;
- нужен scope expansion;
- нарушаются subsystem invariants;
- требуется large refactoring.

---

## Notes

Короткие operational notes.

Без больших prose-блоков.

Task file должен:
- оставаться compact;
- быть operational;
- не превращаться в long-form documentation.
