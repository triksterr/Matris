# Subsystem Context Template

## Template Purpose

Шаблон используется для:
- subsystem architecture contexts;
- bounded subsystem loading;
- subsystem-oriented execution;
- deterministic repository scaling.

---

## Authority

Subsystem context authoritative для:
- subsystem boundaries;
- subsystem invariants;
- ownership model;
- subsystem responsibilities.

Source code authoritative для implementation details.

---

## Subsystem

[SUBSYSTEM_NAME]

---

## Purpose

Краткое назначение подсистемы.

Что subsystem делает.
Что subsystem НЕ делает.

---

## Responsibilities

Subsystem отвечает за:
- ...
- ...
- ...

Subsystem НЕ отвечает за:
- ...
- ...
- ...

---

## Architectural Role

Роль subsystem в общей архитектуре проекта.

Связь с:
- core;
- gameplay;
- rendering;
- input;
- filesystem;
- audio;
- tests.

---

## Core Invariants

Инварианты subsystem:
- ...
- ...
- ...

Инварианты не должны silently нарушаться.

---

## Ownership Model

Описание ownership:
- кто владеет объектами;
- кто создает;
- кто уничтожает;
- кто хранит raw pointers;
- lifecycle rules.

---

## Data Flow

Основной flow данных:
1. ...
2. ...
3. ...

---

## Public Interfaces

Основные public interfaces:
- ...
- ...
- ...

---

## Important Structures

Ключевые структуры:
- ...
- ...
- ...

---

## Lifecycle

Lifecycle объектов:
1. create
2. update
3. transfer
4. destroy

---

## Mutation Rules

Что можно изменять:
- ...

Что нельзя изменять без approval:
- ...

---

## Boundaries

Subsystem context должен:
- оставаться bounded;
- избегать unrelated architecture;
- избегать duplicated implementation details.

Subsystem boundaries:
- что входит;
- что не входит;
- соседние subsystem areas.

---

## Dependencies

Subsystem зависит от:
- ...

Subsystem НЕ должен зависеть от:
- ...

---

## Determinism Requirements

Что должно оставаться deterministic:
- ...
- ...
- ...

---

## Performance Notes

Только важные performance constraints.

Без premature optimization.

---

## Pointer/Reference Safety

Правила pointer/reference safety:
- ...
- ...
- ...

---

## Error Handling

Как subsystem обрабатывает ошибки:
- bool;
- enum;
- assertions;
- validation checks.

try/catch запрещены.

---

## Testing Strategy

Что тестируется:
- ...
- ...
- ...

Что НЕ тестируется:
- ...
- ...

---

## Verification Requirements

Минимальная verification strategy:
- build;
- unit tests;
- runtime checks;
- smoke checks.

---

## Known Risks

Известные риски:
- ...
- ...
- ...

---

## Future Evolution

Что допускается в будущем:
- ...
- ...

Что intentionally deferred:
- ...
- ...

---

## Related Files

Relevant files:
- source files;
- related headers;
- relevant tests;
- related subsystem docs.
- ...

---

## Related Tasks

Relevant task files:
- ...
- ...

---

## Context Loading Notes

При загрузке:
- предпочитать subsystem-first execution;
- загружать только task-relevant source files;
- избегать unrelated subsystem expansion.

---

## Notes

Дополнительные operational notes.

Без больших prose-блоков.

Subsystem context должен:
- оставаться concise;
- не превращаться в architecture encyclopedia;
- быть optimized для operational loading.
