# Matris — Project Architecture and Production Workflow V1

## 1. Project Overview

Matris — экспериментальный AI-assisted игровой проект с deterministic workflow, bounded-context execution и human-governed architecture.

Главная цель текущего этапа:
- стабилизировать игровое ядро;
- стабилизировать ownership/lifetime model;
- стабилизировать игровой цикл;
- создать scalable production-level AI workflow;
- минимизировать context bloat и token usage.

Проект ориентирован на:
- incremental development;
- deterministic execution;
- reviewable mutations;
- bounded task execution;
- AI-native repository structure.

При этом:
- source code authoritative;
- architecture controlled by USER;
- Codex выполняет bounded implementation.

---

# 2. Основная философия workflow

## 2.1 Главная проблема AI-assisted development

Без strict workflow AI-assisted разработка быстро деградирует из-за:
- context bloat;
- massive chat histories;
- uncontrolled reasoning;
- architectural drift;
- unrelated mutations;
- low reviewability.

Поэтому workflow строится вокруг:
- repository files;
- bounded contexts;
- deterministic execution;
- minimal mutation scope.

---

## 2.2 Основной carrier state

Главный carrier state проекта:
- файлы проекта;
- а не история чата.

История чата:
- временная;
- может теряться;
- не считается authoritative context.

Все критические знания должны жить в repository files.

---

## 2.3 Source Code Authority

Source code всегда authoritative.

Если:
- subsystem docs;
- workflow docs;
- task docs

устарели относительно source code:
- source code имеет приоритет;
- drift фиксируется отдельно;
- documentation не переписывается silently.

---

# 3. Workflow Model

## 3.1 Workflow Type

Workflow:
- sequential semi-autonomous.

Не используется:
- multi-agent swarm;
- parallel code editing;
- uncontrolled autonomous execution.

---

## 3.2 Human Governance

USER:
- architecture authority;
- workflow authority;
- scope authority;
- final approval authority.

Codex:
- bounded implementation;
- verification;
- reporting;
- task-scoped execution.

Codex не должен:
- silently mutate architecture;
- expand scope autonomously;
- perform speculative redesign.

---

## 3.3 Workflow Goal

Главная цель workflow:
- deterministic execution;
- predictable context usage;
- scalable repository growth;
- controllable AI-assisted development.

---

# 4. Context Model

## 4.1 Context Levels

Контекст делится на несколько уровней.

### Global Context

Редко изменяется.

Содержит:
- architecture direction;
- workflow rules;
- repository governance;
- core operational rules.

Примеры:
- global_rules.md
- repository_rules.md
- context_loading.md

---

### Runtime Context

Текущий operational state.

Содержит:
- current stage;
- current priorities;
- current blockers.

Пример:
- runtime/current_stage.md

---

### Subsystem Context

Контекст конкретной подсистемы.

Содержит:
- invariants;
- ownership;
- lifecycle;
- subsystem boundaries;
- interaction model.

Не дублирует implementation details.

Примеры:
- entity_cube.md
- entity_figure.md
- layers.md
- round_rules.md

---

### Task Context

Минимальный bounded operational context.

Содержит:
- цель задачи;
- mutation scope;
- relevant files;
- verification requirements;
- known risks.

Task file — главный operational context задачи.

---

## 4.2 Snapshot-first Strategy

Snapshot:
- bootstrap layer;
- краткое operational summary;
- entry point нового чата.

Snapshot НЕ является полной truth source.

---

## 4.3 Subsystem-first Loading

Перед загрузкой source code:
1. определить subsystem;
2. загрузить subsystem docs;
3. определить task scope;
4. загрузить только relevant source files.

---

## 4.4 Bounded Context

Каждая задача должна иметь:
- ограниченный scope;
- ограниченный mutation set;
- минимальный loaded context.

Запрещено:
- загружать весь проект;
- загружать весь backlog;
- загружать весь history;
- делать unrelated analysis.

---

# 5. Repository Structure

