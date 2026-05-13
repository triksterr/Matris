# TASK-0007 — GoogleTest Coverage

## Status

DONE

---

## Goal

Внедрить отдельную систему unit-тестов на GoogleTest через vcpkg.

---

## Result

- создан отдельный проект `matris_tests` в составе `matris.sln`;
- тестовые исходники размещаются в `matris/test/`;
- тест `Figure::num` перенесен из `cons_test.cpp` в `test/test_figure_num_sync.cpp`;
- документация тестовой системы обновлена.
