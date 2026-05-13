# TASK-0011 — Figure Num Synchronization

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

Стабилизировать lifecycle поля `Figure::num` и синхронизировать его с `cubes.size()`.

Только task-scoped цель.

---

## Task Scope

Scope должен оставаться:
- bounded;
- reviewable;
- locally verifiable.

Что входит в задачу:
- найти все точки инициализации и изменения `Figure::num`;
- обеспечить согласованность `num` с фактическим количеством кубиков в `cubes`;
- устранить рассинхронизацию в конструкторе и связанных методах `Figure`.
- создать тест, проверяющий соответствие `Figure::num` и реального количества кубиков в фигуре.

Что НЕ входит:
- изменение rotation/move/collision логики;
- изменение ownership model;
- изменения в `Layers`, `Round Rules`, `Platform`.

---

## Subsystem

Основная subsystem:
- entity_figure

Связанные subsystem:
- entity_cube

---

## Relevant Context Files

Загружать только:
- `prj/subsystems/entity_figure.md`
- `prj/runtime/current_stage.md`
- `prj/workflow/task_execution.md`
- `prj/workflow/testing.md`

---

## Relevant Source Files

Основные source files:
- `cons_test/figure.h`

Дополнительные:
- `cons_test/cube.h` (только для контрактов контейнера кубиков)

---

## Allowed Mutation Scope

Разрешено изменять:
- поле `num` и связанную с ним логику внутри `Figure`;
- локальные вычисления/присваивания, касающиеся количества кубиков;
- минимальные task-scoped корректировки комментариев при необходимости.

Без approval нельзя изменять:
- API других подсистем;
- логику `Rules`, `Layers`, `Round`;
- архитектуру хранения кубиков.

---

## Ownership / Lifecycle Notes

Task-specific ownership notes:
- `Figure` владеет активными кубиками;
- `num` является производным lifecycle-полем от фактического состава `cubes`;
- любые изменения не должны нарушать deterministic lifecycle `Figure`.

---

## Invariants

Инварианты, которые нельзя нарушать:
- `num` согласован с `cubes.size()` после всех релевантных операций;
- поведение `Figure` для valid game-state остается deterministic;
- отсутствие side effects вне Figure subsystem.

---

## Required Verification

Обязательные проверки:
- build verification (Debug|x64);
- targeted review всех мест чтения/записи `num`;
- проверка корректности значений `num` после создания фигуры.
- запуск нового теста на соответствие `num == cubes.size()`.

---

## Test Scope

Что тестируется:
- корректная инициализация `num` в конструкторе `Figure`;
- согласованность `num` и `cubes.size()` в доступных lifecycle-точках;
- отсутствие компиляционных/интерфейсных регрессий.
- отдельный regression-тест: `Figure::getNum()` соответствует фактическому количеству элементов `getCubes()`.

Что НЕ тестируется:
- full gameplay regression;
- rotation/collision edge-cases.

---

## Risks

Известные риски:
- пропуск одной из точек изменения состава `cubes`;
- неявная зависимость внешнего кода от текущего неконсистентного `num`;
- частичная фиксация без покрытия всех lifecycle-paths.

---

## Dependencies

Task dependencies:
- `subsystems/entity_figure.md` invariants;
- текущая реализация `Figure` в `cons_test/figure.h`.

---

## Blockers

Текущие blockers:
- none

---

## Expected Result

Ожидаемый observable result:
- `Figure::num` стабильно отражает фактическое количество кубиков;
- добавлен и выполняется тест на соответствие `num` и фактического размера вектора кубиков;
- build проходит;
- mutation scope остается в пределах `entity_figure`.

---

## Completion Criteria

Task считается завершенной только если:
- `num` синхронизирован с `cubes.size()`;
- добавлен тест на проверку соответствия `num` и `cubes.size()`;
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
- требуется выход за `entity_figure` subsystem.

---

## Notes

Task file должен оставаться compact и operational.
