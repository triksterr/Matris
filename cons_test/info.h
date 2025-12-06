#pragma once
// @file: info.h
// 
#include <string>
#include <vector>

//  Информация об игре - о её текущем состоянии
class Info final
{
public:
	// Удаляем копирование и присваивание
	Info(const Info &) = delete;
	Info &operator=(const Info &) = delete;

	// Получение экземпляра синглтона
	static Info &getInstance()
	{
		static Info instance;
		return instance;
	}

	// геттеры
	int getLevel() const { return level; }
	int getLevelCount() const { return levelCount; }
	int getTotalCount() const { return totalCount; }
	int getLevelLines() const { return levelLines; }
	int getTotalLines() const { return totalLines; }
	int getLevelFigs() const { return levelFigs; }
	int getTotalFigs() const { return totalFigs; }
	//int getTotalTime() const { return totalTime; }
	//int getLevelTime() const { return levelTime; }
	//int getNextFigs() const { return nextFigs; }

	// сеттеры
	void nextLevel() { level++; }
	void addLevelCount() { levelCount++; totalCount++; }

	void setLevel(int level) { this->level = level; }
	void setLevelCount(int levelCount) { this->levelCount = levelCount; }
	void setTotalCount(int totalCount) { this->totalCount = totalCount; }
	void setLevelLines(int levelLines) { this->levelLines = levelLines; }
	void setTotalLines(int totalLines) { this->totalLines = totalLines; }
	void setLevelFigs(int levelFigs) { this->levelFigs = levelFigs; }
	void setTotalFigs(int totalFigs) { this->totalFigs = totalFigs; }
	void setTotalTime(int totalTime) { this->totalTime = totalTime; }
	void setLevelTime(int levelTime) { this->levelTime = levelTime; }
	//void setNextFigs(int nextFigs) { this->nextFigs = nextFigs; }

private:
	// Приватный конструктор и деструктор
	Info() = default;
	~Info() = default;

	// Текущий ровень
	int level = 1;
	// Счет раунда
	int levelCount = 0;	
	// Счет всей игры
	int totalCount = 0;
	// Количество очищенных линий в этом раунде
	int levelLines = 0;
	// Количество очищенных линий во всей игре
	int totalLines = 0;
	// Количество упавших фигур в этом раунде
	int levelFigs = 0;
	// Количество упавших фигур во всей игре
	int totalFigs = 0;
	// Время всей игры
	int  totalTime = 0; //! Не int !
	// Время уровня(раунда)
	int levelTime = 0; //! Не int !
	// Следующая фигура
	int next = 0; //! Не int !
	// Количество успешных операций
	int ops = 0;
	// Количество ошибок
	int errors = 0;

	// Текстовые константы
	std::vector<std::string> txt_ru = {
		"Счет:",
		"Уровень:",
		"Линий:",
		"Фигур:",
		"Время:",
		"Следующая:",
		"Операций:" };

	std::vector<std::string> txt_en = {
		"Count:",
		"Level:",
		"Lines:",
		"Figs:",
		"Time:",
		"Next:",
		"Ops:" };
};
