# Subsystem: Platform Console

## Назначение

Platform Console:
- Windows console platform layer;
- console rendering;
- console input integration;
- platform adapter subsystem.

Текущий этап:
WIN_CONSOLE_V1

---

## Основная ответственность

Platform Console отвечает за:
- console rendering;
- keyboard input integration;
- console-specific behavior;
- WinAPI console interaction.

Platform Console НЕ отвечает за:
- gameplay rules;
- gameplay ownership;
- round logic;
- gameplay orchestration.

---

## Architecture Role

Platform Console:
- adapter layer;
- bridge между gameplay core и Windows console.

Gameplay core:
- platform-independent.

Platform Console:
- platform-specific.

---

## Boundaries

Platform Console subsystem включает:
- WinAPI integration;
- console rendering;
- console input handling;
- platform adapters;
- platform-specific execution behavior.

Platform Console subsystem НЕ включает:
- gameplay rules;
- gameplay ownership;
- deterministic gameplay orchestration;
- round logic;
- gameplay storage.

---

## Determinism Requirements

Platform layer:
- не должен нарушать gameplay determinism;
- не должен изменять gameplay ordering;
- не должен вводить hidden timing drift.

Gameplay determinism:
- authoritative outside platform layer.

---

## Ownership Notes

Gameplay core:
- не должен владеть platform internals.

Platform interfaces:
- должны иметь explicit ownership semantics;
- должны избегать ambiguous lifetime management.

Особое внимание:
- IRender lifecycle;
- adapter destruction order.

---

## Render Layer

Основной render interface:
- IRender

Текущая реализация:
- CRender

Render subsystem:
- отображает gameplay state;
- не изменяет gameplay state.

---

## Input Layer

Будущий input interface:
- IInput

Текущая цель:
- keyboard-only input;
- Windows console keyboard integration.

Input subsystem:
- поставляет normalized input state;
- не содержит gameplay logic.

---

## Console Constraints

Текущие ограничения:
- console only;
- pseudographics;
- keyboard only;
- no graphical window;
- no audio requirements.

---

## Rendering Requirements

Render должен:
- избегать visual artifacts;
- избегать frame garbage accumulation;
- поддерживать stable redraw behavior.

Целевой режим:
- visually stable console updates.

---

## Platform Isolation

WinAPI-specific code:
- должен оставаться внутри platform layer;
- не должен проникать в gameplay core.

Gameplay subsystems:
- не должны зависеть от WinAPI.

---

## Timing Interaction

Platform layer:
- не должен ломать deterministic gameplay timing;
- не должен вводить hidden asynchronous behavior.

---

## Error Handling

Platform errors:
- explicit;
- logged;
- isolated.

Недопустимо:
- silent platform failures;
- hidden console state corruption.

---

## Logging Requirements

Минимальные log levels:
- Error
- Warn
- Info

Избегать:
- frame-by-frame spam;
- excessive runtime noise.

---

## Testing Focus

Основные проверки:
- console startup;
- redraw correctness;
- keyboard handling;
- stable frame behavior;
- console execution outside VS.

---

## Related Tasks

Ключевые задачи:
- console stabilization;
- keyboard integration;
- redraw stabilization;
- platform isolation.

---

## Related Source Files

Основные файлы:
- c_render.h
- c_render.cpp
- console platform files

---

## Related Interfaces

Основные interfaces:
- IRender
- IInput

---

## Related Subsystems

Связанные подсистемы:
- game_loop.md
- entity_figure.md
- layers.md

---

## Mutation Rules

Изменения platform_console subsystem:
- должны быть isolated;
- не должны проникать в gameplay core;
- не должны silently менять gameplay semantics.

---

## Future Evolution

Следующие этапы:
1. Windows windowed graphics
2. Linux
3. Android

Platform layer должен оставаться:
- replaceable;
- isolated;
- extensible.

---

## Anti-Coupling Policy

Не допускать:
- gameplay/render coupling;
- WinAPI leakage into core;
- platform-specific gameplay behavior;
- direct gameplay dependency на console implementation.

---

## Cross-Platform Goal

Gameplay core должен оставаться:
- platform-agnostic;
- reusable;
- portable across future platforms.

Platform-specific behavior:
- isolated inside adapters.

---

## Known Risks

- WinAPI leakage into gameplay core;
- unstable console redraw behavior;
- input latency instability;
- ambiguous IRender ownership;
- platform-specific timing drift.

