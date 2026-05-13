# Subsystem: Layers

## Назначение

Layers:
- матрица стакана;
- storage fixed cubes;
- collision support subsystem;
- authoritative occupancy map.

Layers содержит:
- только зафиксированные кубики;
- без active falling Figure.

---

## Architectural Role

Layers:
- authoritative gameplay field state;
- shared collision validation subsystem;
- persistent fixed-cube storage layer.

---

## Boundaries

Layers subsystem включает:
- occupancy storage;
- bounds validation;
- collision lookup;
- spatial access.

Layers subsystem НЕ включает:
- gameplay timing;
- active movement orchestration;
- gravity execution;
- rendering pipeline;
- platform adapters.

---

## Determinism Requirements

Layers behavior должен быть deterministic:
- occupancy lookup;
- collision validation;
- coordinate access;
- field synchronization;
- pointer validation behavior.

---

## Основная ответственность

Layers отвечает за:
- хранение fixed cubes;
- occupancy lookup;
- collision support;
- bounds validation;
- access to field state.

Layers НЕ отвечает за:
- active figure movement;
- rendering;
- round orchestration;
- gameplay timing.

---

## Storage Model

Рекомендуемая модель:
`std::vector<Cube*>`

Layers:
- non-owning storage;
- pointer-based access;
- deterministic lookup structure.

---

## Ownership Rules

Layers:
- НЕ владеет Cube objects.

Ownership:
- originates from Figure;
- transfer должен быть explicit;
- lifecycle должен быть deterministic.

Недопустимо:
- dangling pointers;
- ambiguous ownership;
- implicit deletion.

---

## Coordinate System

Используются координаты стакана.

Нижний левый угол:
(0,0)

Layers:
- authoritative field coordinate system;
- single occupancy space.

---

## Collision Responsibility

Figure:
- инициирует collision checks.

Layers:
- authoritative validator.

Layers проверяет:
- occupied cells;
- bounds;
- valid placement.

---

## Bounds Rules

Layers отвечает за:
- valid coordinate range;
- стакан boundaries;
- occupancy consistency.

Out-of-bounds:
- invalid state;
- invalid placement;
- invalid movement target.

---

## Access Safety

Все pointer accesses:
- должны проверяться;
- должны быть nullptr-safe.

Недопустимо:
- unsafe dereference;
- silent invalid access.

---

## Invariants

Layers invariants:
- coordinates valid;
- occupancy deterministic;
- pointers valid;
- nullptr handling explicit;
- field state synchronized.

---

## Field Update Rules

Layers обновляется:
- после figure fixation;
- после round rules execution;
- после gravity/destruction cycles.

Field state должен оставаться:
- deterministic;
- stable;
- synchronized.

---

## Gravity Support

Layers:
- предоставляет data для gravity rules;
- предоставляет occupancy analysis;
- предоставляет spatial lookup.

Gravity orchestration:
- outside Layers responsibility.

---

## Destruction Support

Layers:
- предоставляет lookup/access;
- предоставляет neighbor queries.

Destruction rules:
- outside Layers responsibility.

---

## Platform Independence

Layers:
- platform-independent;
- rendering-independent;
- WinAPI-independent.

---

## Testing Focus

Основные проверки:
- collision correctness;
- bounds correctness;
- nullptr safety;
- occupancy correctness;
- coordinate lookup;
- storage consistency.

---

## Related Tasks

Ключевые задачи:
- nullptr guards;
- collision stabilization;
- occupancy validation;
- ownership stabilization.

---

## Related Source Files

Основные файлы:
- layers.h
- layers.cpp

---

## Related Subsystems

Связанные подсистемы:
- entity_cube.md
- entity_figure.md
- round_rules.md

---

## Mutation Rules

Изменения Layers subsystem:
- должны быть minimal;
- должны сохранять deterministic occupancy;
- не должны silently менять ownership model.

---

## Future Evolution

Допустимое развитие:
- optimized lookup;
- spatial acceleration;
- richer occupancy queries.

Не добавлять:
- rendering logic;
- gameplay orchestration;
- speculative storage systems без необходимости.

---

## Known Risks

- dangling pointers;
- stale occupancy state;
- invalid coordinate access;
- nullptr dereference risk;
- collision desynchronization.
