# Testing Policy

## Authority

High authority verification policy.

Определяет:
- testing workflow;
- verification requirements;
- deterministic testing strategy;
- task completion verification.

---

## Основная цель

Тестирование должно:
- подтверждать корректность task-scoped изменений;
- предотвращать regression;
- обеспечивать controllable evolution ядра;
- минимизировать риск hidden breakage.

---

## Testing Strategy

Использовать hybrid strategy:

1. code implementation
2. unit tests
3. build verification
4. runtime verification
5. manual smoke testing

Все этапы выполняются раздельно.

---

## Test Priority

Приоритет тестирования:

1. core logic
2. ownership/lifecycle
3. collision logic
4. round rules
5. deterministic behavior
6. rendering correctness
7. platform adapters

---

## Test Scope Policy

Verification scope должен соответствовать:
- mutation scope;
- task scope;
- affected subsystem scope.

Тесты должны:
- соответствовать task scope;
- проверять только изменяемую логику;
- быть bounded-context.

Избегать:
- unnecessary full-system tests;
- unrelated regression runs;
- oversized test sessions.

---

## Unit Test Policy

Unit tests обязательны для:
- core algorithms;
- ownership transfer;
- collision checks;
- round rules;
- deterministic transformations;
- bugfix regressions.

---

## Test Framework Policy

Основной framework unit-тестов:
- GoogleTest (gtest);
- dependency management через vcpkg.

Встроенные test-only ветки в production entry point:
- не использовать как постоянную тестовую систему;
- переносить в `matris_tests`.

---

## Test Project Policy

Структура тестовой системы:
- отдельный проект `matris_tests` в составе `matris.sln`;
- исходники тестов размещаются в `matris/test/`;
- production проект `cons_test` не должен содержать runtime test switches.

Запуск unit-тестов:
- через `matris_tests.exe`;
- через стандартные gtest-параметры (`--gtest_filter`, `--gtest_repeat`, ...).

---

## Unit Test Isolation

Unit tests должны:
- быть deterministic;
- не зависеть от rendering;
- не зависеть от timing jitter;
- минимизировать nondeterministic behavior;
- не зависеть от filesystem;
- не зависеть от manual input.

---

## Build Verification

После изменения необходимо:
- выполнить build verification;
- проверить compile correctness;
- проверить отсутствие новых build errors.

Предпочитать:
- minimal rebuild;
- task-scoped verification.

---

## Runtime Verification

Runtime verification должна:
- подтверждать runtime stability;
- проверять critical execution path;
- проверять отсутствие obvious runtime regressions.

---

## Manual Smoke Policy

Manual smoke-test обязателен для:
- gameplay logic;
- rendering behavior;
- input handling;
- timing-sensitive behavior;
- lifecycle transitions.

---

## Smoke Test Scope

Минимальный smoke scope:
- запуск из Visual Studio;
- запуск из консоли;
- проверка input handling;
- проверка падения фигуры;
- проверка фиксации;
- проверка правил раунда;
- проверка Game Over.

---

## Regression Policy

Каждый исправленный bug:
- по возможности покрывать unit-test;
- фиксировать regression scenario;
- предотвращать повторное появление.

---

## Deterministic Behavior Policy

Core logic должна:
- быть deterministic;
- давать одинаковый результат при одинаковом input/state;
- не зависеть от platform timing behavior.

---

## Timing Policy

Timing-sensitive logic:
- тестировать отдельно;
- изолировать от rendering;
- проверять на drift/tick issues.

---

## Ownership Testing Policy

Особо проверять:
- ownership transfer;
- pointer validity;
- lifecycle correctness;
- отсутствие dangling pointers;
- корректность move/destruction.

---

## Pointer Safety Policy

Для pointer-based structures проверять:
- nullptr handling;
- invalid access prevention;
- ownership invariants;
- safe destruction order.

---

## Round Rules Testing

Правила раунда тестировать отдельно:
- gravity;
- destruction logic;
- stabilization cycle;
- collision order;
- edge cases.

---

## Rendering Test Policy

Rendering tests:
- не должны проверять console visuals побайтно;
- должны проверять logical rendering correctness;
- должны проверять отсутствие obvious rendering corruption.

---

## Input Testing Policy

Input tests должны проверять:
- single action per input;
- boundary behavior;
- forbidden actions;
- lock-delay restrictions.

---

## Task Completion Policy

Task не считается завершенной без:
- build verification;
- relevant tests;
- runtime verification;
- history record.

---

## Failure Policy

При failure:
- предпочитать isolated debugging;
- не расширять verification scope uncontrolled;
- не выполнять unrelated fixes автоматически.

Если тест не проходит:
- определить scope failure;
- определить связь с task;
- не исправлять unrelated failures без согласования;
- фиксировать результат в history.

---

## History Policy

Результаты тестирования:
- append-only;
- фиксируются в history;
- содержат:
  - что проверялось;
  - как проверялось;
  - результат проверки.

---

## Future Testing Evolution

На следующих этапах допускается:
- расширение test automation;
- integration tests;
- replay-based tests;
- deterministic simulation tests;
- performance tests.

Но:
- core deterministic testing остается базой workflow.

---

## Testing Scalability Policy

Testing workflow должен:
- оставаться bounded;
- оставаться reproducible;
- поддерживать repository growth;
- не превращаться в uncontrolled full-project verification.
