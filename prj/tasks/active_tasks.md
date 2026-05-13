# Active Tasks

## Authority

Medium-authority operational task queue.

---

# Operational Role

Файл является:
- active execution index;
- current stage task queue;
- operational prioritization layer.

Файл НЕ является:
- detailed task context;
- architecture documentation;
- history log.

---

## Назначение

Файл содержит:
- активные задачи текущего execution cycle;
- текущие task priorities;
- execution order;
- task ownership.

Файл:
- mutable;
- operational;
- stage-scoped.

После завершения этапа:
- архивируется;
- заменяется новым.

---

# Current Stage

WIN_CONSOLE_V1

---

# Execution Rules

Workflow:
- sequential semi-autonomous;
- single active task;
- bounded context;
- bounded mutation scope.

Parallel code editing:
NOT USED.

Multi-agent swarm:
NOT USED.

---

# Current Execution Queue

## ACTIVE

Одновременно допускается только:
- одна ACTIVE task.

## READY

### TASK-0010
Priority: P0
Subsystem: entity_figure
Status: READY

Goal:
- stabilize rotate/chkRotate/move logic;
- cover collisions and rotation validation.

---

### TASK-0011
Priority: P0
Subsystem: entity_figure
Status: READY

Goal:
- stabilize Figure::num lifecycle;
- synchronize with cubes.size().

---

### TASK-0015
Priority: P0
Subsystem: entity_cube
Status: READY

Goal:
- add unit tests for Cube copy semantics.

---

### TASK-0016
Priority: P0
Subsystem: entity_figure
Status: READY

Goal:
- remove unnecessary vector/Cube copies.

---

### TASK-0018
Priority: P0
Subsystem: round_rules
Status: READY

Goal:
- stabilize rules.h dependencies/includes.

---

# BLOCKED

### TASK-0013
Priority: P0
Subsystem: platform_console
Status: BLOCKED

Blocked by:
- ownership model decision for IRender.

Requires:
- USER-approved ownership model.

---

# DONE Policy

Completed tasks:
- удаляются из active queue;
- append в history;
- при необходимости архивируются отдельно.

---

# Task Activation Rule

Перед execution:
1. выбрать одну task;
2. создать task file;
3. загрузить только relevant subsystem contexts;
4. загрузить только relevant source files;
5. freeze mutation boundaries;
6. freeze subsystem scope.

---

# Completion Rule

Task считается завершенной только после:
- implementation;
- build verification;
- tests;
- manual verification (если требуется);
- history append.

---

# Mutation Rule

Во время task execution:
- не расширять mutation scope;
- не изменять unrelated subsystems;
- не выполнять speculative refactoring.

---

# Authority Rule

USER:
- approves architecture/significant scope changes.

Codex:
- executes bounded tasks;
- proposes minimal mutations;
- reports results.

---

# Queue Stability Goal

Task queue должна:
- оставаться compact;
- оставаться reviewable;
- поддерживать deterministic execution order;
- минимизировать operational ambiguity.
