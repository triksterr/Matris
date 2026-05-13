# File Registry

---

## chat_context_snapshot.md

### Purpose
Bootstrap operational context для нового чата.

### Authority
Medium

### When Loaded
Всегда первым.

### Update Frequency
Rare

### Update Policy
Обновляется только после:
- значимых workflow changes;
- architecture changes;
- operational priority changes.

### Must NOT Contain
- detailed architecture;
- subsystem implementation;
- full task history;
- detailed backlog.

### Contains
- current operational state;
- workflow summary;
- current priorities;
- bootstrap execution context.

### Related Files
- workflow/context_loading.md
- workflow/session_bootstrap.md
- runtime/current_stage.md
- workflow/repository_rules.md

### Notes
Snapshot:
- compact;
- bootstrap-oriented;
- not authoritative over source code.

---

## global_rules.md

### Purpose
Глобальные operational, governance и code-style правила проекта.

### Authority
High

### When Loaded
- bootstrap phase;
- before implementation tasks;
- before architecture-sensitive work.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении workflow philosophy;
- изменении governance model;
- изменении global coding rules.

### Must NOT Contain
- task-specific logic;
- detailed subsystem implementation;
- temporary operational notes;
- history records.

### Contains
- coding rules;
- governance rules;
- mutation restrictions;
- architecture constraints;
- workflow discipline;
- context discipline.

### Related Files
- workflow/repository_rules.md
- workflow/context_loading.md
- workflow/ai_behavior_rules.md
- workflow/mutation_policy.md

### Notes
Файл:
- high-authority;
- globally applicable;
- stable over time;
- not intended for frequent edits.

---

## runtime/current_stage.md

### Purpose
Текущий runtime operational state проекта.

### Authority
Medium-High

### When Loaded
- bootstrap phase;
- before task execution;
- before subsystem/task loading.

### Update Frequency
Medium

### Update Policy
Обновляется при:
- смене stage;
- изменении operational priorities;
- изменении blockers;
- изменении runtime constraints.

### Must NOT Contain
- detailed subsystem implementation;
- task history;
- detailed architecture docs;
- speculative future planning.

### Contains
- current stage;
- runtime constraints;
- gameplay targets;
- operational priorities;
- current blockers;
- stabilization goals.

### Related Files
- chat_context_snapshot.md
- workflow/context_loading.md
- workflow/task_execution.md
- tasks/active_tasks.md

### Notes
Файл:
- runtime-oriented;
- operational;
- frequently referenced;
- compact relative to full architecture docs.

---

## workflow/context_loading.md

### Purpose
Определяет bounded-context strategy и правила загрузки operational context.

### Authority
High

### When Loaded
- bootstrap phase;
- before task execution;
- before large context operations;
- during context recovery.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении context model;
- изменении loading strategy;
- изменении workflow philosophy;
- изменении repository scaling approach.

### Must NOT Contain
- subsystem implementation;
- task-specific execution;
- detailed architecture decisions;
- temporary operational notes.

### Contains
- context loading order;
- authority priorities;
- bounded-context rules;
- mutation scope discipline;
- context reload strategy;
- anti-context-bloat rules;
- scaling rules.

### Related Files
- chat_context_snapshot.md
- workflow/session_bootstrap.md
- workflow/repository_rules.md
- workflow/ai_behavior_rules.md
- workflow/mutation_policy.md

### Notes
Файл:
- critical for token economy;
- critical for deterministic execution;
- foundational for bounded-context workflow;
- important for long-term repository scaling.

---

## workflow/history_policy.md

### Purpose
Определяет immutable append-only policy для history и audit trail проекта.

### Authority
Medium-High

### When Loaded
- при работе с history;
- при завершении задач;
- при verification/reporting;
- при audit/reconstruction changes.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении history model;
- изменении audit requirements;
- изменении repository governance.

### Must NOT Contain
- task implementation;
- active operational context;
- subsystem architecture;
- speculative discussions.

