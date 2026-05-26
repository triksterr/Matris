# Global Rules

## 1. Authority & Priority

High-authority operational rules.

Priority order:

1. Current chat instructions
2. This file (`global_rules.md`)
3. Existing project architecture and code style
4. Other contextual assumptions

Conflict resolution:

- Source code is authoritative for existing implementation details.
- This file is authoritative for workflow, governance, architecture, and code-style rules.
- User changes are authoritative and must be preserved unless explicit approval is given to modify or revert them.

---

## 2. Language & Communication

- Chat language: Russian
- Code language: C++17
- Code comments: Russian
- Text file encoding: UTF-8

Response style:

- concise,
- factual,
- low-noise,
- without filler.

Avoid explaining basic concepts unless requested.

For non-trivial tasks:

- briefly outline the intended approach when useful.

If the request is ambiguous, incomplete, contradictory, or conflicts with current context:

- ask clarifying questions before proceeding.

Do not make implicit assumptions in critical technical or architectural areas.

Moderate initiative is allowed:

- suggest improvements or safer alternatives when useful,
- avoid aggressive workflow redirection.

Point out relevant user mistakes or inconsistencies directly.

Avoid unnecessary apologies and over-formatting.

---

## 3. Context Discipline

Use bounded-context execution.

Requirements:

- load only task-relevant files/subsystems,
- avoid unnecessary context expansion,
- prefer minimal mutation scope,
- avoid speculative redesign,
- avoid unrelated refactoring without explicit approval.

Monitor context quality proactively:

- context overflow,
- fragmentation,
- semantic drift,
- excessive repetition,
- loss of important constraints.

If context quality degrades:

- compact and stabilize context,
- preserve decisions, constraints, terminology, and invariants,
- reduce redundancy,
- maintain semantic density.

Prefer:

- deterministic behavior,
- predictable execution,
- reviewable isolated changes,
- incremental stabilization.

---

## 4. Workflow Governance

Each task must preserve a valid working project state.

Requirements:

- prefer incremental changes over mass rewrites,
- keep changes reviewable and isolated,
- build/test verification is mandatory for critical logic,
- architecture changes require explicit USER approval,
- scope expansion requires explicit USER approval.

User modifications policy:

- any detected file modification is treated as a user modification by default,
- do not overwrite, revert, or restructure user changes without explicit confirmation,
- clarification about user modifications is allowed when necessary.

---

## 5. Architecture Rules

Architecture goals:

- separate platform-independent game logic from platform-specific code,
- isolate platform-dependent subsystems:
  - console,
  - keyboard/input,
  - sound,
  - file I/O,
  - windowing/platform adapters.

Cross-platform discipline:

- avoid unnecessary WinAPI coupling,
- consider future Linux/Android portability where relevant,
- platform-independent logic must not unnecessarily depend on platform APIs.

Module design:

- prefer small modules with a single clear responsibility,
- avoid unnecessary subsystem coupling.

---

## 6. Code Rules

General:

- avoid unnecessary global variables,
- prefer clear code over premature optimization,
- do not modify stable/archive code without real necessity,
- update subsystem documentation when introducing subsystem-level entities.

C++ restrictions:

- standard: strictly C++17,
- exceptions (`try/catch`) are forbidden,
- use bool/enum/error-code based error handling,
- RTTI (`dynamic_cast`, `typeid`) is forbidden unless real necessity is approved.

Memory management:

- follow existing project patterns first,
- raw pointers, `new/delete`, `unique_ptr`, `shared_ptr` are allowed where appropriate,
- avoid unnecessary architectural rewrites of ownership models.

Style conventions:

- current existing class names in this repository are kept as-is (no mass renaming),
- for new identifiers use camelCase by default unless subsystem style explicitly differs,
- file names: snake_case.h / snake_case.cpp,
- prefixes like `m_`, `g_`, `s_` are forbidden.

Containers & language features:

- STL containers are allowed where appropriate,
- avoid exotic containers or nonstandard abstractions unless explicitly justified,
- `auto` and range-for usage should follow existing project style and local consistency.

Macros:

Allowed:

- include guards,
- platform conditionals,
- compile-time feature flags.

Forbidden:

- functional-style macros replacing language constructs.

Assertions & logging:

- use assert extensively for invariants and impossible states in core logic,
- platform adapters should assert preconditions where appropriate,
- logging is mandatory for:
  - I/O failures,
  - platform API failures.

Logging requirements:

- levels: Error / Warn / Info,
- avoid per-frame spam in game/render loops.

Comments:

- comments must explain non-obvious logic,
- prefer concise but sufficiently informative comments.
- for new or substantially changed logic, use dense explanatory comments at the same level as in current `figure.h` and `cube.h` updates:
  - explain ownership/lifecycle contracts,
  - explain algorithm steps and validation order,
  - explain function intent, inputs, outputs, and side effects where relevant.
- do not leave new complex logic blocks under-commented.

Documentation encoding:

- documentation files (`.md`, `.h` used as docs/templates) must be UTF-8 without BOM,
- exception: Microsoft Visual Studio project/service files may use their native encoding if required by the toolchain.

---

## 7. File & Navigation Conventions

Navigation comments must use the exact format:

` Link:..\path\file.cpp `
` Link:..\path\file.cpp#L14 `
` Link:..\path\file.cpp:"Anchor text" `

Rules:

- keyword must be exactly ` Link: `
- one link per line
- compatible with MS Visual Studio navigation plugins

---

## 8. Technical Environment

Default environment:

- OS: Windows 10
- IDE: MS Visual Studio 2022
- Language: C++17

Assume existing project conventions are important unless explicitly overridden.

When multiple valid implementations exist:

- prefer the solution that minimizes architectural disruption and mutation scope.
