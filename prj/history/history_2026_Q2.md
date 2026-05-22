# History 2026 Q2

## РќР°Р·РЅР°С‡РµРЅРёРµ

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
Р’С‹РїРѕР»РЅРµРЅ РїРѕР»РЅС‹Р№ СЃС‚Р°С‚РёС‡РµСЃРєРёР№ Р°РЅР°Р»РёР· РєР»Р°СЃСЃРѕРІ Рё РјРµС‚РѕРґРѕРІ cons_test.

CHANGES:
- class_method_analysis_report.md
- Codex_todo.txt

VERIFICATION:
- static review
- source analysis

RISKS:
- РІС‹СЏРІР»РµРЅС‹ РєСЂРёС‚РёС‡РµСЃРєРёРµ Р±Р»РѕРєРµСЂС‹ A-001 ... A-012

NEXT:
- stabilization critical P0 tasks

---

[2026-05-02]

TASK: TASK-0009
STATUS: DONE
SUBSYSTEM: layers

SUMMARY:
Р”РѕР±Р°РІР»РµРЅ nullptr guard РІ Layers::eachCube.

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
РџСЂРёРЅСЏС‚ bounded-context AI-native workflow.

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
РЎРѕР·РґР°РЅ production workflow v1.

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
РЎС‚Р°Р±РёР»РёР·РёСЂРѕРІР°РЅ default state РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂР° Cube: СѓР±СЂР°РЅР° РЅРµРёРЅРёС†РёР°Р»РёР·РёСЂРѕРІР°РЅРЅР°СЏ РІРµС‚РєР° СЃРѕСЃС‚РѕСЏРЅРёСЏ.

CHANGES:
- cons_test/cube.h

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- Cube initialization verification: default ctor РґРµР»РµРіРёСЂРѕРІР°РЅ РІ РїРѕР»РЅС‹Р№ РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ СЃ СЏРІРЅРѕР№ РёРЅРёС†РёР°Р»РёР·Р°С†РёРµР№ РІСЃРµС… РїРѕР»РµР№
- deterministic default state verification: Р·РЅР°С‡РµРЅРёСЏ РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ С„РёРєСЃРёСЂРѕРІР°РЅС‹ Рё РЅРµ Р·Р°РІРёСЃСЏС‚ РѕС‚ РІРЅРµС€РЅРµРіРѕ РєРѕРЅС‚РµРєСЃС‚Р°

RISKS:
- smoke runtime test РЅРµ РІС‹РїРѕР»РЅСЏР»СЃСЏ (entry point РѕР¶РёРґР°РµС‚ РёРЅС‚РµСЂР°РєС‚РёРІРЅС‹Р№ _getch)
- unrelated warning remained: rules.cpp C4244

NEXT:
- TASK-0010

---

[2026-05-14]
CORRECTION FOR: TASK-0011

REASON:
РўРµСЃС‚ СЃРёРЅС…СЂРѕРЅРёР·Р°С†РёРё Figure::num РїРµСЂРµРЅРµСЃРµРЅ РёР· `cons_test.cpp` РІ РѕС‚РґРµР»СЊРЅС‹Р№ GoogleTest РїСЂРѕРµРєС‚.

DETAILS:
TASK-0011 history Р·Р°РїРёСЃСЊ СЃСЃС‹Р»Р°РµС‚СЃСЏ РЅР° РІСЂРµРјРµРЅРЅСѓСЋ СЂРµР°Р»РёР·Р°С†РёСЋ РІ production entry point.
РђРєС‚СѓР°Р»СЊРЅРѕРµ СЃРѕСЃС‚РѕСЏРЅРёРµ: РїСЂРѕРІРµСЂРєР° РІС‹РїРѕР»РЅСЏРµС‚СЃСЏ РІ `matris_tests` (test/test_figure_num_sync.cpp).

NO HISTORY REWRITE.
APPEND-ONLY POLICY.

---

[2026-05-14]

TASK: TASK-0007
STATUS: DONE
SUBSYSTEM: testing

SUMMARY:
Р’РЅРµРґСЂРµРЅР° СЃРёСЃС‚РµРјР° unit-С‚РµСЃС‚РѕРІ РЅР° GoogleTest С‡РµСЂРµР· vcpkg Рё СЃРѕР·РґР°РЅ РѕС‚РґРµР»СЊРЅС‹Р№ РїСЂРѕРµРєС‚ `matris_tests` РІ `matris.sln`.

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
- РІ build log РµСЃС‚СЊ РїСЂРµРґСѓРїСЂРµР¶РґРµРЅРёРµ РїСЂРѕ `pwsh.exe` fallback РІ vcpkg applocal step (СЃР±РѕСЂРєСѓ РЅРµ Р±Р»РѕРєРёСЂСѓРµС‚)
- legacy warning C4244 РІ rules.cpp РѕСЃС‚Р°РµС‚СЃСЏ

NEXT:
- TASK-0010

---

[2026-05-14]

TASK: TASK-0011
STATUS: DONE
SUBSYSTEM: entity_figure

