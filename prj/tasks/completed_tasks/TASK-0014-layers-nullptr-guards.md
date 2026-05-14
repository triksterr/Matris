# TASK-0014 — Layers nullptr Guards

## Status

DONE

---

## Context Budget

SMALL

Target:
SMALL

LARGE tasks should preferably be decomposed into smaller bounded tasks.

---

## Priority

P0

---

## Stage

WIN_CONSOLE_V1

---

## Goal

Стабилизировать nullptr safety в методах Layers, принимающих указатели на Cube.

Только task-scoped цель.

---

## Task Scope

Scope должен оставаться:
- bounded;
- reviewable;
- locally verifiable.

Что входит в задачу:
- добавить nullptr guards в pointer-based методы Layers;
- предотвратить unsafe dereference при `Cube* == nullptr`;
- сохранить существующую семантику для валидных указателей.

Что НЕ входит:
- изменение ownership model;
- изменение Figure/Cube/Rules логики;
- рефакторинг API Layers вне nullptr safety.

---

## Subsystem

Основная subsystem:
- layers

Связанные subsystem:
- entity_cube

---

## Relevant Context Files

Загружать только:
- `prj/subsystems/layers.md`
- `prj/runtime/current_stage.md`
- `prj/workflow/task_execution.md`
- `prj/workflow/testing.md`

---

## Relevant Source Files

Основные source files:
- `cons_test/layers.h`

Дополнительные:
- `cons_test/cube.h` (только для сигнатур/контрактов)

---

## Allowed Mutation Scope

Разрешено изменять:
- pointer overload методы в `Layers`;
- локальные guard-checks на входные указатели;
- только task-scoped комментарии по неочевидной логике (при необходимости).

Без approval нельзя изменять:
- архитектуру хранения `std::vector<Cube*>`;
- публичные контракты других подсистем;
- unrelated методы и файлы.

---

## Ownership / Lifecycle Notes

Task-specific ownership notes:
- Layers хранит non-owning `Cube*`;
- nullptr является допустимым состоянием для пустых ячеек;
- методы не должны разыменовывать `Cube*` без валидации.

---

## Invariants

Инварианты, которые нельзя нарушать:
- deterministic occupancy behavior;
- existing bounds validation behavior;
- отсутствие side effects для валидных входных данных.

---

## Required Verification

Обязательные проверки:
- build verification (Debug|x64);
- targeted проверка nullptr-paths в измененных методах;
- regression-check сигнатур и существующих call-sites.

---

## Test Scope

Что тестируется:
- вызовы pointer-based методов Layers с `nullptr`;
- отсутствие крэша/UB из-за разыменования `nullptr`;
- сохранение текущего поведения для non-null указателей.

Что НЕ тестируется:
- full gameplay regression;
- round rules behavior.

---

## Risks

Известные риски:
- неполное покрытие всех pointer-based overloads;
- неявное изменение поведения return-value;
- скрытые зависимости call-sites от текущего undefined behavior.

---

## Dependencies

Task dependencies:
- `subsystems/layers.md` invariants;
- текущие сигнатуры `Cube`/`Layers`.

---

## Blockers

Текущие blockers:
- none

---

## Expected Result

Ожидаемый observable result:
- методы Layers с `Cube*` безопасно обрабатывают `nullptr`;
- build проходит;
- mutation scope остается локальным в пределах `layers`.

---

## Completion Criteria

Task считается завершенной только если:
- требуемые nullptr guards реализованы;
- build проходит;
- verification выполнен;
- history обновлен;
- task архивирован по workflow.

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
- to be appended after completion

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
- требуется выход за `layers` subsystem.

---

## Notes

Task file должен оставаться compact и operational.