### Contains
- append-only rules;
- correction policy;
- verification logging rules;
- archival policy;
- audit requirements;
- history granularity rules.

### Related Files
- workflow/reporting.md
- history/history_template.md
- tasks/active_tasks.md
- workflow/task_execution.md

### Notes
Файл:
- governs immutable project history;
- supports auditability;
- supports deterministic reconstruction;
- prevents silent history rewriting.

---

## workflow/mutation_policy.md

### Purpose
Определяет bounded mutation rules и governance для изменений repository.

### Authority
High

### When Loaded
- перед implementation tasks;
- перед code mutations;
- перед refactoring;
- при verification mutation scope.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении mutation model;
- изменении governance model;
- изменении repository workflow philosophy.

### Must NOT Contain
- subsystem implementation details;
- task-specific execution;
- temporary operational notes;
- architecture discussions outside mutation governance.

### Contains
- mutation boundaries;
- scope rules;
- autonomous change restrictions;
- reviewability rules;
- verification requirements;
- stabilization priorities.

### Related Files
- workflow/context_loading.md
- workflow/repository_rules.md
- workflow/task_execution.md
- workflow/ai_behavior_rules.md

### Notes
Файл:
- critical for deterministic development;
- limits uncontrolled AI mutations;
- protects repository stability;
- supports bounded-context execution.

---

## workflow/task_execution.md

### Purpose
Определяет deterministic task execution workflow и execution boundaries.

### Authority
High

### When Loaded
- перед implementation tasks;
- перед verification;
- перед task completion;
- during execution recovery.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении execution workflow;
- изменении verification model;
- изменении task lifecycle model.

### Must NOT Contain
- subsystem implementation;
- architecture decisions;
- detailed testing strategies;
- temporary operational notes.

### Contains
- execution flow;
- task lifecycle;
- verification rules;
- completion criteria;
- failure handling;
- execution recovery rules.

### Related Files
- workflow/mutation_policy.md
- workflow/testing.md
- workflow/reporting.md
- workflow/context_loading.md
- tasks/task_file_template.md

### Notes
Файл:
- governs deterministic execution;
- defines task lifecycle;
- protects bounded execution model;
- supports scalable AI-assisted workflow.

---

## workflow/testing.md

### Purpose
Определяет deterministic testing workflow и verification requirements проекта.

### Authority
High

### When Loaded
- перед verification;
- после implementation;
- при regression handling;
- перед task completion.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении testing model;
- изменении verification workflow;
- изменении deterministic testing strategy.

### Must NOT Contain
- subsystem implementation;
- task-specific logic;
- temporary debug procedures;
- architecture discussions outside testing scope.

### Contains
- testing workflow;
- verification stages;
- deterministic testing rules;
- runtime verification;
- smoke testing policy;
- regression handling.

### Related Files
- workflow/task_execution.md
- workflow/mutation_policy.md
- workflow/build_commands.md
- history/history_template.md

### Notes
Файл:
- governs repository verification;
- protects deterministic behavior;
- minimizes regression risk;
- supports scalable AI-assisted stabilization.

---

## workflow/reporting.md

### Purpose
Определяет deterministic reporting workflow и communication discipline проекта.

### Authority
Medium-High

### When Loaded
- during execution;
- during verification;
- during task completion;
- during failure reporting.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении reporting workflow;
- изменении communication standards;
- изменении repository execution model.

### Must NOT Contain
- subsystem implementation;
- architecture truth source;
- duplicated repository context;
- speculative redesign discussions.

### Contains
- reporting structure;
- mutation reporting rules;
- verification reporting;
- failure reporting;
- communication boundaries;
- context economy rules.

### Related Files
- workflow/task_execution.md
- workflow/testing.md
- workflow/history_policy.md
- workflow/ai_behavior_rules.md

### Notes
Файл:
- governs operational communication;
- minimizes token overhead;
- supports predictable review;
- stabilizes AI-human interaction workflow.

