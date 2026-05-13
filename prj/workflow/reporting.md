# Reporting Policy

## Authority

Medium-High authority operational communication policy.

Определяет:
- execution reporting;
- verification reporting;
- communication boundaries;
- reporting structure.

Reporting НЕ authoritative для:
- implementation details;
- architecture truth;
- current repository state.

Source code и workflow files имеют больший приоритет.

---

## Назначение

Файл определяет:
- reporting rules;
- execution reporting;
- mutation reporting;
- verification reporting;
- concise communication format.

Цель:
- deterministic reporting;
- minimal token usage;
- reviewable execution logs;
- bounded communication.

---

# Core Reporting Principles

Reporting должен быть:
- кратким;
- deterministic;
- task-oriented;
- reviewable;
- locally understandable.

Избегать:
- длинных narrative explanations;
- speculative reasoning;
- repeated context;
- unrelated analysis;
- repeated repository summaries;
- unnecessary historical retelling.

---

# Standard Reporting Flow

Во время execution reporting должен содержать:

1. цель шага;
2. mutation scope;
3. результат;
4. verification;
5. next step.

---

# Preferred Communication Style

Предпочитать:
- короткие блоки;
- structured summaries;
- explicit status;
- explicit boundaries.

---

# Mutation Reporting

После изменений сообщать:

- какие файлы изменены;
- какие методы/sections изменены;
- зачем изменение выполнено;
- как проверить изменение.

---

# Verification Reporting

Verification reporting должен содержать:
- build status;
- test status;
- smoke status;
- manual verification status.

Если verification НЕ выполнялся:
- явно указать это.

---

# Build Reporting

Build report:
- краткий;
- deterministic;
- focused on current task.

Избегать:
- unrelated warnings;
- unrelated failures;
- full verbose logs без необходимости.

---

# Failure Reporting

При reporting failures:
- предпочитать concise recovery proposals;
- не выполнять speculative redesign analysis;
- не расширять communication scope uncontrolled.

Если возникает ошибка:
- определить scope;
- определить связь с текущей task;
- сообщить blocking reason;
- предложить minimal next action.

Не выполнять:
- autonomous scope expansion;
- unrelated fixes;
- speculative rewrites.

---

# Task Completion Reporting

После completion сообщать:

- task status;
- changed files;
- verification results;
- remaining risks;
- next recommended step.

---

# Reporting Granularity

Предпочитать:
- medium granularity;
- bounded reports;
- isolated explanations.

Избегать:
- over-reporting;
- under-reporting;
- giant diff explanations.

---

# Human Reviewability

Reporting должен:
- помогать manual review;
- помогать local reasoning;
- объяснять intent изменений;
- сохранять predictable structure.

---

# Context Economy

Reporting должен:
- минимизировать token usage;
- не дублировать docs;
- не дублировать source code;
- ссылаться на subsystem/task files вместо повторения.

---

# History Separation

Reporting:
- НЕ заменяет history;
- НЕ заменяет ADR;
- НЕ заменяет subsystem docs.

History append выполняется отдельно.

---

# Operational Discipline

Во время execution:
- держать focus на current task;
- не уходить в unrelated redesign;
- не расширять discussion scope без необходимости.

---

# AI Behavior Rule

Codex должен:
- объяснять significant mutations;
- явно обозначать assumptions;
- сообщать verification scope;
- сохранять bounded reasoning.

---

# Workflow Goal

Итоговая цель reporting:
- predictable execution;
- efficient review;
- scalable AI-assisted development;
- minimal communication overhead.

---

## Reporting Scalability Policy

Reporting workflow должен:
- оставаться compact;
- поддерживать long-term repository growth;
- поддерживать bounded token usage;
- оставаться readable при large task history.
