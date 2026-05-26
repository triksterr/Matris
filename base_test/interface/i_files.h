#pragma once
// @file: i_files.h

class iFiles
{
public:
	virtual ~iFiles() = default;

	// Загрузка музыки
	virtual void loadMusic() = 0;

	// Загрузка звука
	virtual void loadSound() = 0;

	// Заргузка настроек, счета, текущего состояния
	virtual void loadSetup() = 0;

	// Запись настроек, счета, текущего состояния
	virtual void saveSetup() = 0;

	// Нижний уровень

	// Открыть файл (создать, если не существует)
	virtual void openFile() = 0;

	// Закрыть файл - возможно, не нужно - автоматическое закрытие в деструкторе Файла
	virtual void closeFile() = 0;

	// Считать данные из файла (какие именно? - настройки, счет, состояние)
	virtual void readData() = 0;

	// Записать в файл (что именно? - настройки, счет, состояние)
	virtual void writeData() = 0;

	// Дописать в конец файла
	virtual void addData() = 0;
};

// Файл - объект ?