---

## workflow/subsystem_context_template.md

### Purpose
Шаблон для создания bounded subsystem architecture contexts.

### Authority
Template-Level

### When Loaded
- при создании subsystem contexts;
- при architecture stabilization;
- при onboarding новых subsystem areas.

### Update Frequency
Very Rare

### Update Policy
Изменяется только при:
- изменении subsystem context philosophy;
- изменении repository scaling strategy;
- изменении workflow architecture.

### Must NOT Contain
- concrete subsystem implementation;
- active task execution;
- duplicated source code;
- speculative architecture.

### Contains
- subsystem structure template;
- invariants template;
- ownership/lifecycle template;
- subsystem boundaries;
- verification expectations;
- deterministic subsystem modeling.

### Related Files
- workflow/context_loading.md
- workflow/repository_rules.md
- workflow/task_file_template.md
- subsystems/subsystem_index.md

### Notes
Файл:
- standardizes subsystem contexts;
- supports bounded-context loading;
- improves deterministic reasoning;
- supports scalable repository architecture.

---

## workflow/task_file_template.md

### Purpose
Шаблон для deterministic bounded task execution.

### Authority
Template-Level

### When Loaded
- при создании новых task files;
- при task decomposition;
- при task planning;
- при workflow onboarding.

### Update Frequency
Very Rare

### Update Policy
Изменяется только при:
- изменении task lifecycle model;
- изменении workflow execution philosophy;
- изменении bounded-task strategy.

### Must NOT Contain
- concrete implementation;
- subsystem architecture truth;
- duplicated repository rules;
- speculative planning outside task scope.

### Contains
- task lifecycle template;
- task scope template;
- verification requirements;
- mutation boundaries;
- escalation conditions;
- completion criteria.

### Related Files
- workflow/task_execution.md
- workflow/context_loading.md
- workflow/mutation_policy.md
- tasks/active_tasks.md

### Notes
Файл:
- standardizes task execution;
- supports bounded-context workflow;
- improves deterministic execution;
- keeps repository growth controllable.

---

## workflow/task_execution_checklist.md

### Purpose
Quick operational checklist для deterministic task execution.

### Authority
Operational Reference

### When Loaded
- перед implementation;
- перед verification;
- during execution;
- during recovery/debugging.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении execution workflow;
- изменении verification flow;
- изменении operational discipline.

### Must NOT Contain
- architecture decisions;
- subsystem implementation;
- long-form explanations;
- duplicated workflow policies.

### Contains
- execution checklist;
- mutation checklist;
- verification checklist;
- recovery reminders;
- operational discipline reminders.

### Related Files
- workflow/task_execution.md
- workflow/testing.md
- workflow/context_loading.md
- workflow/mutation_policy.md

### Notes
Файл:
- optimized for quick loading;
- supports deterministic execution;
- reduces operational mistakes;
- minimizes workflow drift.

---

## workflow/file_roles.md

### Purpose
Определяет роли repository files и responsibility boundaries.

### Authority
Medium-High

### When Loaded
- при repository onboarding;
- при workflow stabilization;
- при context-loading analysis;
- при repository scaling.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении repository structure;
- изменении workflow architecture;
- изменении file responsibility model.

### Must NOT Contain
- implementation details;
- subsystem logic;
- task execution details;
- duplicated architecture documentation.

### Contains
- file responsibilities;
- authority hierarchy;
- loading semantics;
- repository navigation rules;
- responsibility boundaries.

### Related Files
- workflow/context_loading.md
- workflow/file_registry.md
- workflow/repository_rules.md
- chat_context_snapshot.md

### Notes
Файл:
- standardizes repository navigation;
- reduces context ambiguity;
- supports deterministic loading;
- improves scalable AI-assisted workflow.

---

## workflow/repository_rules.md

### Purpose
Главный governance-файл repository workflow и repository discipline.

### Authority
High

