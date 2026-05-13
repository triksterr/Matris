# Context Ignore Rules

## Always Ignore

`.vs/`
`x64/`
`Debug/`
`Release/`
`build/`
`bin/`
`obj/`
`.cache/`
`.vscode/`
`prj/user/`
`*.lnk`

---

## Usually Ignore

`archive/`
`history/`
`legacy/`

---

## Ignore Unless Explicitly Requested

full backlog
unrelated subsystem docs
old snapshots
obsolete task files

---

## Source Loading Rules

Do not load entire source trees.
Do not load unrelated cpp/h files.
Prefer task-scoped source loading.

---

## Context Compaction Rules

After source inspection:
- retain only task-relevant information;
- discard unrelated file content from active context;
- minimize retained reasoning state;
- prefer compact operational summaries over full file retention.
