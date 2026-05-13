# Context Compaction

## Authority

Medium-High authority context-management policy.

---

## Operational Model

Repository рассматривается как:
- layered context system;
- bounded operational workspace;
- reloadable execution environment.

---

## Основная цель

Минимизировать:
- loaded context;
- token usage;
- unnecessary reasoning;
- repeated information;
- cross-task contamination.

---

## Core Principle

Контекст должен быть:
- bounded;
- task-oriented;
- subsystem-scoped;
- reloadable;
- disposable.

---

## Primary Context Layers

Основные уровни контекста:

1. source code
2. task file
3. subsystem context
4. current stage
5. workflow rules
6. snapshot
7. archive/history

---

## Minimal Loading Policy

Загружать:
- только task-related files;
- только relevant subsystems;
- только нужные sections крупных файлов.

Не загружать:
- "just in case" context;
- recursive dependency exploration;
- speculative architecture analysis;
- весь repository;
- весь backlog;
- весь history;
- unrelated source files.

---

## Snapshot Usage

Snapshot:
- bootstrap layer;
- краткий operational summary;
- entry point нового чата.

Snapshot не должен:
- дублировать subsystem docs;
- дублировать workflow docs;
- содержать large detailed history.

---

## Task Context Policy

Task file:
- основной operational context;
- главный execution scope;
- главный source task boundaries.

Task file должен:
- быть компактным;
- содержать только execution-relevant data;
- ссылаться на subsystem docs вместо дублирования.

---

## Subsystem Context Policy

Subsystem docs должны:
- хранить invariants;
- хранить ownership rules;
- хранить lifecycle rules;
- хранить architecture boundaries.

Не хранить:
- implementation details;
- large code excerpts;
- duplicated task notes.

---

## Context Reload Policy

При recovery:
- уменьшать active context;
- возвращаться к task-boundaries;
- reload только relevant operational layers.

При длинной работе:
- перечитывать только измененные files;
- перечитывать только active task docs;
- не делать full context reload без необходимости.

---

## Context Expansion Policy

Перед расширением context:
1. определить necessity;
2. определить exact target;
3. загрузить minimal additional scope.

Избегать:
- speculative loading;
- exploratory full-project reading;
- unrelated subsystem analysis.

---

## Context Isolation Policy

Каждая задача должна:
- быть изолированной;
- иметь собственный bounded context;
- минимально зависеть от unrelated tasks.

---

## Token Efficiency Policy

Предпочитать:
- короткие summaries;
- structured markdown;
- subsystem references;
- targeted source loading.

Избегать:
- repeated prose;
- duplicated architecture explanations;
- full file dumps без необходимости.

---

## Documentation Deduplication

Не дублировать одинаковые правила между:
- snapshot;
- workflow docs;
- subsystem docs;
- task files.

Использовать:
- references;
- compact summaries;
- layered context structure.

---

## Operational Drift Policy

Если documentation drift detected:
- source code authoritative;
- drift фиксируется отдельно;
- selective correction preferred.

---

## Long-Term Repository Scaling

Repository должен:
- масштабироваться без context explosion;
- сохранять manageable loading cost;
- поддерживать bounded reasoning;
- оставаться AI-friendly.

---

## Workflow Goal

Цель context compaction:
- predictable token usage;
- fast bootstrap;
- bounded reasoning;
- scalable repository growth;
- controllable AI execution.

---

## Repository Entropy Control

Context workflow должен:
- минимизировать context entropy;
- предотвращать uncontrolled repository cognition growth;
- сохранять deterministic operational reasoning.

