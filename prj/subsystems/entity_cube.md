# Subsystem: Cube

## Назначение

Cube:
- базовая игровая сущность;
- единичный элемент фигуры;
- единичный элемент layers matrix.

Cube должен оставаться:
- lightweight;
- deterministic;
- platform-independent.

---

## Architectural Role

Cube:
- atomic gameplay entity;
- shared primitive between Figure and Layers;
- lowest-level gameplay data unit.

---

## Boundaries

Cube subsystem включает:
- cube state;
- cube coordinates;
- cube value/state semantics.

Cube subsystem НЕ включает:
- figure orchestration;
- round processing;
- rendering pipeline;
- platform adapters.

---

## Основная ответственность

Cube отвечает за:
- numeric value;
- coordinates;
- visibility/state;
- color data;
- minimal cube state.

Cube НЕ отвечает за:
- gameplay rules;
- movement rules;
- rendering;
- ownership orchestration;
- round logic.

---

## Pointer Safety

Cube pointers:
- могут использоваться как non-owning references;
- не должны переживать owner destruction;
- не должны implicitly transfer ownership.

Dangling pointers:
- forbidden.

---

## Determinism Requirements

Cube behavior должен быть deterministic:
- initialization;
- copy behavior;
- coordinate updates;
- state transitions.

---

## Error Handling

Используются:
- assertions;
- validation checks;
- deterministic initialization.

try/catch:
- not used.

---

## Known Risks

- dangling pointers in Layers;
- incorrect ownership transfer;
- partial state copy;
- uninitialized cube state.

---

## Coordinate System

Используется система координат стакана.

Нижний левый кубик:
(0,0)

Примеры соседей:
- вверх: (0,1)
- вправо: (1,0)
- диагональ: (1,1)

---

## Cube State

Типичный state cube:
- numeric value;
- x/y coordinates;
- visibility/status;
- color data;
- optional gameplay flags.

---

## Ownership Model

На текущем этапе:

Figure:
- владеет Cube objects.

Рекомендуемая модель:
- `std::vector<std::unique_ptr<Cube>>`

Layers:
- хранит non-owning pointers.

Рекомендуемая модель:
- `std::vector<Cube*>`

---

## Lifecycle Rules

Lifecycle:
1. Cube создается внутри Figure.
2. Figure управляет lifetime cube.
3. При фиксации:
   - pointers передаются в Layers.
4. Figure destruction:
   - ownership transfer должен быть корректным.
5. dangling pointers недопустимы.

---

## Invariants

Cube invariants:
- coordinates должны быть валидны;
- cube state должен быть initialized;
- visibility/status должен быть deterministic;
- ownership должен быть однозначным.

---

## Copy Rules

Копирование Cube:
- должно быть explicit и predictable;
- должно корректно копировать state;
- не должно терять gameplay fields.

Особое внимание:
- status fields;
- coordinates;
- color/value state.

---

## Platform Independence

Cube:
- не должен зависеть от WinAPI;
- не должен зависеть от rendering layer;
- не должен зависеть от console specifics.

---

## Testing Focus

Основные проверки:
- initialization;
- coordinate correctness;
- copy correctness;
- ownership safety;
- lifecycle correctness.

---

## Related Tasks

Ключевые задачи:
- initialization fixes;
- copy operator tests;
- ownership stabilization.

---

## Related Source Files

Основные файлы:
- cube.h
- cube.cpp

---

## Related Subsystems

Связанные подсистемы:
- entity_figure.md
- layers.md
- round_rules.md

---

## Mutation Rules

Изменения Cube subsystem:
- должны быть минимальными;
- должны сохранять deterministic state;
- не должны silently менять ownership semantics.

---

## Future Evolution

Возможное развитие:
- additional gameplay metadata;
- optimization of storage;
- richer gameplay flags.

Не добавлять:
- rendering logic;
- platform logic;
- speculative abstractions без use-case.
