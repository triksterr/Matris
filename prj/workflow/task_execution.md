# Политика выполнения задач

## Authority

High authority execution workflow policy.

Определяет:
- execution flow;
- task completion model;
- verification flow;
- execution boundaries.

---

## Основная цель

Каждая задача должна:
- переводить проект из одного рабочего состояния в другое рабочее состояние;
- иметь bounded scope;
- быть проверяемой;
- быть воспроизводимой.

---

## Основная модель работы

Workflow:
1. load context;
2. analyze task;
3. implement minimal change;
4. build;
5. run tests;
6. run manual verification;
7. append history;
8. update task state.

---

## Task-Oriented Execution

Current task file authoritative для:
- task scope;
- task boundaries;
- required verification;
- affected files.

Codex должен:
- работать только в рамках текущей задачи;
- избегать unrelated changes;
- избегать speculative redesign;
- избегать opportunistic refactoring.

---

## Minimal Mutation Policy

Предпочитать:
- small isolated edits;
- single-responsibility changes;
- minimal mutation scope.

Не изменять:
- unrelated files;
- neighboring subsystems;
- architecture layers

без необходимости.

Не выполнять:
- stylistic cleanup;
- formatting-only rewrites;
- normalization unrelated code.

---

## Working State Policy

После каждой задачи проект должен:
- собираться;
- запускаться;
- оставаться в рабочем состоянии.

Broken intermediate states нежелательны.

---

## Build Policy

Verification scope должен соответствовать:
- mutation scope;
- task scope;
- affected subsystem scope.

После изменений:
- выполнять build;
- проверять build output;
- фиксировать build problems.

Не игнорировать:
- compiler warnings;
- linker warnings;
- unstable behavior.

---

## Testing Policy

Тестирование выполняется раздельными этапами:
1. implementation;
2. unit tests;
3. build;
4. test execution;
5. manual verification.

Hybrid testing model используется по умолчанию.

---

## Manual Verification Policy

Даже при наличии unit tests:
- выполнять manual smoke verification;
- проверять runtime behavior;
- проверять gameplay invariants.

---

## Context Discipline

Во время выполнения задачи:
- не расширять scope;
- не загружать unrelated contexts;
- не переходить к следующей задаче преждевременно.

---

## User Governance

USER:
- утверждает архитектурные изменения;
- контролирует critical mutations;
- принимает завершение задачи.

Codex:
- предлагает изменения;
- реализует bounded tasks;
- не принимает архитектурные решения автономно.

---

## Result Recording Policy

После завершения задачи:
- append result в history;
- update task status;
- append correction records при необходимости.

Не переписывать прошлые записи.

---

## Task Completion Policy

Задача считается завершенной только если:
- код реализован;
- build успешен;
- tests выполнены;
- manual verification выполнен;
- result recorded.

---

## Task Completion Procedure

After successful completion:
1. Run required verification.
2. Append history record.
3. Update task status to DONE.
4. Remove task from active queue.
5. Update backlog if required.
6. Move completed task file from tasks/ to tasks/completed_tasks/.
7. Report concise operational summary.

---

## Task Archive Policy

Completed task files:
- should be removed from active task area;
- should be moved from tasks/ to tasks/completed_tasks/ after completion;
- should remain immutable after archival.

Archive:
- historical storage only;
- not operational execution context;
- not loaded by default.

Corrections:
- handled through history correction records;
- not through task file rewrites.

---

## Task Granularity Policy

Предпочтительный размер задачи:
- один метод;
- одна небольшая логическая правка;
- одна локальная подсистема.

Избегать:
- large refactoring;
- multi-subsystem mutations;
- oversized tasks.

---

## Failure Handling Policy

Если задача:
- блокируется;
- требует architecture change;
- требует scope expansion;

Codex должен:
1. остановить mutation;
2. описать проблему;
3. предложить варианты;
4. дождаться решения USER.

---

## Workflow Stability Goal

Execution workflow должен:
- оставаться deterministic;
- минимизировать context growth;
- минимизировать regression risk;
- поддерживать long-term maintainability.

---

## Execution Recovery Policy

Если execution flow деградирует:
- reload bootstrap context;
- reload current task file;
- reload relevant subsystem contexts;

избегать:
- uncontrolled reasoning expansion;
- speculative redesign during recovery.