SUMMARY:
РЎС‚Р°Р±РёР»РёР·РёСЂРѕРІР°РЅ lifecycle РїРѕР»СЏ Figure::num Рё РґРѕР±Р°РІР»РµРЅ С‚РµСЃС‚ РЅР° СЃРѕРѕС‚РІРµС‚СЃС‚РІРёРµ С„Р°РєС‚РёС‡РµСЃРєРѕРјСѓ РєРѕР»РёС‡РµСЃС‚РІСѓ РєСѓР±РёРєРѕРІ.

CHANGES:
- cons_test/figure.h
- cons_test/cons_test.cpp

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- MATRIS_TEST_FIGURE_NUM_SYNC=1 + Р·Р°РїСѓСЃРє x64/Debug/cons_test.exe: TEST Figure::num sync: OK
- code review: num РёРЅРёС†РёР°Р»РёР·РёСЂСѓРµС‚СЃСЏ Рё СЃРёРЅС…СЂРѕРЅРёР·РёСЂСѓРµС‚СЃСЏ С‡РµСЂРµР· cubes.size()

RISKS:
- С‚РµСЃС‚ РёРЅС‚РµРіСЂРёСЂРѕРІР°РЅ РІ entry point Рё Р·Р°РїСѓСЃРєР°РµС‚СЃСЏ С‡РµСЂРµР· env flag (РЅРµ РѕС‚РґРµР»СЊРЅС‹Р№ unit-test РїСЂРѕРµРєС‚)

NEXT:
- TASK-0010

---

[2026-05-13]

TASK: TASK-0014
STATUS: DONE
SUBSYSTEM: layers

SUMMARY:
Р”РѕР±Р°РІР»РµРЅС‹ nullptr guards РІ pointer-based РјРµС‚РѕРґС‹ Layers РґР»СЏ РёСЃРєР»СЋС‡РµРЅРёСЏ unsafe dereference.

CHANGES:
- cons_test/layers.h

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- targeted nullptr-path review РґР»СЏ РјРµС‚РѕРґРѕРІ writeCube/delCube/isCube/isNear/isBelow/isNearXY/isNearDiag/isNears
- regression-check: РїРѕРІРµРґРµРЅРёРµ РјРµС‚РѕРґРѕРІ РґР»СЏ РІР°Р»РёРґРЅС‹С… СѓРєР°Р·Р°С‚РµР»РµР№ СЃРѕС…СЂР°РЅРµРЅРѕ

RISKS:
- runtime smoke test РЅРµ РІС‹РїРѕР»РЅСЏР»СЃСЏ
- unrelated warning remained: rules.cpp C4244

NEXT:
- TASK-0010

---

[2026-05-16]

TASK: TASK-0018
STATUS: DONE
SUBSYSTEM: round_rules

SUMMARY:
Стабилизированы include-зависимости `rules.h`: заголовок сделан самодостаточным через явное подключение `types.h`.

CHANGES:
- cons_test/rules.h
- prj/tasks/active_tasks.md
- prj/tasks/backlog.md

VERIFICATION:
- code review: `rules.h` использует типы `Point` и `RGBcolor`, объявленные в `types.h`
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success

RISKS:
- unrelated warning remained: rules.cpp C4244

NEXT:
- TASK-0010

---

[2026-05-17]

TASK: TASK-0008
STATUS: DONE
SUBSYSTEM: testing, workflow

SUMMARY:
Стандартизирован manual QA workflow: добавлен обязательный блок ручной проверки для USER и task-specific акценты проверки в completion-отчётах.

CHANGES:
- prj/workflow/task_execution.md
- prj/workflow/reporting.md
- prj/workflow/testing.md
- prj/workflow/task_file_template.md
- prj/workflow/task_execution_checklist.md
- prj/tasks/backlog.md

VERIFICATION:
- policy review: обязательные блоки `Manual Check For USER` и `Manual Check Accents` закреплены в workflow
- consistency check: требования синхронизированы между execution/testing/reporting/template/checklist

RISKS:
- manual QA quality зависит от полноты task-specific accents в каждом отчёте

NEXT:
- TASK-0010

---

[2026-05-17]

TASK: TASK-0010
STATUS: DONE
SUBSYSTEM: entity_figure

SUMMARY:
Реализована и стабилизирована логика `Figure::move` и `Figure::rotate/chkRotate` с валидацией границ стакана и коллизий со слоями.

CHANGES:
- cons_test/figure.h
- test/test_figure_move_rotate.cpp
- test/test.vcxproj
- prj/tasks/TASK-0010-figure-rotation.md
- prj/tasks/active_tasks.md
- prj/tasks/backlog.md

VERIFICATION:
- MSBuild matris.sln /p:Configuration=Debug /p:Platform=x64: success
- x64\Debug\test.exe --gtest_color=no: 6 tests passed
- added tests: move bounds invariant, move collision block, rotate collision block

RISKS:
- rotate/move покрыты только на текущей модели `Figure` (value-based `std::vector<Cube>`)
- upcoming ownership migration task (TASK-0019) потребует адаптации тестов и методов

NEXT:
- TASK-0015
