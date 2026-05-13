# Current Stage

## Stage Role

Current Stage:
- runtime operational context;
- active development constraints layer;
- current execution priority layer.

Файл НЕ является:
- полной gameplay specification;
- subsystem documentation;
- architecture source of truth.

---

## Authority

Runtime operational context.

Authority level:
Medium-High

Определяет:
- текущий active stage;
- текущие priorities;
- текущие runtime constraints.

При конфликте:
- source code authoritative;
- task file authoritative для task scope;
- subsystem docs authoritative для subsystem semantics;
- данный файл authoritative для current runtime direction.

---

## Current Stage

WIN_CONSOLE_V1

---

## Stage Goals

Стабилизировать минимально рабочее ядро консольной версии:
- platform-independent gameplay core;
- console platform layer;
- deterministic gameplay execution;
- stable round behavior;
- reproducible build/test workflow;
- bounded workflow execution.

---

## Current Platform

- MS Windows
- Console
- Pseudographics
- Keyboard input

---

## Current Non-Goals

Current stage intentionally excludes:
- filesystem persistence;
- audio;
- windowed graphics;
- Linux;
- Android;
- multiplayer;
- networking;
- generalized gameplay frameworks;
- asynchronous execution models;
- advanced rendering systems.

---

## Base Technical Constraints

- Visual Studio 2022
- MSBuild
- Debug|x64
- C++17
- no try/catch
- no RTTI
- no uncontrolled refactoring

---

## Runtime Gameplay Constraints

Current gameplay constraints:
- deterministic gravity execution;
- deterministic destruction ordering;
- deterministic stabilization cycle;
- stable lock-delay behavior;
- stable collision validation.

---

## Timing Constraints

Timing target:
- 60 FPS approximate;
- deterministic gameplay priority выше visual precision.

---

## Active Technical Focus

Current stabilization areas:
- ownership/lifetime safety;
- rotation validation;
- collision determinism;
- nullptr safety;
- bounded reviewable mutations;
- deterministic gameplay sequencing.

---

## Current Operational Priorities

Priority order:
1. correctness
2. deterministic gameplay behavior
3. repository stability
4. bounded task scope
5. reviewability
6. testability
7. token efficiency

---

## Current Execution Strategy

Workflow:
- sequential semi-autonomous;
- single active task;
- subsystem-first loading;
- bounded context execution;
- minimal mutation scope.

---

## Definition Of Stable State

Current stage считается стабилизированным только если:
- gameplay behavior deterministic;
- rotation/collision stable;
- fixation sequencing stable;
- round execution reproducible;
- build reproducible;
- tests reproducible;
- smoke verification stable.

---

## Current Known Blocking Areas

Current blocking areas:
- ownership model stabilization;
- rotation/collision edge cases;
- nullptr safety gaps;
- deterministic fixation sequencing.

---

## Architecture Direction

Gameplay core:
- platform-independent;
- deterministic;
- minimally coupled.

Platform layer:
- isolated adapters;
- replaceable implementations;
- minimal gameplay impact.

Ownership direction:
- Figure owns active cubes;
- Layers stores non-owning Cube* references.

Primary migration direction:
`std::vector<std::unique_ptr<Cube>>`

---

## Verification Priorities

Current verification focus:
- deterministic gameplay behavior;
- stable build execution;
- reproducible runtime behavior;
- bounded regression scope;
- isolated subsystem verification.

---

## Drift Rule

If runtime behavior diverges from this file:
- source code authoritative;
- subsystem docs authoritative for subsystem semantics;
- current_stage updated selectively.