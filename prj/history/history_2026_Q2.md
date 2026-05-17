# History 2026 Q2

## Назначение

Operational history:
- WIN_CONSOLE_V1
- workflow migration
- subsystem stabilization
- bounded-context transition

Append-only.

---

[2026-05-02]

TASK: TASK-0001
STATUS: DONE
SUBSYSTEM: analysis

SUMMARY:
Выполнен полный статический анализ классов и методов cons_test.

CHANGES:
- class_method_analysis_report.md
- Codex_todo.txt

VERIFICATION:
- static review
- source analysis

RISKS:
- выявлены критические блокеры A-001 ... A-012

NEXT:
- stabilization critical P0 tasks

---

[2026-05-02]

TASK: TASK-0009
STATUS: DONE
SUBSYSTEM: layers

SUMMARY:
Добавлен nullptr guard в Layers::eachCube.

CHANGES:
- cons_test/layers.h

VERIFICATION:
- code review
- Debug|x64 build attempt

RISKS:
- unrelated known build issue in c_render.h remained

NEXT:
- TASK-0010

---

[2026-05-11]

ADR: ADR-0001

SUMMARY:
Принят bounded-context AI-native workflow.

IMPACT:
- subsystem-first loading
- task-oriented execution
- append-only history
- sequential semi-autonomous workflow
- minimal mutation policy

---

[2026-05-11]

TASK: WORKFLOW-MIGRATION
STATUS: DONE
SUBSYSTEM: workflow

SUMMARY:
Создан production workflow v1.

CHANGES:
- workflow/*
- subsystems/*
- runtime/*
- tasks/*
- history/*
- adr/*
- risks/*

VERIFICATION:
- manual structural review

RISKS:
- requires operational validation during real tasks

NEXT:
- migrate active tasks into task files

---

[2026-05-13]

TASK: TASK-0012
STATUS: DONE
SUBSYSTEM: entity_cube

SUMMARY:
Стабилизирован default state конструктора Cube: убрана неинициализированная ветка состояния.

CHANGES:
- cons_test/cube.h

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- Cube initialization verification: default ctor делегирован в полный конструктор с явной инициализацией всех полей
- deterministic default state verification: значения по умолчанию фиксированы и не зависят от внешнего контекста

RISKS:
- smoke runtime test не выполнялся (entry point ожидает интерактивный _getch)
- unrelated warning remained: rules.cpp C4244

NEXT:
- TASK-0010

---

[2026-05-14]
CORRECTION FOR: TASK-0011

REASON:
Тест синхронизации Figure::num перенесен из `cons_test.cpp` в отдельный GoogleTest проект.

DETAILS:
TASK-0011 history запись ссылается на временную реализацию в production entry point.
Актуальное состояние: проверка выполняется в `matris_tests` (test/test_figure_num_sync.cpp).

NO HISTORY REWRITE.
APPEND-ONLY POLICY.

---

[2026-05-14]

TASK: TASK-0007
STATUS: DONE
SUBSYSTEM: testing

SUMMARY:
Внедрена система unit-тестов на GoogleTest через vcpkg и создан отдельный проект `matris_tests` в `matris.sln`.

CHANGES:
- matris.sln
- test/matris_tests.vcxproj
- test/matris_tests.vcxproj.filters
- test/test_figure_num_sync.cpp
- cons_test/cons_test.cpp
- prj/workflow/testing.md
- prj/workflow/build_commands.md
- prj/workflow/test_system.md
- prj/workflow/file_registry.md
- prj/tasks/backlog.md

VERIFICATION:
- C:\Users\Alex\Documents\prog\vcpkg\vcpkg.exe install gtest:x64-windows: success
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- x64\Debug\matris_tests.exe --gtest_color=no: 1 test passed

RISKS:
- в build log есть предупреждение про `pwsh.exe` fallback в vcpkg applocal step (сборку не блокирует)
- legacy warning C4244 в rules.cpp остается

NEXT:
- TASK-0010

---

[2026-05-14]

TASK: TASK-0011
STATUS: DONE
SUBSYSTEM: entity_figure

SUMMARY:
Стабилизирован lifecycle поля Figure::num и добавлен тест на соответствие фактическому количеству кубиков.

CHANGES:
- cons_test/figure.h
- cons_test/cons_test.cpp

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- MATRIS_TEST_FIGURE_NUM_SYNC=1 + запуск x64/Debug/cons_test.exe: TEST Figure::num sync: OK
- code review: num инициализируется и синхронизируется через cubes.size()

RISKS:
- тест интегрирован в entry point и запускается через env flag (не отдельный unit-test проект)

NEXT:
- TASK-0010

---

[2026-05-13]

TASK: TASK-0014
STATUS: DONE
SUBSYSTEM: layers

SUMMARY:
Добавлены nullptr guards в pointer-based методы Layers для исключения unsafe dereference.

CHANGES:
- cons_test/layers.h

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- targeted nullptr-path review для методов writeCube/delCube/isCube/isNear/isBelow/isNearXY/isNearDiag/isNears
- regression-check: поведение методов для валидных указателей сохранено

RISKS:
- runtime smoke test не выполнялся
- unrelated warning remained: rules.cpp C4244

NEXT:
- TASK-0010

---

[2026-05-16]

TASK: TASK-0018
STATUS: DONE
SUBSYSTEM: round_rules

SUMMARY:
��������������� include-����������� `rules.h`: ��������� ������ ��������������� ����� ����� ����������� `types.h`.

CHANGES:
- cons_test/rules.h
- prj/tasks/active_tasks.md
- prj/tasks/backlog.md

VERIFICATION:
- code review: `rules.h` ���������� ���� `Point` � `RGBcolor`, ����������� � `types.h`
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success

RISKS:
- unrelated warning remained: rules.cpp C4244

NEXT:
- TASK-0010
