# Subsystem: Figure

## Назначение

Figure:
- игровая фигура из кубиков;
- movable gameplay entity;
- временный owner активных Cube objects.

Figure:
- управляет movement;
- управляет rotation;
- управляет active gameplay state фигуры.

---

## Architectural Role

Figure:
- active gameplay entity;
- primary movable gameplay object;
- bridge between gameplay input and Layers collision validation.

---

## Boundaries

Figure subsystem включает:
- movement logic;
- rotation logic;
- cube ownership;
- figure-local geometry state.

Figure subsystem НЕ включает:
- round processing;
- gravity resolution;
- destruction cycles;
- rendering pipeline;
- platform adapters.

---

## Determinism Requirements

Figure behavior должен быть deterministic:
- movement;
- rotation;
- collision requests;
- ownership transfer;
- cube synchronization.

---

## Pointer Safety

Figure:
- является temporary cube owner;
- не должен оставлять dangling references;
- должен explicitly finalize ownership transfer.

Non-owning references:
- должны использоваться только временно.

---

## Основная ответственность

Figure отвечает за:
- ownership cube objects;
- movement;
- rotation;
- collision initiation;
- figure-local state.

Figure НЕ отвечает за:
- rendering;
- round rules;
- layers gravity;
- destruction rules;
- platform logic.

---

## Ownership Model

Рекомендуемая модель:

`std::vector<std::unique_ptr<Cube>>`

Figure:
- владеет active cubes;
- отвечает за cube lifecycle;
- отвечает за destruction safety.

---

## Layers Interaction

Layers:
- хранит non-owning Cube pointers.

Figure:
- инициирует movement checks;
- инициирует rotation checks.

Layers:
- проверяет occupancy;
- проверяет collisions;
- проверяет bounds.

---

## Coordinate Model

Figure хранит:
- координаты центра;
- матрицу смещений;
- active cubes.

Cube coordinates:
- в координатах стакана.

Offset matrix:
- относительно центра Figure.

---

## Rotation Model

Rotation:
- вокруг central cube;
- использует offset matrix;
- выполняется deterministic.

Если rotation invalid:
- rotation cancelled;
- previous state preserved.

---

## Movement Model

Figure инициирует:
- move left;
- move right;
- move down;
- rotation attempt.

Collision/bounds:
- проверяются через Layers
- проверяются через координаты и размеры стакана

---

## Figure Geometry

На текущем этапе:
- fixed predefined figures;
- geometry задается matrices/offsets.

Future evolution:
- procedural figures;
- generated geometry;
- rule-driven figure generation.

---

## Lifecycle

Lifecycle:
1. Figure created.
2. Cubes initialized.
3. Figure active in game field.
4. Figure moves/rotates.
5. Figure fixed into Layers.
6. Ownership transfer finalized.
7. Figure destroyed.

---

## Ownership Transfer

При фиксации:
- Figure relinquishes ownership;
- Layers получает stable cube references;
- dangling pointers недопустимы.

Ownership transfer должен быть:
- explicit;
- deterministic;
- reviewable.

---

## Invariants

Figure invariants:
- center coordinates valid;
- cubes synchronized;
- offset matrix synchronized;
- cube count deterministic;
- ownership unambiguous.

---

## Collision Policy

Figure:
- инициирует collision checks.

Layers:
- authoritative collision validator.

Figure НЕ должна:
- напрямую изменять Layers internals.

---

## Platform Independence

Figure:
- platform-independent;
- rendering-independent;
- WinAPI-independent.

---

## Testing Focus

Основные проверки:
- rotation validity;
- rotation cancellation;
- movement collisions;
- boundary checks;
- ownership safety;
- lifecycle correctness.

---

## Related Tasks

Ключевые задачи:
- rotation stabilization;
- collision stabilization;
- ownership migration;
- move validation.

---

## Related Source Files

Основные файлы:
- figure.h
- figure.cpp

---

## Related Subsystems

Связанные подсистемы:
- entity_cube.md
- layers.md
- round_rules.md
- game_loop.md

---

## Mutation Rules

Изменения Figure subsystem:
- должны быть bounded;
- должны сохранять deterministic movement;
- не должны silently менять ownership semantics;
- не должны ломать rotation invariants.

---

## Future Evolution

Допустимое развитие:
- richer figure generation;
- configurable geometry;
- advanced movement rules.

Не добавлять:
- rendering logic;
- platform-specific logic;
- speculative generalized systems без use-case.

---

## Known Risks

- rotation/collision coupling;
- cube synchronization drift;
- invalid ownership transfer;
- dangling pointers after fixation;
- inconsistent offset matrix updates.
