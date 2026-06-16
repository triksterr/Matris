
# Этап 2. Реализовать только настройки

Сделать полностью рабочими только:
```cpp
loadSettings()
saveSettings()
```
Сейчас - добавить логику обработки бэкапов

Это позволит проверить всю цепочку:
```text
Application - !!!!!! Теперь - здесь!
- Загрузка при старте.
- Перезапись при изменениях в настройках.
- Запись при выходе.
    ↓
iFiles
    ↓
nlohmann/json
    ↓
readText()/writeText()
    ↓
wFiles
    ↓
Файл settings.json
```
---

# Этап 6. Только после loadSettings() - подключить:

```cpp
loadState()
saveState()

loadResults()
saveResults()



loadImage() - это - вообще потом.
loadMusic()
```

Потому что они будут почти копией механизма настроек.