### When Loaded
- during bootstrap;
- during workflow stabilization;
- during repository governance decisions;
- during architecture-sensitive operations.

### Update Frequency
Very Rare

### Update Policy
Изменяется только при:
- изменении repository governance;
- изменении workflow philosophy;
- изменении authority model;
- изменении repository scaling strategy.

### Must NOT Contain
- implementation details;
- subsystem-specific logic;
- task-specific execution;
- temporary operational decisions.

### Contains
- repository governance;
- authority hierarchy;
- workflow principles;
- repository discipline;
- scaling philosophy;
- deterministic development rules.

### Related Files
- global_rules.md
- workflow/context_loading.md
- workflow/mutation_policy.md
- workflow/file_roles.md
- workflow/ai_behavior_rules.md

### Notes
Файл:
- defines repository governance model;
- stabilizes workflow philosophy;
- protects deterministic execution;
- governs scalable AI-assisted development.

---

## workflow/ai_behavior_rules.md

### Purpose
Главный governance-файл поведения AI/Codex внутри repository workflow.

### Authority
High

### When Loaded
- during bootstrap;
- during execution;
- during recovery;
- during architecture-sensitive tasks.

### Update Frequency
Very Rare

### Update Policy
Изменяется только при:
- изменении AI workflow philosophy;
- изменении governance model;
- изменении repository execution model.

### Must NOT Contain
- subsystem implementation;
- task-specific execution;
- temporary operational notes;
- duplicated repository architecture.

### Contains
- AI operational behavior;
- execution constraints;
- bounded-context rules;
- governance boundaries;
- deterministic workflow behavior;
- escalation/recovery behavior.

### Related Files
- workflow/repository_rules.md
- workflow/context_loading.md
- workflow/mutation_policy.md
- workflow/task_execution.md
- global_rules.md

### Notes
Файл:
- stabilizes AI behavior;
- minimizes uncontrolled mutations;
- supports deterministic repository evolution;
- protects long-term workflow scalability.

---

## workflow/context_compaction.md

### Purpose
Определяет bounded-context strategy и context minimization workflow.

### Authority
Medium-High

### When Loaded
- during bootstrap;
- during long execution sessions;
- during recovery/reload;
- during repository scaling analysis.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении context-loading philosophy;
- изменении repository scaling strategy;
- изменении bounded-context workflow model.

### Must NOT Contain
- subsystem implementation;
- task execution logic;
- duplicated workflow rules;
- architecture-specific behavior.

### Contains
- context minimization rules;
- layered context strategy;
- token-efficiency rules;
- reload policies;
- context isolation rules;
- repository scaling principles.

### Related Files
- workflow/context_loading.md
- workflow/file_roles.md
- workflow/repository_rules.md
- chat_context_snapshot.md

### Notes
Файл:
- minimizes context explosion;
- stabilizes token usage;
- supports scalable AI-assisted execution;
- preserves deterministic operational reasoning.

---

## workflow/session_bootstrap.md

### Purpose
Определяет deterministic bootstrap workflow для новых chat/session execution cycles.

### Authority
Medium

### When Loaded
- при старте нового чата;
- после long interruption;
- после context drift;
- during recovery bootstrap.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении bootstrap workflow;
- изменении context initialization strategy;
- изменении repository onboarding model.

### Must NOT Contain
- subsystem implementation;
- task-specific mutations;
- duplicated workflow rules;
- detailed architecture docs.

### Contains
- bootstrap order;
- context initialization rules;
- incremental reload strategy;
- bounded startup workflow;
- recovery bootstrap behavior.

### Related Files
- workflow/context_loading.md
- workflow/context_compaction.md
- chat_context_snapshot.md
- runtime/current_stage.md

### Notes
Файл:
- minimizes startup overhead;
- stabilizes session initialization;
- supports predictable context loading;
- improves scalable AI-assisted onboarding.

---

## workflow/build_commands.md

