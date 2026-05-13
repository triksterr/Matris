# Build Commands

## Authority

Medium-authority build and verification policy.

---

## Build Philosophy

Build system должен:
- поддерживать deterministic verification;
- поддерживать minimal rebuild workflow;
- минимизировать verification cost.

---

## Основная сборочная среда

- Microsoft Visual Studio 2022
- MSBuild
- C++17

---

## Основная конфигурация сборки

Debug|x64

---

## Рабочие пути

Корень проекта:
`C:\Users\Alex\Documents\prog\matris`

Рабочий проект:
`C:\Users\Alex\Documents\prog\matris\cons_test`

Папка документации workflow:
`C:\Users\Alex\Documents\prog\matris\prj`

---

## Solution File

`C:\Users\Alex\Documents\prog\matris\matris.sln`

---

## Основной рабочий проект

`cons_test`

---

## MSBuild

Использовать: MSBuild из PATH
Если недоступен:
C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe

---

## Стандартная команда сборки

Пример:
MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64

---

## Базовые требования к сборке

Сборка должна:
- выполняться без ручных исправлений;
- не требовать изменения solution/project files;
- завершаться без critical errors;
- использовать актуальные исходники.

---

## Startup Binary

Основной startup target:
`cons_test`

Запуск:
- из Visual Studio;
- напрямую из консоли Windows.

---

## Startup Verification

После сборки необходимо проверить:
- запуск из Visual Studio;
- запуск бинарника напрямую из консоли.

Startup verification:
- не заменяет gameplay verification;
- не заменяет smoke testing;
- подтверждает только launch/runtime viability.

---

## Build Artifacts

Артефакты сборки:
- не являются source code;
- не используются как context;
- не изменяются вручную.

Игнорировать:
`.vs/`
`x64/`
`Debug/`
`Release/`
`build/`
`bin/`
`obj/`
`.cache/`
`.vscode/`
`cons_test/x64/`
`cons_test/cons_test/`
`prj/user/`
`.ipch/`
`*.obj`
`*.pdb`
`*.ilk`

---

## Build Failure Policy

Если сборка не проходит:
- определить scope ошибки;
- проверить связь с текущей задачей;
- не исправлять unrelated build problems без согласования;
- зафиксировать проблему в history/task results.

---

## Warning Policy

Новые warnings:
- анализировать;
- фиксировать в reporting;
- не игнорировать silently.

Unrelated legacy warnings:
- не исправлять автоматически вне task scope.

---

## Clean Rebuild Policy

Clean rebuild выполнять только:
- при проблемах incremental build;
- после значимых build-system изменений;
- при подозрении на stale artifacts.

По умолчанию использовать incremental build.

---

## Incremental Build Policy

По возможности:
- минимизировать rebuild scope;
- не выполнять unnecessary clean rebuild;
- использовать task-scoped verification.

---

## Test Build Policy

Unit tests:
- должны собираться отдельно;
- не должны изменять production build pipeline;
- не должны требовать platform-specific hacks.

---

## Test Build Isolation

Unit tests не должны:
- ломать production build;
- изменять production configuration;
- требовать platform-specific workaround.

---

## Future Platforms

Текущий этап: 
WIN_CONSOLE_V1

Следующие этапы:
1. Windows windowed graphics
2. Linux
3. Android

Build workflow должен оставаться расширяемым.

---

## Build Error Ownership Policy

Codex не должен:
- автоматически исправлять unrelated build errors;
- изменять build configuration;
- менять solution/project structure;

без явного подтверждения USER.

---

## Task-Scoped Verification

После изменения:
- одного метода;
- одной подсистемы;
- одного класса;

предпочитать:
- локальную проверку;
- минимальный rebuild;
- targeted verification.

Избегать full-project rebuild без необходимости.

---

## Build Determinism

Build workflow должен:
- оставаться воспроизводимым;
- минимально зависеть от состояния IDE;
- не требовать ручных действий между задачами.

---

## Future Evolution

В будущем допускается:
- CI integration;
- automated build verification;
- replayable verification pipelines.

Но:
- local deterministic build remains primary workflow.
