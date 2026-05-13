# Known Risks

# Authority

Medium-high authority operational risk registry.

---

## Назначение

Файл содержит:
- известные architectural risks;
- workflow risks;
- technical risks;
- operational risks.

Файл НЕ содержит:
- execution history;
- speculative ideas;
- unrelated notes.

---

# Workflow Risks

## R-0001 — Context Drift

Severity:
MEDIUM

Риск:
documentation может устаревать относительно source code.

Причина:
source evolves faster than docs.

Detection:
- docs contradict source behavior;
- outdated workflow assumptions;
- inconsistent operational descriptions.

Mitigation:
- source code authoritative;
- selective doc updates;
- drift reporting.

Ownership:
Shared

---

## R-0002 — Context Bloat

Severity:
HIGH

Риск:
слишком большой loaded context.

Последствия:
- token waste;
- unstable reasoning;
- degraded execution quality.

Detection:
- oversized prompts;
- unrelated reasoning chains;
- degraded task focus;
- unstable execution quality.

Mitigation:
- bounded context;
- subsystem-first loading;
- task-scoped execution.

Ownership:
Codex

---

## R-0003 — Scope Expansion

Severity:
HIGH

Риск:
неуправляемое расширение task scope.

Последствия:
- unstable working state;
- oversized diffs;
- review complexity.

Detection:
- unrelated file mutations;
- growing mutation scope;
- multi-subsystem edits without planning.

Mitigation:
- mutation scope freeze;
- single active task;
- explicit USER approval.

Ownership:
Shared

---

# Architecture Risks

## R-0010 — Cube Ownership Transition

Severity:
CRITICAL

Риск:
переход Figure:
`std::vector<Cube>`
к:
`std::vector<std::unique_ptr<Cube>>`

может затронуть:
- ownership;
- lifetime;
- Layers integration;
- copy semantics.

Detection:
- invalid ownership behavior;
- move/destruction regressions;
- pointer invalidation;
- broken figure/layer synchronization.

Mitigation:
- incremental migration;
- bounded tasks;
- explicit ownership rules;
- tests before/after migration.

Ownership:
Shared

---

## R-0011 — Raw Pointer Layer Access

Severity:
CRITICAL

Риск:
Layers хранит:
`std::vector<Cube*>`

Последствия:
- dangling pointers;
- invalid ownership assumptions;
- lifetime bugs.

Detection:
- dangling pointer crashes;
- invalid cube access;
- inconsistent ownership behavior;
- nullptr-related runtime failures.

Mitigation:
- explicit ownership model;
- Figure owns cubes;
- Layers non-owning references only;
- nullptr guards.

Ownership:
Shared

---

## R-0012 — Rotation Logic Complexity

Severity:
HIGH

Риск:
rotation/collision logic имеет высокий coupling.

Последствия:
- hidden edge cases;
- unstable movement behavior;
- hard-to-debug collisions.

Detection:
- inconsistent rotations;
- unstable collision behavior;
- edge-case regressions;
- nondeterministic movement.

Mitigation:
- isolate rotation logic;
- task-scoped stabilization;
- targeted unit tests.

Ownership:
Shared

---

# Platform Risks

## R-0020 — Console Rendering Limitations

Severity:
MEDIUM

Риск:
WinConsole rendering ограничен:
- FPS stability;
- redraw behavior;
- flickering;
- input latency.

Detection:
- visible flickering;
- unstable redraw behavior;
- inconsistent frame pacing;
- delayed input response.

Mitigation:
- minimal redraw strategy;
- bounded rendering scope;
- future platform abstraction.

Ownership:
Shared

---

## R-0021 — Platform Coupling

Severity:
HIGH

Риск:
WinAPI leakage в core logic.

Последствия:
- difficult Linux/Android migration;
- reduced portability.

Detection:
- WinAPI includes inside gameplay/core;
- platform-specific logic leakage;
- difficult platform isolation.

Mitigation:
- isolate platform adapters;
- keep gameplay logic platform-independent.

Ownership:
Shared

---

# Testing Risks

## R-0030 — Weak Unit Isolation

Severity:
MEDIUM

Риск:
tests могут зависеть от platform/runtime state.

Detection:
- flaky tests;
- timing-dependent behavior;
- platform-dependent failures.

Mitigation:
- isolate core logic;
- deterministic tests;
- avoid platform dependencies in tests.

Ownership:
Codex

---

## R-0031 — Missing Regression Coverage

Severity:
HIGH

Риск:
critical gameplay fixes могут ломаться позже.

Detection:
- repeated bug reappearance;
- regressions after unrelated changes;
- unstable gameplay behavior.

Mitigation:
- regression tests;
- task-linked tests;
- targeted verification.

Ownership:
Shared

---

# Operational Risks

## R-0040 — Large Refactoring Attempts

Severity:
CRITICAL

Риск:
слишком крупные изменения за один task cycle.

Последствия:
- unstable repository state;
- difficult review;
- rollback complexity.

Detection:
- oversized diffs;
- multi-subsystem mutations;
- unstable intermediate states;
- review difficulty growth.

Mitigation:
- small isolated tasks;
- bounded mutations;
- incremental stabilization.

Ownership:
Shared

---

## R-0041 — Silent Architecture Drift

Severity:
CRITICAL

Риск:
architecture changes without explicit approval.

Detection:
- undocumented architecture mutations;
- subsystem boundary drift;
- ownership model inconsistencies.

Mitigation:
- ADR process;
- USER governance;
- architecture approval policy.

Ownership:
USER

---

# Review Rules

Known risks:
- periodically reviewed;
- updated incrementally;
- append-oriented.

Не превращать файл:
- в backlog;
- в architecture doc;
- в brainstorming storage.

---

# Risk Management Goal

Risk workflow должен:
- поддерживать deterministic stabilization;
- предотвращать uncontrolled architecture drift;
- минимизировать hidden operational instability;
- сохранять bounded repository evolution.