### Purpose
Определяет deterministic build workflow и build verification rules проекта.

### Authority
Medium

### When Loaded
- during build verification;
- during task completion;
- during runtime validation;
- during build failure recovery.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении build environment;
- изменении build pipeline;
- изменении platform support strategy;
- изменении verification workflow.

### Must NOT Contain
- subsystem implementation;
- task-specific logic;
- duplicated workflow governance;
- unrelated architecture documentation.

### Contains
- build environment rules;
- MSBuild usage;
- verification commands;
- incremental build policy;
- build failure handling;
- runtime launch verification.

### Related Files
- workflow/testing.md
- workflow/task_execution.md
- runtime/current_stage.md
- global_rules.md

### Notes
Файл:
- stabilizes build workflow;
- minimizes rebuild overhead;
- supports deterministic verification;
- preserves reproducible development environment.

---

## workflow/file_registry.md

### Purpose
Central metadata registry всех operational repository files.

### Authority
Medium

### When Loaded
- during repository navigation;
- during bootstrap analysis;
- during context-loading planning;
- during workflow onboarding.

### Update Frequency
Frequent

### Update Policy
Обновляется append-only/iteratively:
- при создании новых workflow files;
- при создании subsystem contexts;
- при изменении repository structure.

### Must NOT Contain
- implementation details;
- duplicated full documents;
- large prose explanations;
- source-code excerpts.

### Contains
- file purposes;
- loading semantics;
- authority levels;
- update frequencies;
- repository navigation metadata.

### Related Files
- workflow/file_roles.md
- workflow/context_loading.md
- workflow/repository_rules.md

### Notes
Файл:
- acts as repository navigation index;
- improves deterministic context loading;
- reduces repository ambiguity;
- supports scalable AI-assisted workflow.

---

## history/history_template.md

### Purpose
Шаблон append-only history records и deterministic audit logging.

### Authority
Medium

### When Loaded
- during history updates;
- during audit review;
- during correction logging;
- during workflow stabilization.

### Update Frequency
Rare

### Update Policy
Изменяется только при:
- изменении history format;
- изменении audit requirements;
- изменении workflow logging model.

### Must NOT Contain
- implementation details;
- subsystem architecture;
- speculative reasoning;
- duplicated operational context.

### Contains
- history record templates;
- correction record templates;
- failure record templates;
- audit formatting rules;
- append-only logging structure.

### Related Files
- workflow/history_policy.md
- workflow/reporting.md
- workflow/task_execution.md

### Notes
Файл:
- standardizes audit logging;
- improves deterministic reporting;
- preserves append-only history discipline;
- supports scalable operational auditability.

---

## tasks/active_tasks.md

### Purpose
Главный operational task queue текущего execution stage.

### Authority
Medium

### When Loaded
- during task selection;
- during execution planning;
- during bootstrap;
- during workflow stabilization.

### Update Frequency
Frequent

### Update Policy
Обновляется:
- при изменении task statuses;
- при добавлении новых tasks;
- при completion/blocking tasks;
- при stage transitions.

### Must NOT Contain
- large task descriptions;
- subsystem implementation details;
- architecture redesign discussions;
- duplicated task contexts.

### Contains
- active task queue;
- execution priorities;
- task ordering;
- blocked tasks;
- operational execution state.

### Related Files
- workflow/task_execution.md
- workflow/task_file_template.md
- runtime/current_stage.md
- history/history_template.md

### Notes
Файл:
- acts as operational scheduler;
- supports bounded task execution;
- stabilizes sequential workflow;
- minimizes execution ambiguity.

---

## tasks/backlog.md

### Purpose
Operational planning backlog и reservoir будущих task units.

### Authority
Medium

### When Loaded
- during task planning;
- during prioritization;
- during stage preparation;
- during execution queue updates.

### Update Frequency
Frequent

### Update Policy
Обновляется:
- при добавлении новых tasks;
- при reprioritization;
- при stage transitions;
- при moving tasks between ACTIVE/BACKLOG/DEFERRED.

