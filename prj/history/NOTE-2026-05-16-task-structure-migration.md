# Note: Task Structure Migration (2026-05-16)

## Type
Operational workflow note.

## Summary
Task file layout under `prj/tasks` was simplified to remove extra nesting.

## Applied Changes
- Active/current/ready task files are stored directly in `prj/tasks/`.
- Folder `prj/tasks/active/` was removed.
- Folder `prj/tasks/archive/completed_tasks/` was moved to `prj/tasks/completed_tasks/`.
- After completion, task files must be moved from `prj/tasks/` to `prj/tasks/completed_tasks/`.

## Effective Policy
- `prj/tasks/` is the active task area.
- `prj/tasks/completed_tasks/` is immutable historical storage for completed task files.
- Completed task files are not part of default operational loading context.
