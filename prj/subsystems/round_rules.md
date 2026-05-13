# Subsystem: Round Rules

## Назначение

Round Rules:
- определяют gameplay behavior раунда;
- определяют gravity/destruction logic;
- определяют stabilization cycle;
- определяют round parameters.

Round:
- фиксирует rules snapshot;
- rules не меняются внутри активного раунда.

---

## Architectural Role

Round Rules:
- authoritative gameplay rule orchestrator;
- deterministic gameplay state transformer;
- stabilization-cycle coordinator.

---

## Boundaries

Round Rules subsystem включает:
- gravity execution;
- destruction execution;
- stabilization cycles;
- gameplay rule ordering;
- round parameter orchestration.

Round Rules subsystem НЕ включает:
- rendering pipeline;
- platform adapters;
- low-level storage ownership;
- input polling;
- active figure rendering.

---

## Execution Order Authority

Round Rules:
- authoritative execution-order subsystem.

Execution order:
- explicit;
- deterministic;
- stable between identical runs.

Implicit rule ordering:
- forbidden.

---

## Error Handling

Используются:
- assertions;
- validation checks;
- deterministic rule guards.

Недопустимо:
- silent invalid state recovery;
- hidden rule correction;
- try/catch-based flow control.

---

## Основная ответственность

Round Rules отвечают за:
- gravity logic;
- destruction logic;
- stabilization loop;
- round parameters;
- gameplay rule execution order.

Round Rules НЕ отвечают за:
- rendering;
- platform logic;
- input handling;
- low-level storage ownership.

---

## Round Parameters

Типичные параметры:
- field size;
- gravity speed;
- lock delay;
- number range;
- figure count;
- destruction rules;
- geometry rules;
- color rules.

---

## Rule Generation Model

При старте раунда:
- вызываются generators;
- parameters фиксируются;
- active rules snapshot стабилизируется.

Во время раунда:
- rules immutable.

---

## Gravity Rule

Текущее правило:
- каждый cube без опоры падает вниз;
- падение до:
  - дна;
  - другого fixed cube.

Gravity:
- повторяется до стабилизации state.

---

## Destruction Rule

Текущее правило:
- ищется первая pair с суммой 10.

Порядок проверки:
1. vertical
2. left
3. right
4. top

Удаляется:
- только первая найденная pair.

---

## Stabilization Cycle

Execution cycle:

1. gravity
2. destruction
3. repeat until stable

Система считается stable:
- когда gravity не меняет state;
- когда destruction pair отсутствует.

---

## Lock Delay Rules

После касания снизу:
- lock delay = 1 секунда.

Во время lock delay:
- разрешено только left/right movement.

После завершения:
- Figure фиксируется в Layers.

---

## Game Over Rule

Game Over:
- новая Figure пересекается с Layers при spawn.

---

## Determinism Requirements

Round execution должен быть:
- deterministic;
- reproducible;
- order-consistent.

Недопустимо:
- nondeterministic rule ordering;
- hidden state mutations;
- unstable execution order.

---

## Rule Ownership

Round:
- orchestrates rules.

Rules:
- работают поверх gameplay state.

Layers:
- storage/lookup subsystem.

Figure:
- active entity subsystem.

---

## Platform Independence

Round Rules:
- platform-independent;
- rendering-independent;
- WinAPI-independent.

---

## Testing Focus

Основные проверки:
- gravity correctness;
- destruction ordering;
- stabilization correctness;
- lock delay behavior;
- game over detection;
- deterministic execution.

---

## Related Tasks

Ключевые задачи:
- gravity stabilization;
- destruction stabilization;
- cycle stabilization;
- round parameter generation.

---

## Related Source Files

Основные файлы:
- rules.h
- rules.cpp
- round.h
- round.cpp

---

## Related Subsystems

Связанные подсистемы:
- entity_cube.md
- entity_figure.md
- layers.md
- game_loop.md

---

## Mutation Rules

Изменения Round Rules subsystem:
- должны сохранять determinism;
- должны сохранять stable execution order;
- не должны silently менять gameplay semantics.

---

## Future Evolution

Допустимое развитие:
- configurable rule generators;
- richer destruction rules;
- advanced gravity systems;
- dynamic round generation.

Не добавлять:
- platform-specific logic;
- rendering logic;
- speculative generalized rule engines без use-case.

---

## Known Risks

- nondeterministic execution order;
- gravity/destruction infinite loops;
- hidden stabilization drift;
- destruction ordering regressions;
- gameplay state desynchronization.