### Must NOT Contain
- execution history;
- detailed implementation notes;
- architecture redesign discussions;
- duplicated task contexts.

### Contains
- backlog tasks;
- deferred tasks;
- priority ordering;
- future-stage planning;
- operational task reservoir.

### Related Files
- tasks/active_tasks.md
- workflow/task_file_template.md
- runtime/current_stage.md
- workflow/task_execution.md

### Notes
Файл:
- supports bounded execution planning;
- stabilizes prioritization workflow;
- separates planning from execution;
- preserves scalable task management.

---

## adr/ADR-0001-workflow-foundation.md

### Purpose
Foundational ADR, определяющий базовую workflow architecture и governance model repository.

### Authority
High

### When Loaded
- during workflow bootstrap;
- during architecture governance;
- during workflow redesign discussions;
- during repository scaling decisions.

### Update Frequency
Very Rare

### Update Policy
Изменяется только:
- после explicit USER approval;
- при major workflow redesign;
- при foundational governance changes.

### Must NOT Contain
- task-specific details;
- implementation specifics;
- operational history;
- subsystem implementation notes.

### Contains
- workflow foundation decisions;
- governance model;
- context-loading strategy;
- mutation philosophy;
- repository operational model.

### Related Files
- workflow/repository_rules.md
- workflow/context_loading.md
- workflow/mutation_policy.md
- workflow/ai_behavior_rules.md

### Notes
Файл:
- acts as foundational governance ADR;
- stabilizes repository operational philosophy;
- defines deterministic AI-assisted workflow model;
- minimizes future workflow ambiguity.

---

## risks/known_risks.md

### Purpose
Operational registry известных architectural, workflow и technical risks проекта.

### Authority
Medium-High

### When Loaded
- during architecture-sensitive tasks;
- during ownership/lifecycle changes;
- during workflow stabilization;
- during risk review and verification planning.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при обнаружении новых risks;
- при mitigation updates;
- при architecture changes;
- при workflow stabilization changes.

### Must NOT Contain
- execution history;
- speculative brainstorming;
- detailed implementation notes;
- duplicated subsystem documentation.

### Contains
- architectural risks;
- workflow risks;
- platform risks;
- testing risks;
- operational risks;
- mitigation strategies;
- detection patterns;
- ownership responsibility.

### Related Files
- workflow/mutation_policy.md
- workflow/testing.md
- workflow/repository_rules.md
- adr/ADR-0001-workflow-foundation.md

### Notes
Файл:
- supports deterministic stabilization;
- tracks high-risk repository areas;
- prevents silent architecture drift;
- improves bounded operational reasoning.

---

## tasks/task_naming_rules.md

### Purpose
Defines deterministic naming conventions и lifecycle rules для operational task files.

### Authority
Medium

### When Loaded
- during task creation;
- during backlog maintenance;
- during task review;
- during repository scaling.

### Update Frequency
Rare

### Update Policy
Обновляется:
- при evolution task workflow;
- при scaling task system;
- при naming convention stabilization.

### Must NOT Contain
- execution history;
- task implementation details;
- architecture discussions;
- backlog content.

### Contains
- task ID conventions;
- task filename rules;
- lifecycle states;
- naming semantics;
- task granularity guidance.

### Related Files
- workflow/task_file_template.md
- tasks/active_tasks.md
- tasks/backlog.md
- workflow/task_execution.md

### Notes
Файл:
- stabilizes task navigation;
- improves deterministic task lookup;
- supports scalable repository organization;
- minimizes task-management ambiguity.

---

## subsystems/entity_cube.md

### Purpose
Defines architecture, invariants и ownership rules subsystem Cube.

### Authority
High

### When Loaded
- before cube-related tasks;
- during ownership/lifecycle analysis;
- during Layers/Figure integration work;
- during pointer-safety verification.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при stabilization ownership model;
- при lifecycle changes;
- при invariant clarification;
- при subsystem evolution.

