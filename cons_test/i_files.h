#pragma once
// @file: i_files.h

class IFiles
{
public:
	virtual ~IFiles() = default;

	// Загрузка музыки
	virtual void LoadMusic() = 0;

	// Загрузка звука
	virtual void LoadSound() = 0;

	// Заргузка настроек, счета, текущего состояния
	virtual void LoadSetup() = 0;

	// Запись настроек, счета, текущего состояния
	virtual void SaveSetup() = 0;

	// Нижний уровень

	// Открыть файл (создать, если не существует)
	virtual void OpenFile() = 0;

	// Закрыть файл - возможно, не нужно - автоматическое закрытие в деструкторе Файла
	virtual void CloseFile() = 0;

	// Считать данные из файла (какие именно? - настройки, счет, состояние)
	virtual void ReadData() = 0;

	// Записать в файл (что именно? - настройки, счет, состояние)
	virtual void WriteData() = 0;

	// Дописать в конец файла
	virtual void AddData() = 0;
};

// Файл - объект ?