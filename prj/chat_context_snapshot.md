# Chat Context Snapshot

## Project

Matris

Экспериментальный AI-assisted игровой проект с deterministic workflow и bounded-context execution.

---

## Snapshot Role

Snapshot:
- bootstrap entry point;
- compact operational context;
- recovery layer after context loss.

Snapshot НЕ является:
- architecture source of truth;
- subsystem documentation;
- workflow specification;
- execution history.

---

## Current Workflow State

Workflow:
- Production Workflow V1 active;
- subsystem-first loading;
- bounded-context execution;
- task-oriented mutations.

Execution model:
- sequential semi-autonomous;
- deterministic;
- review-oriented.

---

## Core Governance

USER:
- architecture authority;
- scope authority;
- final approval authority.

Codex:
- bounded execution;
- implementation;
- verification;
- reporting.

Source code authoritative.

---

## Core Repository Rules

Primary carrier state:
- repository files;
- not chat history.

History:
- append-only;
- audit-oriented;
- non-authoritative operationally.

---

## Current Stage

WIN_CONSOLE_V1

Stage goals:
- gameplay core stabilization;
- ownership/lifetime stabilization;
- deterministic gameplay behavior;
- workflow stabilization.

---

## Active Subsystems

Current primary subsystems:
- entity_cube
- entity_figure
- layers
- round_rules
- game_loop
- platform_console

---

## Critical Architecture Facts

- gameplay core platform-independent;
- Figure owns active cubes;
- Layers stores non-owning Cube*;
- platform adapters isolated;
- source code authoritative.

Primary ownership migration direction:
`std::vector<std::unique_ptr<Cube>>`

---

## Current Stabilization Focus

Current focus:
- rotation/collision stabilization;
- ownership/lifetime stabilization;
- nullptr safety;
- deterministic gameplay execution;
- bounded workflow execution.

---

## Workflow Priorities

Operational priorities:
1. correctness
2. repository stability
3. bounded scope
4. reviewability
5. token efficiency
6. deterministic execution

---

## Bootstrap Order

Recommended loading order:
1. snapshot
2. current_stage
3. subsystem doc
4. task file
5. relevant source files

---

## Context Discipline

Load:
- only active subsystem;
- only active task;
- only relevant source files.

Avoid:
- full repository loading;
- unrelated subsystem analysis;
- full history loading;
- speculative context expansion.

---

## Current Execution Strategy

Execution flow:
1. load minimal context;
2. identify subsystem;
3. identify task scope;
4. execute bounded mutation;
5. verify;
6. report;
7. append history.

---

## Important Constraints

Avoid:
- uncontrolled refactoring;
- speculative redesign;
- autonomous architecture drift;
- oversized diffs;
- uncontrolled context growth.

Prefer:
- isolated tasks;
- incremental stabilization;
- deterministic execution;
- reviewable mutations.

---

## Drift Rule

If snapshot diverges from source code:
- source code authoritative;
- snapshot updated selectively;
- drift reported explicitly.

---

## Snapshot Rules

Snapshot:
- bootstrap-only;
- compact;
- operational;
- rarely updated.

Snapshot should:
- minimize token usage;
- avoid duplicated architecture;
- avoid duplicated workflow rules;
- avoid detailed gameplay mechanics.