### Must NOT Contain
- rendering implementation;
- platform-specific logic;
- task execution history;
- speculative gameplay systems.

### Contains
- cube invariants;
- ownership rules;
- lifecycle semantics;
- coordinate rules;
- pointer safety constraints;
- deterministic behavior requirements.

### Related Files
- cube.h
- cube.cpp
- subsystems/entity_figure.md
- subsystems/layers.md

### Notes
Файл:
- defines lowest-level gameplay entity;
- stabilizes ownership expectations;
- supports deterministic gameplay behavior;
- acts as shared primitive contract between subsystems.

---

## subsystems/entity_figure.md

### Purpose
Defines architecture, ownership и deterministic movement rules subsystem Figure.

### Authority
High

### When Loaded
- before figure-related tasks;
- during movement/rotation stabilization;
- during ownership transfer changes;
- during collision validation analysis.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при stabilization movement logic;
- при ownership model evolution;
- при lifecycle clarification;
- при geometry model changes.

### Must NOT Contain
- rendering implementation;
- platform-specific logic;
- round orchestration details;
- unrelated gameplay systems.

### Contains
- movement model;
- rotation model;
- ownership semantics;
- collision responsibilities;
- lifecycle rules;
- deterministic behavior requirements.

### Related Files
- figure.h
- figure.cpp
- subsystems/entity_cube.md
- subsystems/layers.md
- subsystems/round_rules.md

### Notes
Файл:
- defines active gameplay entity behavior;
- stabilizes movement and rotation invariants;
- formalizes ownership transfer semantics;
- supports deterministic gameplay execution.

---

## subsystems/layers.md

### Purpose
Defines authoritative occupancy storage и collision validation subsystem Layers.

### Authority
High

### When Loaded
- before collision-related tasks;
- during occupancy validation work;
- during pointer-safety stabilization;
- during gravity/destruction integration tasks.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при storage model stabilization;
- при collision logic clarification;
- при pointer-safety changes;
- при occupancy model evolution.

### Must NOT Contain
- rendering implementation;
- gameplay orchestration;
- platform-specific logic;
- speculative storage abstractions.

### Contains
- occupancy rules;
- bounds validation semantics;
- ownership boundaries;
- collision responsibilities;
- coordinate system rules;
- deterministic lookup behavior.

### Related Files
- layers.h
- layers.cpp
- subsystems/entity_cube.md
- subsystems/entity_figure.md
- subsystems/round_rules.md

### Notes
Файл:
- defines authoritative gameplay field state;
- stabilizes collision responsibilities;
- formalizes non-owning storage semantics;
- supports deterministic gameplay validation.

---

## subsystems/round_rules.md

### Purpose
Defines deterministic gameplay rules, stabilization cycle и round orchestration subsystem.

### Authority
High

### When Loaded
- before gameplay-rule tasks;
- during gravity/destruction stabilization;
- during deterministic behavior analysis;
- during round orchestration changes.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при gameplay rule evolution;
- при stabilization-cycle changes;
- при deterministic execution clarification;
- при round parameter updates.

### Must NOT Contain
- rendering implementation;
- platform-specific logic;
- low-level storage ownership;
- speculative generalized gameplay engines.

### Contains
- gravity rules;
- destruction rules;
- stabilization-cycle semantics;
- execution-order guarantees;
- deterministic gameplay requirements;
- round parameter behavior.

### Related Files
- rules.h
- rules.cpp
- round.h
- round.cpp
- subsystems/layers.md
- subsystems/entity_figure.md

### Notes
Файл:
- defines authoritative gameplay rule execution;
- stabilizes deterministic round behavior;
- formalizes gameplay execution ordering;
- supports reproducible gameplay state transitions.

---

## subsystems/game_loop.md

### Purpose
Defines deterministic gameplay orchestration и frame execution subsystem Game Loop.

### Authority
High

