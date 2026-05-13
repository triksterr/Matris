# Subsystem: Game Loop

## Назначение

Game Loop:
- orchestrates gameplay execution;
- управляет frame/update cycle;
- управляет lifecycle игры;
- управляет round transitions.

Game Loop:
- central execution coordinator;
- НЕ storage subsystem;
- НЕ rendering subsystem.

---

## Architectural Role

Game Loop:
- top-level gameplay execution coordinator;
- deterministic frame orchestrator;
- integration boundary между gameplay subsystems.

---

## Boundaries

Game Loop subsystem включает:
- frame sequencing;
- gameplay orchestration;
- timing coordination;
- gameplay state transitions.

Game Loop subsystem НЕ включает:
- rendering implementation;
- platform adapters;
- low-level storage;
- gameplay rule implementation details.

---

## Update Order Authority

Game Loop:
- authoritative update-order subsystem.

Execution order:
- explicit;
- deterministic;
- stable between runs.

Implicit update sequencing:
- forbidden.

---

## Error Handling

Используются:
- assertions;
- validation checks;
- explicit state transitions.

Недопустимо:
- hidden recovery behavior;
- implicit invalid-state correction;
- try/catch-driven gameplay flow.

---

## Основная ответственность

Game Loop отвечает за:
- update sequencing;
- timing;
- frame execution;
- round lifecycle;
- spawn/update/fixation flow;
- synchronization gameplay stages.

Game Loop НЕ отвечает за:
- rendering implementation;
- platform APIs;
- storage ownership;
- low-level rule implementation.

---

## Core Execution Model

Текущая модель:
- sequential deterministic loop.

Workflow:
1. input
2. update
3. collision checks
4. rules execution
5. render
6. frame finalize

---

## Determinism Requirements

Loop должен быть:
- deterministic;
- predictable;
- stable;
- reproducible.

Недопустимо:
- hidden asynchronous behavior;
- uncontrolled parallelism;
- nondeterministic update order.

---

## Timing Model

Целевой режим:
- 60 FPS.

Допустимо:
- небольшой timing drift;
- controlled degradation на слабых systems.

Timing должен:
- оставаться predictable;
- не ломать gameplay consistency.

---

## Figure Lifecycle

Типичный lifecycle:
1. spawn Figure
2. active movement
3. collision handling
4. lock delay
5. fixation into Layers
6. round rules execution
7. next Figure spawn

---

## Round Integration

Game Loop orchestrates:
- gravity cycle;
- destruction cycle;
- stabilization checks;
- game over checks.

Rules execution:
- deterministic;
- order-consistent.

---

## Lock Delay Integration

После bottom collision:
- запускается lock delay timer.

Во время lock delay:
- разрешен limited movement;
- запрещены invalid actions.

После завершения:
- Figure фиксируется.

---

## Input Integration

Input subsystem:
- external provider.

Game Loop:
- consumes normalized input state;
- orchestrates gameplay response.

Game Loop НЕ зависит напрямую от:
- WinAPI;
- console APIs;
- platform-specific input details.

---

## Render Integration

Render subsystem:
- external adapter.

Game Loop:
- предоставляет gameplay state;
- инициирует render phase.

Rendering:
- НЕ должен изменять gameplay state.

---

## Game State Model

Типичные states:
- running
- paused
- game over
- round transition

State transitions:
- explicit;
- deterministic;
- reviewable.

---

## Platform Independence

Game Loop:
- platform-independent;
- rendering-independent;
- input-implementation-independent.

---

## Testing Focus

Основные проверки:
- deterministic update order;
- timing stability;
- lock delay behavior;
- round sequencing;
- game over transitions;
- stable lifecycle execution.

---

## Related Tasks

Ключевые задачи:
- loop stabilization;
- timing stabilization;
- fixation sequencing;
- deterministic execution.

---

## Related Source Files

Основные файлы:
- game loop related files
- round orchestration files

---

## Related Subsystems

Связанные подсистемы:
- entity_figure.md
- layers.md
- round_rules.md
- platform_console.md

---

## Mutation Rules

Изменения Game Loop subsystem:
- должны сохранять deterministic sequencing;
- должны сохранять stable timing behavior;
- не должны silently менять gameplay ordering.

---

## Future Evolution

Допустимое развитие:
- configurable timing;
- richer state transitions;
- advanced round orchestration.

Не добавлять:
- platform-specific logic;
- rendering implementation;
- uncontrolled async execution.

---

## Known Risks

- timing drift accumulation;
- update-order regressions;
- hidden state desynchronization;
- unstable fixation sequencing;
- nondeterministic lifecycle transitions.
