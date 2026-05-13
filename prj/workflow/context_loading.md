# Политика загрузки контекста

## Authority

High authority workflow policy.

Определяет:
- context loading strategy;
- context boundaries;
- loading priorities;
- operational context discipline.

При конфликте:
- source code authoritative для implementation;
- task file authoritative для task scope;
- данный файл authoritative для context-loading behavior.

---

## Основная цель

Минимизировать:
- loaded context;
- token usage;
- unrelated reasoning;
- cross-task contamination.

Основной carrier state проекта:
- файлы проекта;
- а не история чата.

---

## Общий порядок загрузки

Стандартный порядок:

1. chat_context_snapshot.md
2. relevant workflow files
3. runtime/current_stage.md
4. relevant subsystem files
5. current task file
6. relevant source files

---

## Snapshot-first стратегия

Snapshot используется:
- как bootstrap context;
- как краткое operational summary;
- как entry point для нового чата.

Snapshot НЕ является полным источником истины.
Snapshot должен оставаться compact bootstrap layer.

---

## Приоритет источников

Приоритет:

1. source code
2. current task file
3. subsystem context files
4. runtime/current_stage.md
5. workflow files
6. snapshot
7. old history/docs

---

## Subsystem-first loading

Перед загрузкой исходников:
1. определить subsystem;
2. загрузить subsystem context;
3. определить task scope;
4. загружать только task-relevant source files.

---

## Bounded Context Policy

Каждая задача должна иметь:
- ограниченный task scope;
- ограниченный subsystem scope;
- минимально необходимый loaded context.

Не загружать:
- весь проект;
- весь TODO;
- весь history;
- нерелевантные subsystem files.

---

## Политика task files

Task file должен содержать:
- цель задачи;
- boundaries;
- relevant files;
- required checks;
- known risks;
- related subsystem contexts.

Task file является главным operational context задачи.

---

## Политика subsystem contexts

Subsystem contexts:
- описывают архитектуру подсистемы;
- описывают invariants;
- описывают ownership/lifecycle;
- не дублируют исходный код.

Source code authoritative.

---

## Политика history

History:
- append-only;
- не используется как основной рабочий контекст;
- загружается только при необходимости.

---

## Политика snapshot updates

Snapshot обновляется только:
- после значимых архитектурных изменений;
- после workflow stabilization;
- после изменения operational priorities.

Не обновлять snapshot после каждой задачи.

---

## Политика архива

Archive:
- не загружается по умолчанию;
- используется только для historical lookup.

---

## Контекстная дисциплина

Codex должен:
- избегать unnecessary context expansion;
- избегать unrelated analysis;
- избегать speculative redesign;
- работать task-oriented.

---

## Оптимальная стратегия workflow

Рекомендуемая модель:
subsystem-first
+
task-oriented
+
bounded context
+
minimal mutation

---

## Multi-Agent Policy

Multi-agent swarm: не используется.
Parallel code editing: не используется.
Workflow: sequential semi-autonomous.

---

## Task Boundary Freeze

После определения task scope:
- не расширять scope без необходимости;
- не загружать дополнительные subsystem contexts без причины;
- не переходить в соседние subsystem areas без явного основания.

---

## Source Loading Policy

Загружать:
- только релевантные source files;
- только необходимые sections крупных файлов;
- только связанные headers/cpp.

Избегать:
- полного чтения больших файлов без необходимости.

---

## Transient Context Policy

Codex должен:
- читать только task-relevant files;
- извлекать только relevant operational data;
- избегать удержания full-file context;
- избегать repeated full-file reasoning.

После анализа файла:
- использовать compact operational summary;
- удерживать только task-relevant details;
- discard unrelated details from active reasoning context.

Предпочитать:
- selective reasoning;
- bounded operational memory;
- compact execution context.

Избегать:
- repository-wide mental state;
- long-lived unrelated context;
- repeated full reloads.

---

## Context Retention Policy

Во время execution:
- unrelated subsystem details не должны оставаться active context;
- completed task context не должен загрязнять новый execution cycle;
- stale reasoning должен discard/reload selective.

Каждая новая task:
- начинается с bounded operational context;
- минимально зависит от previous reasoning chain;
- использует selective context refresh вместо полного reload.

---

## Context Compaction Policy

После анализа:
- больших source files;
- subsystem docs;
- workflow docs;

Codex должен:
- сохранять только operationally relevant data;
- минимизировать retained context;
- compress reasoning state до compact task-relevant summary.

Не удерживать:
- полный content файлов;
- large prose sections;
- unrelated implementation details;
- obsolete reasoning chains.

---

## Mutation Scope Policy

Перед изменением:
- определить точный mutation scope;
- определить список изменяемых файлов;
- не расширять mutation scope без необходимости.

Предпочитать:
- small isolated changes;
- single-responsibility edits;
- task-scoped mutations.

Не изменять:
- unrelated files;
- neighboring subsystems;
- shared architecture layers;

без явной необходимости.

---

## Response Verbosity Policy

По умолчанию Codex должен:
- отвечать кратко;
- не писать длинных explanations;
- не дублировать очевидную информацию;
- не генерировать large prose blocks без запроса USER.

После task execution:
- достаточно краткого operational report;
- detailed explanation только по запросу USER.

Комментарии в коде:
- только если необходимы;
- только если explicitly requested;
- только если улучшают maintainability.

---

## Operational Drift Policy

Если:
- subsystem docs;
- workflow docs;
- task docs

устарели относительно source code:

- source code authoritative;
- drift фиксируется отдельно;
- documentation не переписывается silently.

---

## Anti-Context-Bloat Policy

Не дублировать:
- одинаковые правила;
- одинаковые architecture notes;
- одинаковые task descriptions

между:
- snapshot;
- workflow;
- subsystem contexts;
- task files.

---

## Context Reload Policy

При длинной работе:
- перечитывать только измененные task-related files;
- не выполнять полный reload workflow context без необходимости.

Snapshot используется только как bootstrap layer.

---

## Human Governance Policy

USER:
- утверждает архитектурные изменения;
- утверждает scope expansion;
- контролирует critical mutations;
- принимает завершение задач.

Codex:
- предлагает изменения;
- выполняет bounded tasks;
- не принимает архитектурные решения автономно.

---

## Anti-Overengineering Policy

Не добавлять:
- abstractions без необходимости;
- generalized systems без текущего use-case;
- premature extensibility;
- speculative architecture.

Предпочитать:
- minimal viable structure;
- incremental evolution;
- task-driven growth.

---

## Workflow Goal

Цель workflow:
- deterministic execution;
- predictable context usage;
- scalable repository growth;
- controllable AI-assisted development.

---

## Repository Scaling Policy

Workflow должен:
- масштабироваться на long-term development;
- поддерживать growth количества subsystem contexts;
- поддерживать growth количества task files;
- сохранять controllable context size.

---

## Context Failure Recovery

При:
- context degradation;
- context loss;
- inconsistent reasoning;

предпочитать:
- reload bootstrap layer;
- reload current task file;
- reload relevant subsystem contexts;
