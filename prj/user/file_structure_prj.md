# File Structure

prj/
├── chat_context_snapshot.md - Bootstrap operational context для нового чата.
├── global_rules.md - Глобальные operational, governance и code-style правила проекта.
├── runtime/
│   └── current_stage.md - Текущий runtime operational state проекта.
├── workflow/
│   ├── context_loading.md - Определяет bounded-context strategy и правила загрузки operational context.
│   ├── history_policy.md - Определяет immutable append-only policy для history и audit trail проекта.
│   ├── mutation_policy.md - Определяет bounded mutation rules и governance для изменений repository.
│   ├── task_execution.md - Определяет deterministic task execution workflow и execution boundaries.
│   ├── testing.md - Определяет deterministic testing workflow и verification requirements проекта.
│   ├── reporting.md - Определяет deterministic reporting workflow и communication discipline проекта.
│   ├── subsystem_context_template.md - Шаблон для создания bounded subsystem architecture contexts.
│   ├── task_file_template.md - Шаблон для deterministic bounded task execution.
│   ├── task_execution_checklist.md - Quick operational checklist для deterministic task execution.
│   ├── file_roles.md - Определяет роли repository files и responsibility boundaries.
│   ├── repository_rules.md - Главный governance-файл repository workflow и repository discipline.
│   ├── ai_behavior_rules.md - Главный governance-файл поведения AI/Codex внутри repository workflow.
│   ├── context_compaction.md - Определяет bounded-context strategy и context minimization workflow.
│   ├── session_bootstrap.md - Определяет deterministic bootstrap workflow для новых chat/session execution cycles.
│   ├── build_commands.md - Определяет deterministic build workflow и build verification rules проекта.
│   ├── context_ignore_rules.md - Определяет Context/File/Folder Ignore Rules.
│   └── file_registry.md - Central metadata registry всех operational repository files.
├── subsystems/
│   ├── subsystem_index.md - Defines high-level subsystem map и architecture navigation structure.
│   ├── entity_cube.md - Defines architecture, invariants и ownership rules subsystem Cube.
│   ├── entity_figure.md - Defines architecture, ownership и deterministic movement rules subsystem Figure.
│   ├── layers.md - Defines authoritative occupancy storage и collision validation subsystem Layers.
│   ├── round_rules.md - Defines deterministic gameplay rules, stabilization cycle и round orchestration subsystem.
│   ├── game_loop.md - Defines deterministic gameplay orchestration и frame execution subsystem Game Loop.
│   └── platform_console.md - Defines Windows console platform adapter subsystem и platform isolation rules.
├── tasks/
│   ├── active_tasks.md - Главный operational task queue текущего execution stage.
│   ├── task_naming_rules.md - Defines deterministic naming conventions и lifecycle rules для operational task files.
│   ├── backlog.md - Operational planning backlog и reservoir будущих task units.
│   ├── TASK-XXXX.md - Current task...
│   └── ...
├── history/
│   ├── history_template.md - Шаблон append-only history records и deterministic audit logging.
│   ├── history_YYYY_QX.md - Current history...
│   └── ...
├── adr/
│   ├── ADR-0001-workflow-foundation.md - Foundational ADR, определяющий базовую workflow architecture и governance model repository.
│   └── ...
├── risks/
│   └── known_risks.md - Operational registry известных architectural, workflow и technical risks проекта.
├── legacy/ - старые файлы предыдущих этапов workflow
│   ├── Codex.txt
│   ├── chat_context_snapshot.md
│   ├── class_method_analysis_report.md
│   └── Codex_todo.txt
├── archive/ - архивные файлы workflow проекта
│   └── ...
└── user/ - файлы пользователя, не имеющие прямого отношения в workflow проекта
    └── ...


---

# Будущие возможные дополнения

## Vocabulary

workflow/workflow_vocabulary.md - сейчас не нужен:

Сейчас vocabulary уже:
достаточно стабилен;
компактно распределен по workflow docs;
не создает критической ambiguity.

Отдельный workflow_vocabulary.md обычно появляется позже, когда:
subsystem count сильно растет;
появляется несколько AI agents;
начинается drift терминов;
появляются сокращения/aliases;
workflow становится слишком большим.

Для текущего Workflow V1 отдельный vocabulary file пока не обязателен.

---

## ADR template

adr/ADR-template.md - сейчас не нужен:

На текущем этапе отдельный ADR template не обязателен.

И это даже соответствует вашему подходу:

минимизация лишних workflow artifacts;
отсутствие premature abstraction;
repository grows incrementally.
