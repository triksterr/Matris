# Session Bootstrap

## Authority

Medium-authority bootstrap workflow policy.

---

# Bootstrap Model

Bootstrap рассматривается как:
- minimal operational initialization;
- deterministic context recovery;
- bounded session startup.

---

## Основная цель

Обеспечить:
- быстрый старт нового чата;
- минимальный bootstrap context;
- predictable context loading;
- bounded reasoning с первых сообщений.

---

## Bootstrap Strategy

Использовать:
snapshot-first
+
subsystem-first
+
task-oriented loading

---

## Standard Bootstrap Order

Порядок загрузки:

1. chat_context_snapshot.md
2. relevant workflow files
3. runtime/current_stage.md
4. relevant subsystem contexts
5. active task file
6. relevant source files

---

## Minimal Bootstrap Principle

На старте НЕ загружать:
- speculative future tasks;
- exploratory architecture analysis;
- full subsystem inventories;
- весь repository;
- весь backlog;
- весь history;
- unrelated subsystems;
- large source trees.

---

## Snapshot Role

Snapshot:
- entry point нового чата;
- compact operational summary;
- bootstrap layer.

Snapshot НЕ является:
- architecture source;
- full operational history;
- complete repository description.

---

## Workflow Loading Rules

Workflow docs загружаются:
- selectively;
- только при необходимости;
- только relevant sections.

Не выполнять:
- full workflow reload без причины.

---

## Subsystem Bootstrap

Перед работой:
1. определить subsystem;
2. загрузить subsystem context;
3. определить task scope;
4. загрузить только relevant sources.

---

## Task Bootstrap

Task file должен определять:
- execution scope;
- mutation boundaries;
- relevant files;
- verification requirements.

Task file = primary operational context.

---

## Source Loading Rules

Загружать:
- минимальный набор source files;
- только нужные sections больших файлов;
- только связанные headers/cpp.

Избегать:
- exploratory loading;
- unrelated analysis;
- full-project parsing.

---

## Context Refresh Policy

Refresh должен:
- оставаться incremental;
- минимизировать repeated loading;
- сохранять bounded operational context.

При длинной работе:
- перечитывать только modified task-related files;
- не выполнять full bootstrap повторно;
- использовать incremental context refresh.

---

## Bootstrap Verification

После bootstrap необходимо определить:
- active subsystem;
- active task;
- mutation scope;
- required verification scope.

---

## Human Governance

USER:
- определяет priorities;
- определяет architecture direction;
- утверждает scope expansion.

Codex:
- предлагает execution plan;
- выполняет bounded tasks;
- минимизирует loaded context.

---

## Failure Recovery Bootstrap

После:
- context drift;
- long interruption;
- workflow confusion;

выполнять:
1. snapshot reload
2. current stage reload
3. active task reload
4. subsystem reload
5. targeted source reload

---

## Anti-Context-Bloat Bootstrap

Не переносить в новый чат:
- длинные reasoning chains;
- старые unrelated discussions;
- obsolete task context;
- duplicated architecture prose.

---

## Workflow Goal

Цель bootstrap workflow:
- fast session startup;
- predictable context loading;
- bounded execution;
- scalable AI-assisted development.

Bootstrap workflow должен:
- давать predictable startup behavior;
- минимизировать startup entropy;
- поддерживать scalable repository onboarding.
