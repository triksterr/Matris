# History Policy

## Authority

Medium-High authority workflow policy.

Определяет:
- правила ведения history;
- immutable logging policy;
- audit behavior.

History НЕ authoritative для:
- implementation;
- architecture;
- current operational state.

Source code и active workflow files имеют больший приоритет.

## Основная цель

History используется для:
- фиксации выполненных изменений;
- фиксации результатов проверок;
- фиксации решений;
- audit trail проекта.

History НЕ является:
- TODO;
- operational task list;
- architecture context;
- discussion log.

---

## Основные принципы

History:
- append-only;
- immutable;
- chronological;
- task-oriented.

---

## Запрещено

Запрещено:
- редактировать прошлые записи;
- silently rewrite history;
- reorder historical records;
- удалять старые записи;
- менять старые task results.

---

## Correction Policy

Если запись ошибочна:
- добавляется correction record;
- старая запись не изменяется.

---

## History Granularity

History фиксирует:
- task completion;
- task failure;
- verification results;
- build/test outcomes;
- approved architectural decisions;
- important operational events.

History НЕ фиксирует:
- промежуточные мысли;
- speculative ideas;
- large discussions;
- unrelated observations.

---

## Operational Focus

History должен:
- оставаться коротким;
- быть searchable;
- быть machine-readable;
- быть human-readable.

---

## Recommended Structure

Рекомендуемая структура записи:

- timestamp
- task id
- action/result
- verification
- affected files
- next step

---

## Verification Requirement

Каждая completed task должна содержать:
- что изменено;
- как проверено;
- результат проверки.

---

## Failure Logging

Если задача:
- заблокирована;
- провалена;
- отложена;

это фиксируется отдельно.

---

## Architecture Decision Logging

Крупные architecture decisions:
- фиксируются отдельными записями;
- содержат rationale;
- содержат approval status.

---

## Context Usage Policy

History:
- не загружается полностью по умолчанию;
- используется selective lookup;
- не используется как primary operational context.

---

## Archiving Policy

После завершения этапа:
- history архивируется;
- создается новый active history file.

Archive остается immutable.

---

## Human Governance

Critical records:
- architecture decisions;
- scope expansions;
- ownership model changes;

фиксируются только после approval USER.

---

## AI Mutation Policy

Codex может:
- append history records;
- append verification records;
- append correction records.

Codex не должен:
- rewrite history;
- delete records;
- silently modify old entries.

---

## Workflow Integration

History должен:
- поддерживать deterministic workflow;
- позволять reconstruction изменений;
- минимизировать context bloat;
- поддерживать AI-assisted development auditability.

---

## Scaling Policy

History должен:
- оставаться compact;
- разделяться по stage/time periods;
- поддерживать selective lookup;
- избегать giant monolithic logs.

