# File Roles

# Authority

Medium-High authority repository structure policy.

Определяет:
- роли файлов;
- responsibility boundaries;
- loading semantics;
- authority hierarchy.

---

## Основной принцип

Цель:
- predictable navigation;
- deterministic context loading;
- bounded repository scaling;
- reduced context ambiguity.

Каждый файл workflow должен иметь:
- одну основную роль;
- минимальное дублирование;
- понятный ownership;
- понятный lifecycle.

---

# Workflow Files

## workflow/context_loading.md

Назначение:
- правила загрузки контекста;
- bounded-context policy;
- context minimization.

Используется:
- в начале task session;
- при reload/rebootstrap.

---

## workflow/task_execution.md

Назначение:
- execution workflow;
- Definition of Done;
- verification stages;
- smoke-check policy.

Используется:
- при выполнении задач;
- при completion verification.

---

## workflow/build_commands.md

Назначение:
- build commands;
- build policies;
- verification commands;
- build environment rules.

Используется:
- во время build/test phase.

---

## workflow/testing.md

Назначение:
- testing strategy;
- test boundaries;
- verification policies;
- regression policy.

Используется:
- при test planning;
- при verification.

---

## workflow/mutation_policy.md

Назначение:
- mutation boundaries;
- safe-edit rules;
- scope control;
- governance rules.

Используется:
- перед code modifications;
- при scope expansion.

---

## workflow/history_policy.md

Назначение:
- append-only history rules;
- auditability;
- result logging policy.

Используется:
- при logging;
- при history updates.

---

## workflow/subsystem_context_template.md

Назначение:
- template subsystem contexts.

Используется:
- при создании новых subsystem files.

---

## workflow/task_file_template.md

Назначение:
- template bounded task files.

Используется:
- при создании новых task files.

---

## workflow/task_execution_checklist.md

Назначение:
- ultra-short operational checklist.

Используется:
- во время active execution.

---

# Runtime Files

## runtime/current_stage.md

Назначение:
- current active stage;
- active priorities;
- current constraints.

Используется:
- как operational stage context.

---

## chat_context_snapshot.md

Назначение:
- bootstrap context;
- quick reload summary;
- chat-independent operational snapshot.

Используется:
- первым файлом нового чата.

Не является:
- полной архитектурной документацией;
- source of truth.

---

# Subsystem Contexts

## subsystems/*.md

Назначение:
- subsystem architecture;
- invariants;
- ownership/lifecycle;
- subsystem boundaries.

Используется:
- перед loading source code subsystem.

---

# Task Files

## tasks/TASK-XXXX.md

Назначение:
- bounded operational task context;
- mutation scope;
- verification scope;
- relevant files list.

Главный operational context задачи.

---

## tasks/completed_tasks/TASK-XXXX.md

Назначение:
- immutable completed task record;
- historical task scope snapshot;
- non-operational archival storage.

Используется:
- только при selective historical lookup.

По умолчанию:
- не загружается в active execution context.

---

# Task Lists

## tasks/active_tasks.md

Назначение:
- active backlog;
- task ordering;
- current priorities.

Используется:
- для выбора следующей задачи.

Не используется:
- как execution context.

---

# History Files

## history/*.md

Назначение:
- append-only audit trail;
- task results;
- verification results;
- approved decisions.

Используется:
- selective lookup only.

---

# Archive Files

## archive/*

Назначение:
- immutable historical storage.

По умолчанию:
- не загружается.

---

# Source Code

## cons_test/*.h
## cons_test/*.cpp

Назначение:
- authoritative implementation.

Source code authoritative.

---

# Architectural Authority Model

При конфликте:

1. source code
2. active task file
3. subsystem context
4. runtime/current_stage.md
5. workflow rules
6. snapshot/history

---

# Mutation Ownership

USER:
- architecture authority;
- workflow authority;
- scope authority.

Codex:
- bounded execution;
- task implementation;
- verification;
- operational updates.

---

# File Registry

workflow/file_registry.md:
- central metadata registry;
- file descriptions;
- loading semantics;
- operational reference index.

---

# Anti-Duplication Principle

Не дублировать:
- architecture;
- rules;
- task descriptions;
- invariants

между несколькими файлами.

Каждый файл должен иметь:
- narrow responsibility;
- predictable usage;
- bounded scope.

---

# Repository Scaling Rule

При росте repository:
- file responsibilities должны оставаться narrow;
- context loading должен оставаться bounded;
- navigation должна оставаться predictable.


