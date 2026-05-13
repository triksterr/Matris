# Repository Rules

## Authority

High-authority repository governance file.

---

## Repository Model

Repository рассматривается как:
- deterministic operational system;
- AI-assisted development environment;
- bounded-context workspace;
- human-governed architecture.

---

## Основная цель

Repository должен:
- поддерживать deterministic development;
- поддерживать bounded-context workflow;
- минимизировать context bloat;
- быть удобным для human review;
- быть удобным для AI-assisted execution.

---

## Core Principles

Основные принципы:
- source code authoritative;
- human governance;
- bounded mutations;
- append-only history;
- task-oriented workflow;
- subsystem-first context loading.

---

## Repository Authority Model

USER:
- architecture authority;
- workflow authority;
- scope authority;
- final approval authority.

Codex:
- bounded implementation;
- verification;
- reporting;
- task-scoped execution.

---

## Context Discipline

Не загружать:
- весь repository;
- весь history;
- весь backlog;
- unrelated subsystems.

Всегда использовать:
- minimal operational loading;
- local reasoning;
- bounded verification;
- bounded context;
- subsystem-first loading;
- task-oriented execution.

---

## Mutation Rules

Изменения должны:
- быть minimal;
- быть reviewable;
- быть task-scoped;
- сохранять working state.

Избегать:
- mass refactoring;
- speculative redesign;
- uncontrolled rewrites.

---

## Architecture Governance

Architecture:
- не изменяется silently;
- не изменяется автоматически;
- изменяется только после approval USER.

---

## Documentation Rules

Documentation должна:
- иметь bounded responsibility;
- не дублировать source code;
- не дублировать другие docs;
- обновляться selective.

---

## Source Code Rules

Source code:
- authoritative;
- primary truth source;
- deterministic;
- reviewable.

При конфликте:
source code priority выше documentation.

---

## Workflow Rules

Workflow должен:
- оставаться deterministic;
- минимизировать token usage;
- минимизировать loaded context;
- поддерживать incremental stabilization.

---

## History Rules

History:
- append-only;
- immutable;
- chronological;
- audit-oriented.

Correction records:
- append-only;
- не переписывают старые записи.

---

## Task Rules

Каждая task:
- имеет bounded scope;
- имеет explicit verification;
- имеет limited mutation scope;
- должна завершаться working state.

---

## Subsystem Rules

Subsystem contexts:
- описывают invariants;
- описывают ownership;
- описывают boundaries;
- не дублируют implementation details.

---

## Build Rules

Build workflow:
- deterministic;
- reproducible;
- minimally invasive;
- task-scoped when possible.

---

## Testing Rules

Testing:
- mandatory for critical logic;
- deterministic;
- isolated;
- task-scoped.

---

## AI Interaction Rules

Codex должен:
- избегать context bloat;
- избегать speculative analysis;
- избегать autonomous architecture drift;
- объяснять significant mutations;
- сохранять reviewability.

---

## Human Reviewability

Каждое изменение должно:
- быть читаемым;
- быть explainable;
- быть locally understandable;
- иметь ограниченный diff size.

---

## Repository Growth Policy

Repository должен:
- расти incremental;
- сохранять manageable complexity;
- избегать uncontrolled abstraction growth;
- поддерживать long-term maintainability.

---

## Anti-Overengineering Rules

Запрещено:
- premature abstraction;
- speculative frameworks;
- generalized systems без use-case;
- optimization without need.

---

## Archive Rules

Archive:
- immutable;
- не загружается по умолчанию;
- используется только для historical lookup.

---

## Legacy Rules

Legacy files:
- сохраняются;
- не являются active workflow;
- используются только как migration/reference layer.

---

## Task Execution Policy

Одна execution unit:
- одно небольшое изменение;
- одна проверяемая logical mutation;
- один bounded verification cycle.

Предпочитать:
- small commits;
- small diffs;
- sequential stabilization.

---

## Context Authority Policy

Global workflow docs:
- stable;
- редко изменяются;
- требуют explicit approval USER.

Subsystem docs:
- могут уточняться по мере стабилизации subsystem.

Task files:
- operational;
- mutable;
- disposable после завершения этапа.

---

## Drift Handling Policy

Если:
- workflow docs;
- subsystem docs;
- snapshot files

устарели относительно source code:

- source code authoritative;
- drift фиксируется отдельно;
- silent global rewrites запрещены.

---

## Workflow Goal

Итоговая цель repository:
- predictable development;
- deterministic execution;
- scalable AI-assisted workflow;
- controllable evolution проекта.

Repository должен оставаться:
- predictable;
- scalable;
- locally understandable;
- operationally stable
при long-term development.

