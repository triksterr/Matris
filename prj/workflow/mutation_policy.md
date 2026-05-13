# Mutation Policy

## Authority

High authority operational workflow policy.

Определяет:
- mutation boundaries;
- mutation governance;
- autonomous change limits;
- stabilization priorities.

## Основная цель

Изменения кода должны:
- быть controllable;
- быть bounded;
- быть reviewable;
- минимизировать unintended side-effects.

---

## Core Principle

Предпочитать:
- small isolated mutations;
- task-scoped edits;
- incremental evolution.

Избегать:
- large uncontrolled rewrites;
- speculative refactoring;
- architecture drift.

---

## Mutation Scope

Mutation scope должен быть согласован с:
- current task file;
- current subsystem scope;
- current operational priorities.

Перед изменением необходимо определить:
- mutation scope;
- affected files;
- affected subsystem;
- verification scope.

---

## Scope Freeze

После определения task scope:
- не расширять mutation scope без необходимости;
- не изменять unrelated files;
- не выполнять opportunistic refactoring;
- не выполнять "cleanup nearby code" без необходимости;
- не расширять edits ради stylistic consistency.

---

## Minimal Mutation Rule

Каждая задача должна:
- изменять минимально необходимый код;
- сохранять working state;
- оставаться locally verifiable.

---

## Source Authority

Source code authoritative.

Но:
- архитектурные invariants должны уважаться;
- subsystem contracts должны сохраняться.

---

## Human Governance

Codex не должен без approval USER:
- менять architecture;
- менять ownership model;
- менять subsystem boundaries;
- менять build structure;
- менять workflow rules.

---

## Allowed Autonomous Changes

Codex может самостоятельно:
- выполнять bounded task edits;
- исправлять локальные bugs;
- добавлять task-scoped tests;
- обновлять task results/history;
- обновлять snapshot после крупных approved changes.

---

## Forbidden Autonomous Changes

Codex не должен автоматически:
- переписывать subsystem architecture;
- менять large code areas;
- выполнять mass refactoring;
- менять unrelated code;
- исправлять unrelated warnings/errors;
- менять immutable workflow rules.

---

## Ownership Mutation Policy

Изменения ownership/lifecycle:
- считаются high-risk;
- требуют explicit reasoning;
- требуют focused verification;
- желательно покрывать tests.

---

## Pointer Safety Policy

При работе с указателями:
- минимизировать dangling risk;
- явно определять ownership;
- сохранять lifecycle invariants;
- избегать hidden ownership transfer.

---

## Refactoring Policy

Refactoring допускается только если:
- он необходим для task completion;
- уменьшает risk;
- уменьшает complexity;
- улучшает maintainability локального scope.

---

## Anti-Overengineering Policy

Не добавлять:
- abstractions без use-case;
- generalized frameworks;
- premature extensibility;
- speculative systems.

---

## Reviewability Policy

Каждое изменение должно:
- быть понятным;
- быть explainable;
- быть reviewable человеком;
- иметь ограниченный diff size.

---

## Deterministic Workflow Policy

Mutation workflow должен:
- оставаться predictable;
- поддерживать deterministic debugging;
- минимизировать hidden interactions.

---

## Verification Requirement

После mutation:
- выполнить verification;
- проверить build;
- проверить affected behavior;
- зафиксировать результат.

---

## Failure Handling

Если mutation:
- ломает build;
- ломает invariants;
- вызывает unexpected regressions;

необходимо:
- остановить scope expansion;
- локализовать проблему;
- зафиксировать результат;
- согласовать дальнейшие изменения.

Предпочитать:
- rollback local mutation scope;
- reload task context;
- isolated debugging.

---

## Documentation Drift Policy

Если mutation делает documentation outdated:
- drift фиксируется;
- documentation update выполняется отдельно;
- не выполнять silent rewrite больших docs.

---

## Incremental Stabilization

Приоритет:
1. stable behavior
2. deterministic behavior
3. maintainability
4. extensibility
5. optimization

Optimization without need запрещена.

---

## AI-Native Repository Principle

Repository должен:
- поддерживать bounded-context development;
- поддерживать deterministic mutations;
- быть удобным для human review;
- быть удобным для AI-assisted execution.

---

## Mutation Scaling Policy

При росте repository:
- mutation scope должен оставаться bounded;
- verification scope должен оставаться controllable;
- review complexity не должна расти uncontrollably.
