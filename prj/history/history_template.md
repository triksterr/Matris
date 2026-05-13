# History Template

## Authority

Template-level operational history formatting policy.

---

# Template Role

Файл определяет:
- стандарт history records;
- append-only formatting;
- audit consistency;
- deterministic logging structure.

---

## Назначение

History:
- append-only;
- immutable;
- chronological;
- audit-oriented.

History НЕ является:
- TODO list;
- backlog;
- architecture document.

---

# Record Format

## TASK RESULT

[DATE]
TASK: TASK-XXXX
STATUS: DONE | BLOCKED | CANCELLED
SUBSYSTEM: subsystem_name

SUMMARY:
Краткий результат.

CHANGES:
- file1
- file2

VERIFICATION:
- build
- tests
- smoke
- manual review

RISKS:
- none

NEXT:
- next step

---

## CORRECTION RECORD

[DATE]
CORRECTION FOR: TASK-XXXX

REASON:
Причина correction record.

DETAILS:
Что уточнено/исправлено.

NO HISTORY REWRITE.
APPEND-ONLY POLICY.

---

## FAILURE RECORD

[DATE]
TASK: TASK-XXXX
STATUS: FAILURE

PROBLEM:
Краткое описание failure.

SCOPE:
Что затронуто.

ACTION:
Что сделано.

NEXT:
Следующий recommended step.

---

## ARCHITECTURE DECISION REFERENCE

[DATE]
ADR: ADR-XXXX

SUMMARY:
Краткое описание решения.

IMPACT:
Какие subsystem affected.

---

# History Rules

History:
- никогда не переписывается;
- никогда не редактирует старые записи;
- допускает только append correction records.

---

# Loading Policy

History:
- не загружается по умолчанию;
- используется только для audit/history lookup;
- не используется как operational context.

---

# Granularity Rules

Record должен:
- быть кратким;
- быть deterministic;
- быть reviewable;
- ссылаться на task/subsystem.

Избегать:
- длинных narrative logs;
- speculative analysis;
- duplicated information.

---

# Recommended Frequency

Append history:
- после task completion;
- после important blocking issue;
- после approved architecture decision.

Не append:
- после каждой мелкой мысли;
- после промежуточных размышлений.

---

## History Compactness Rule

History должен:
- быстро читаться;
- поддерживать selective lookup;
- минимизировать context bloat;
- сохранять audit clarity.
