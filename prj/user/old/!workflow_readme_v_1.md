# Matris Workflow V1

## Назначение

Данная структура предназначена для:
- task-oriented разработки;
- bounded context execution;
- минимизации loaded context;
- последовательной semi-autonomous работы Codex;
- AI-native repository с human governance.

---

# Основные принципы

## Source Of Truth

Приоритет источников:
1. source code
2. task files
3. subsystem contexts
4. runtime/current_stage.md
5. workflow files
6. snapshot
7. history/archive

Source code authoritative.

---

## Workflow Model

Используется:
- sequential semi-autonomous workflow;
- subsystem-first loading;
- bounded context;
- task-oriented execution;
- minimal mutation policy.

Не используется:
- multi-agent swarm;
- parallel code editing.

---

## Mutation Policy

Разрешены:
- только минимальные изменения в рамках задачи.

Запрещены без подтверждения USER:
- архитектурные изменения;
- opportunistic refactoring;
- массовые изменения unrelated code.

---

## History Policy

History:
- append-only;
- не редактируется;
- corrections добавляются отдельными записями.

---

# Структура папки prj

```
prj/
├── chat_context_snapshot.md
├── global_rules.md
│
├── runtime/
│   └── current_stage.md
│
├── workflow/
│   ├── ai_behavior_rules.md
│   ├── build_commands.md
│   ├── context_compaction.md
│   ├── context_loading.md
│   ├── file_roles.md
│   ├── history_policy.md
│   ├── mutation_policy.md
│   ├── reporting.md
│   ├── repository_rules.md
│   ├── session_bootstrap.md
│   ├── subsystem_context_template.md
│   ├── task_execution.md
│   ├── task_execution_checklist.md
│   ├── task_file_template.md
│   └── testing.md
│
├── subsystems/
│   ├── subsystem_index.md
│   ├── entity_cube.md
│   ├── entity_figure.md
│   ├── game_loop.md
│   ├── layers.md
│   ├── platform_console.md
│   └── round_rules.md
│
├── tasks/
│   ├── active/
│   │   ├── TASK-XXXX.md
│   │   └── ...
│   │
│   ├── archive/
│   │   └── ...
│   │
│   ├── active_tasks.md
│   ├── backlog.md
│   └── task_naming_rules.md
│
├── history/
│   ├── history_template.md
│   ├── history_2026_Q2.md
│   └── ...
│
├── adr/
│   ├── ADR-0001-workflow-foundation.md
│   └── ...
│
├── risks/
│   └── known_risks.md
│
├── legacy/
│   ├── Codex.txt
│   ├── Codex_todo.txt
│   ├── chat_context_snapshot.md
│   └── class_method_analysis_report.md
│
├── user/
│   ├── здесь находятся файлы пользователя
│
└── archive/
    └── ...
```

---

# Назначение основных файлов

## chat_context_snapshot.md

Минимальный bootstrap context.
Используется как entry point нового чата.

---

## global_rules.md

Immutable/global project rules:
- code style;
- architecture restrictions;
- language rules;
- ownership rules.

---

## runtime/current_stage.md

Текущий этап разработки:
- stage scope;
- gameplay constraints;
- platform scope;
- exclusions;
- completion criteria.

---

## workflow/*

Operational workflow:
- context loading;
- task execution;
- testing;
- reporting;
- build process.

---

## subsystems/*

Subsystem architecture contexts:
- responsibilities;
- invariants;
- lifecycle;
- ownership;
- dependencies;
- risks.

---

## tasks/TASK-XXXX.md

Bounded operational context конкретной задачи:
- цель;
- scope;
- relevant files;
- required checks;
- risks;
- execution notes.

---

## history/*

Append-only operational history:
- task results;
- build/test results;
- regressions;
- fixes.

---

## adr/*

Architecture Decision Records.

Хранят:
- устойчивые архитектурные решения;
- причины решений;
- ограничения.

---

## risks/known_risks.md

Текущие известные риски:
- architecture risks;
- technical debt;
- unstable areas;
- deferred problems.

---

# Рекомендуемый порядок работы Codex

1. Load snapshot.
2. Load workflow files.
3. Load current stage.
4. Load subsystem context.
5. Load task file.
6. Load relevant source files.
7. Execute bounded task.
8. Build.
9. Run tests.
10. Append history.
11. Optional snapshot update.

---

# Основная цель Workflow V1

Сделать:
- deterministic Codex execution;
- минимальный context usage;
- reproducible task workflow;
- scalable long-term repository structure.