```text
prj/
├── chat_context_snapshot.md
├── global_rules.md
├── runtime/
│   └── current_stage.md
├── workflow/
│   ├── context_loading.md
│   ├── history_policy.md
│   ├── mutation_policy.md
│   ├── task_execution.md
│   ├── testing.md
│   ├── reporting.md
│   ├── subsystem_context_template.md
│   ├── task_file_template.md
│   ├── task_execution_checklist.md
│   ├── file_roles.md
│   ├── repository_rules.md
│   ├── ai_behavior_rules.md
│   ├── context_compaction.md
│   ├── session_bootstrap.md
│   └── build_commands.md
├── subsystems/
│   ├── subsystem_index.md
│   ├── entity_cube.md
│   ├── entity_figure.md
│   ├── layers.md
│   ├── round_rules.md
│   ├── game_loop.md
│   └── platform_console.md
├── tasks/
│   ├── active_tasks.md
│   ├── task_naming_rules.md
│   ├── backlog.md
│   ├── TASK-XXXX.md
│   └── ...
├── history/
│   ├── history_template.md
│   ├── history_YYYY_QX.md
│   └── ...
├── adr/
│   ├── ADR-0001-workflow-foundation.md
│   └── ...
├── risks/
│   └── known_risks.md
├── legacy/
│   ├── Codex.txt
│   ├── chat_context_snapshot.md
│   ├── class_method_analysis_report.md
│   └── Codex_todo.txt
└── archive/
    └── ...
```

---

# 6. Core Gameplay Architecture

## 6.1 Cube

Cube — базовая игровая сущность.

Содержит:
- число;
- цвет;
- координаты;
- visibility state.

Кубик:
- объект единичного размера;
- существует в координатах стакана.

Координаты:
- нижний левый кубик: (0;0)
- соседи:
  - (0;1)
  - (1;0)
  - (1;1)

---

## 6.2 Figure

Figure — фигура из нескольких кубиков.

Содержит:
- набор кубиков;
- центр вращения;
- offset matrix;
- порядок кубиков.

Ownership model:

```cpp
std::vector<std::unique_ptr<Cube>>
```

Figure owns cubes.

Figure:
- инициирует movement/rotation;
- проверяет возможность движения;
- взаимодействует со Layers.

---

## 6.3 Layers

Layers — нижние фиксированные слои.

Хранит:
- matrix/grid стакана;
- non-owning references на кубики.

Storage model:

```cpp
std::vector<Cube*>
```

Layers:
- не владеет кубиками;
- использует raw non-owning pointers.

Основная ответственность:
- collision checks;
- occupancy checks;
- layer gravity;
- destruction rules.

---

## 6.4 Ownership Model

Ownership:

Figure:
- owns cubes.

Layers:
- stores references only.

При фиксации фигуры:
- ownership transfer/state transition должен быть explicit;
- dangling pointers недопустимы.

---

## 6.5 Round

Round содержит параметры текущего игрового цикла.

Содержит:
- размеры стакана;
- скорость падения;
- digit rules;
- geometry rules;
- color rules;
- destruction rules;
- figure generation rules.

Правила внутри раунда:
- фиксируются при старте раунда;
- внутри раунда не изменяются.

---

## 6.6 Game Loop

Game loop практически фиксирован.

Основной flow:
1. spawn figure;
2. falling;
3. collision;
4. lock delay;
5. transfer to layers;
6. gravity;
7. destruction;
8. stabilization;
9. next figure.

---

# 7. Platform Architecture

## 7.1 Platform Separation

Gameplay logic:
- platform-independent.

Platform layer:
- isolated adapters.

---

## 7.2 Rendering

Interface:

```cpp
IRender
```

Implementations:
- CRender — console;
- WRender — windows graphics.

---

## 7.3 Audio

Interface:

```cpp
IAudio
```

Implementations:
- CAudio;
- WAudio.

---

## 7.4 Input

Interface:

```cpp
IInput
```

Implementations:
- WInput;
- MInput.

---

## 7.5 Files

Interface:

```cpp
IFiles
```

Implementations:
- WFiles.

---

# 8. Current Stage — WIN_CONSOLE_V1

## 8.1 Stage Goal

Стабилизировать:
- консольное ядро;
- игровой цикл;
- round logic;
- testability;
- ownership model.

---

## 8.2 Current Platform

- Windows
- Console
- Pseudographics
- Keyboard input

---

## 8.3 Non-Goals

Не входят:
- sound;
- file IO;
- Linux;
- Android;
- multiplayer;
- networking.

---

## 8.4 Runtime Targets

