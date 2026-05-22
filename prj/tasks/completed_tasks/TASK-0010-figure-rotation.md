# TASK-0010 - Figure Rotation/Move Stabilization

## Status
DONE

---

## Context Budget
SMALL

---

## Priority
P0

---

## Stage
WIN_CONSOLE_V1

---

## Goal
Stabilize `Figure` rotation and movement logic with collision and bounds validation.

---

## Subsystem
Primary:
- entity_figure

Related:
- layers
- round_rules

---

## Relevant Context Files
- prj/subsystems/entity_figure.md
- prj/workflow/task_execution.md
- prj/workflow/testing.md

---

## Relevant Source Files
- cons_test/figure.h
- cons_test/layers.h
- cons_test/rules.h
- test/test.vcxproj
- test/test_figure_num_sync.cpp

---

## Allowed Mutation Scope
- Figure rotate/chkRotate/move implementation.
- Figure collision checks against Layers.
- Focused unit tests for move/rotate validation.

---

## Required Verification
- build: matris.sln Debug|x64
- tests: x64\Debug\test.exe --gtest_color=no
- targeted review of rotate/move invariants

---

## Completion Criteria
- `Figure` move/rotate methods implemented and deterministic.
- rotate validation rejects invalid rotations (bounds/collision).
- move validation rejects invalid moves (bounds/collision).
- build/tests pass.

---

## Completion Actions
After successful completion:
- update active_tasks.md
- update backlog.md if required
- append history record
- move completed task file from tasks/ to tasks/completed_tasks/

---

## Reporting
Required:
- concise mutation summary
- concise verification summary
- Manual Check For USER
- Manual Check Accents
