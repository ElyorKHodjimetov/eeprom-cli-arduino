# EEPROM CLI for Arduino Uno

**Тестовое задание:** реализовать CLI-интерфейс доступа к памяти EEPROM на Arduino Uno.

**Платформа:** Arduino Uno  
**IDE:** Arduino IDE  
**Файл проекта:** `eeprom_cli.ino`

---

## Требования к командам

| №  | Описание                | Ключ/Пример                 |
|----|-------------------------|-----------------------------|
| 1  | Префикс команды         | `eeprom`                    |
| 2  | Запись ячейки           | `-w -a <addr> -v <value>`   |
| 3  | Чтение ячейки           | `-r -a <addr>`              |
| 4  | Стирание ячейки         | `-e -a <addr>`              |
| 5  | Дамп всех ячеек         | `-d`                        |
| 6  | Ключ адреса (DEC)       | `-a <address>`              |
| 7  | Ключ значения (DEC)     | `-v <value>`                |

**Примеры команд:**
```text
# Записать 55 в ячейку 10
eeprom -w -a 10 -v 55
# Прочитать ячейку 10
eeprom -r -a 10
# Стереть ячейку 10
eeprom -e -a 10
# Вывести дамп всех ячеек
eeprom -d
```

---

## Установка и запуск

### Локально (Arduino IDE)

1. Клонировать репозиторий:

   ```bash
   git clone https://github.com/your_username/eeprom-cli-arduino.git
   cd eeprom-cli-arduino
   ```
2. Открыть `eeprom_cli.ino` в Arduino IDE.
3. В меню **Tools → Board** выбрать **Arduino Uno**.
4. В меню **Tools → Port** выбрать ваш COM-порт.
5. Нажать **Upload** (или **Ctrl+U**).
6. Открыть **Tools → Serial Monitor**, установить **115200 baud**.
7. Вводить команды (см. раздел «Требования к командам»).

### Онлайн-демо (Wokwi)

Проверка без реальной платы:  
[https://wokwi.com/projects/430829469978551297](https://wokwi.com/projects/430829469978551297)

---

## Тестирование

В **Serial Monitor** (115200 baud) проверьте следующие сценарии:

### Базовые операции

```text
# Запись
> eeprom -w -a 0 -v 42
OK

# Чтение
> eeprom -r -a 0
42

# Стирание
> eeprom -e -a 0
OK

# Проверка после стирания
> eeprom -r -a 0
255

# Дамп памяти
> eeprom -d
0000 : FF FF FF FF FF FF FF FF
0008 : FF FF FF FF FF FF FF FF
...
```

### Ошибочные сценарии

```text
# Неправильный префикс
> eprm -r -a 0
ERROR: Unknown prefix

# Без операции
> eeprom -a 5 -v 10
ERROR: No valid operation specified

# Адрес вне диапазона
> eeprom -r -a 2000
ERROR: Address out of range

# Неизвестный ключ
> eeprom -x -a 0
ERROR: Unknown argument -x
```

---

## Структура репозитория

```text
eeprom-cli-arduino/
├── .gitignore       # Исключает артефакты сборки Arduino
├── LICENSE          # Лицензия MIT
├── README.md        # Документация и инструкции
└── eeprom_cli.ino   # Исходный код CLI для EEPROM
```

---

## Лицензия

Этот проект распространяется под **MIT License**. Подробности в файле [LICENSE](LICENSE).
