# Файловая структура

C:\Users\Alex\Documents\prog\matris\base_test

├── interface\   (файлы интерфейсов)
│   ├── i_audio.h	(класс iAudio - звуки)
│   ├── i_files.h	(класс iFiles - файловый ввод-вывод)
│   ├── i_input.h	(класс iInput - пользовательский ввод)
│   └── i_render.h	(класс iRender - экранный вывод)

├── win_cons\    (реализации для консоли Windows)
│   ├── c_render_old.h	(старая, рабочая реализация)
│   └── c_render.h		(реализация iRender для консоли Windows)

├── base_test.cpp	(функция main)
├── cube.h			(класс Cube)
├── figure.h		(класс Figure)
├── game.h			(класс Game)
├── layers.h		(класс Layers)	
├── point.h			(класс Point)
├── rgbcolor.h		(класс RGBcolor)	
├── round.h			(класс Round)
├── types.h			(виды фигур и т.п.)

├── base_test.vcxproj			(файл проекта MS Visual Studio)
├── base_test.vcxproj.filters	(файл проекта MS Visual Studio)
├── base_test.vcxproj.user		(файл проекта MS Visual Studio)

├── rules\		(методы-правила)
│   ├── common_rules.h	(общие методы-правила)
│   ├── cube_rules.h	(методы-правила для кубиков)
│   ├── figure_rules.h	(методы-правила для фигур)
│   ├── game_rules.h	(методы-правила для игры)
│   ├── layer_rules.h	(методы-правила для слоев)
│   ├── round_rules.h	(методы-правила для раунда)
│   └── rules.h			(основной хедер для всех rules)

├── windsurf.md		(настройки проекта для Windsurf)
├── .continue		(настройки модуля Continue для VS Code)

├── base_test\          (результаты сборки) - не имеет прямого отношения к проекту
├── x64\                (результаты сборки) - не имеет прямого отношения к проекту
├── test\               (unit-тесты)
│   └── ...

├── codex\              (документация для Codex)
│   ├── global_rules.md		(глобальный контекст проекта)
│   ├── !todo_шаблон.h		(файл маркеров пользовательской разметки комментариев в коде)
│   ├── file_structure.md	(этот файл)
│   ├── subsystems.md		(список подсистем)
│   ├── project_map.md		(список файлов кода)
│   ├── file_tree.cmd		(CMD файл для создания структуры файлов проекта)

│   └── tasks\						(задачи)
│       ├── task_file_template.md	(шаблон файла задачи)
│       ├── backlog.md				(файл списка задач)
│       ├── TASK-XXXX.md			(файлы невыполненных задач)
│       ├── ...
│       └── archive\       		(выполненные задачи)
│           ├── TASK-XXXX.md	(файлы выполненных задач)
│           └── ...

└── doc\   (пользовательская документация, read-only!)
    ├── !todo_шаблон.h
    ├── ai_todo.md
    ├── class.md
    ├── file_tree.cmd.lnk
    ├── game_loop.md
    ├── info.md
    ├── rules.md
    ├── todo.h
    ├── windsurf.md
    └── graph\	( файлы по графическому интерфейсу)
		└── ...
		