### When Loaded
- before gameplay orchestration tasks;
- during timing stabilization;
- during update-order analysis;
- during lifecycle sequencing work.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при loop architecture evolution;
- при timing model changes;
- при lifecycle clarification;
- при sequencing stabilization.

### Must NOT Contain
- rendering implementation;
- platform-specific APIs;
- low-level gameplay storage;
- speculative async systems.

### Contains
- execution sequencing;
- timing behavior;
- gameplay lifecycle rules;
- update-order guarantees;
- deterministic orchestration semantics.

### Related Files
- round.h
- round.cpp
- subsystems/round_rules.md
- subsystems/entity_figure.md
- subsystems/platform_console.md

### Notes
Файл:
- defines top-level gameplay orchestration;
- stabilizes deterministic frame execution;
- formalizes update-order guarantees;
- coordinates gameplay subsystem interaction.

---

## subsystems/platform_console.md

### Purpose
Defines Windows console platform adapter subsystem и platform isolation rules.

### Authority
High

### When Loaded
- before platform-specific tasks;
- during rendering/input integration;
- during WinAPI isolation work;
- during platform abstraction stabilization.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при platform-layer evolution;
- при adapter stabilization;
- при input/render integration changes;
- при cross-platform preparation.

### Must NOT Contain
- gameplay rules;
- gameplay orchestration;
- low-level gameplay ownership;
- speculative rendering frameworks.

### Contains
- platform adapter responsibilities;
- WinAPI isolation rules;
- render/input integration boundaries;
- platform determinism constraints;
- cross-platform architecture goals.

### Related Files
- c_render.h
- c_render.cpp
- subsystems/game_loop.md
- workflow/repository_rules.md

### Notes
Файл:
- isolates platform-specific behavior;
- protects gameplay core portability;
- formalizes adapter-layer boundaries;
- supports future multi-platform migration.

---

## subsystems/subsystem_index.md

### Purpose
Defines high-level subsystem map и architecture navigation structure.

### Authority
Medium-High

### When Loaded
- during bootstrap;
- before subsystem selection;
- during architecture navigation;
- during task routing.

### Update Frequency
Incremental

### Update Policy
Обновляется:
- при добавлении subsystem;
- при architecture restructuring;
- при boundary clarification;
- при dependency model evolution.

### Must NOT Contain
- implementation details;
- task execution history;
- detailed gameplay logic;
- duplicated subsystem documentation.

### Contains
- subsystem map;
- dependency overview;
- subsystem responsibilities;
- architecture routing guidance;
- loading recommendations.

### Related Files
- subsystems/entity_cube.md
- subsystems/entity_figure.md
- subsystems/layers.md
- workflow/context_loading.md

### Notes
Файл:
- acts as subsystem navigation hub;
- minimizes bootstrap ambiguity;
- supports bounded context loading;
- reduces architecture navigation cost.

---

## workflow/context_ignore_rules.md

Назначение:
- centralized ignore/loading exclusion policy;
- context minimization rules;
- anti-context-bloat policy;
- operational context compaction rules.

Authority:
High workflow authority.

Файл определяет:
- какие папки/файлы не загружать по умолчанию;
- какие build artifacts игнорировать;
- какие legacy/archive areas исключать из active context;
- правила selective source loading;
- правила context compaction после file inspection.

Используется для:
- bounded context loading;
- token usage minimization;
- deterministic repository navigation;
- scalable AI-assisted execution.

Основные категории:
- always-ignore paths;
- usually-ignore paths;
- conditional loading rules;
- source loading restrictions;
- context compaction rules.

Связанные файлы:
- workflow/context_loading.md
- workflow/task_execution.md
- runtime/current_stage.md
- tasks/task_file_template.md

Основные правила:
- не загружать unrelated source trees;
- не загружать build artifacts;
- не загружать archive/history без необходимости;
- сохранять только task-relevant operational context;
- минимизировать retained reasoning state после file analysis.
