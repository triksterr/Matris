# ADR-0001 — Workflow Foundation

## Status

Authority level:
FOUNDATIONAL

ACCEPTED

---

## Date

2026-05-11

---

## Context

Проект:
- растет по объему;
- использует AI-assisted development;
- требует минимизации token usage;
- требует deterministic execution;
- требует controllable mutations.

Проблемы старого подхода:
- слишком большой shared context;
- смешение history/TODO/context;
- высокая зависимость от chat history;
- высокий риск context bloat;
- слабая bounded isolation задач.

---

## Rejected Alternatives

Не приняты:
- full-chat-driven workflow;
- shared-global-context workflow;
- swarm-agent execution;
- parallel mutation workflow;
- history-centric operational model.

---

## Decision

Принят workflow:

- subsystem-first loading;
- task-oriented execution;
- bounded contexts;
- sequential semi-autonomous execution;
- append-only history;
- source code authoritative;
- human governance.

Основной carrier state:
- repository files;
- а не история чата.

---

## Core Rules

### Context Rules

- minimal loaded context;
- selective source loading;
- bounded task scope;
- subsystem-scoped execution.

---

### Mutation Rules

- minimal mutations;
- reviewable diffs;
- no speculative refactoring;
- no silent architecture drift.

---

### Governance Rules

USER:
- architecture authority;
- scope authority;
- final approval authority.

Codex:
- bounded execution;
- reporting;
- verification;
- task-scoped implementation.

---

### Workflow Rules

Workflow:
- single active task;
- no parallel editing;
- no swarm agents;
- deterministic execution flow.

---

### History Rules

History:
- append-only;
- immutable;
- audit-oriented.

Corrections:
- append correction records only.

---

## Consequences

Преимущества:
- lower token usage;
- scalable repository growth;
- easier recovery after context loss;
- deterministic execution;
- easier human review;
- bounded AI behavior.

Недостатки:
- больше repository docs;
- требуется discipline;
- требуется explicit task preparation.

Operational consequences:
- требуется strict context discipline;
- требуется bounded task preparation;
- repository docs становятся частью execution system;
- workflow stabilization становится critical infrastructure.

---

## Future Impact

Workflow должен:
- поддерживать дальнейший рост проекта;
- поддерживать Linux/Android stages;
- поддерживать AI-assisted scaling;
- минимизировать context collapse risks.

---

## Related Files

- workflow/context_loading.md
- workflow/mutation_policy.md
- workflow/task_execution.md
- workflow/repository_rules.md
- workflow/ai_behavior_rules.md

---

## Stability Note

Данный ADR:
- является foundational;
- изменяется редко;
- требует explicit USER approval для revisions.