### Field

Базовый размер:
- 20x10

---

### FPS

Цель:
- 60 FPS

Небольшой drift допускается.

---

### Falling

- 1 second step.

---

### Lock Delay

- 1 second;
- only left/right movement allowed.

---

### Game Over

Новая фигура пересекается со слоями.

---

# 9. Round Rules

## 9.1 Gravity Rule

Каждый кубик без опоры:
- падает вниз;
- пока не встретит:
  - другой кубик;
  - дно.

---

## 9.2 Destruction Rule

Удаляется:
- первая найденная пара;
- с суммой 10.

Порядок проверки:
1. vertical;
2. left;
3. right;
4. top.

---

## 9.3 Stabilization Cycle

После:
- gravity;
- destruction;

цикл повторяется до стабилизации.

---

# 10. Task Execution Model

## 10.1 Unit of Work

Task:
- переводит код из одного рабочего состояния в другое рабочее состояние.

Task должна:
- быть reviewable;
- быть bounded;
- быть testable;
- быть manually verifiable.

---

## 10.2 Execution Flow

Стандартный flow:
1. load bootstrap context;
2. load subsystem context;
3. load task file;
4. load relevant source files;
5. implementation;
6. tests;
7. build;
8. verification;
9. reporting;
10. history append.

---

## 10.3 Mutation Policy

Изменения должны:
- быть minimal;
- isolated;
- reviewable;
- task-scoped.

Запрещено:
- uncontrolled refactoring;
- unrelated mutations;
- speculative redesign.

---

## 10.4 Mutation Scope Freeze

После определения scope:
- не расширять mutation set;
- не подключать unrelated subsystems;
- не выполнять autonomous redesign.

---

# 11. Testing Model

## 11.1 Hybrid Testing

Testing model:
- hybrid.

Этапы разделены:
1. implementation;
2. tests;
3. build;
4. execution.

---

## 11.2 Unit Testing

Используется:
- GoogleTest.

Покрываются:
- critical public methods;
- round logic;
- collisions;
- ownership transitions.

---

## 11.3 Manual Testing

Обязательны:
- smoke checks;
- runtime verification;
- console behavior checks.

---

# 12. Build Model

## 12.1 Build Environment

- Visual Studio 2022
- MSBuild
- C++17
- Debug|x64

---

## 12.2 Build Principles

Build должен быть:
- reproducible;
- deterministic;
- minimally invasive.

---

## 12.3 Incremental Verification

Предпочитать:
- minimal rebuilds;
- local verification;
- task-scoped validation.

---

# 13. History Model

## 13.1 Append-only History

History:
- append-only;
- immutable;
- chronological.

---

## 13.2 Corrections

Corrections:
- append-only;
- не переписывают старые записи.

---

# 14. ADR Model

ADR используются для:
- architecture decisions;
- workflow decisions;
- governance changes.

Architecture changes:
- explicit;
- reviewable;
- approved by USER.

---

# 15. Anti-Overengineering Policy

Запрещено:
- premature abstraction;
- generalized systems without use-case;
- speculative frameworks;
- unnecessary extensibility.

Предпочитать:
- incremental evolution;
- minimal viable structures;
- task-driven growth.

---

# 16. Operational Discipline

Codex должен:
- избегать context bloat;
- избегать unrelated analysis;
- избегать speculative reasoning;
- избегать autonomous architecture drift.

Каждое изменение должно:
- быть locally understandable;
- иметь bounded scope;
- иметь explainable intent.

---

# 17. Long-Term Direction

Workflow должен:
- поддерживать дальнейший рост repository;
- поддерживать Linux;
- поддерживать Android;
- поддерживать future rendering backends;
- оставаться deterministic.

Core gameplay:
- platform-independent.

Platform implementations:
- isolated adapters.

---

# 18. Final Workflow Goals

Итоговые цели проекта:

## Technical

- stable gameplay core;
- deterministic round logic;
- stable ownership model;
- scalable architecture.

---

## Workflow

- scalable AI-assisted development;
- bounded context execution;
- minimal token usage;
- controllable repository growth.

---

## Governance

- human-controlled architecture;
- predictable mutations;
- reviewable evolution.

---

## Repository

- AI-native;
- deterministic;
- maintainable;
- scalable.

