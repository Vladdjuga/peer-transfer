# Быстрый старт

## 1. Пересоберите проект
В CLion: `Ctrl+F9` или меню `Build → Rebuild Project`

Или из командной строки:
```powershell
cmake -S . -B cmake-build-debug -G "Ninja"
cmake --build cmake-build-debug --config Debug
```

## 2. Проверьте работу

### Терминал 1 - Запустите получатель:
```powershell
cd cmake-build-debug
.\receiver.exe 8080 received.txt
```

### Терминал 2 - Отправьте файл:
```powershell
cd cmake-build-debug
.\sender.exe 127.0.0.1 8080 ..\test_file.txt
```

## 3. Проверьте результат
Файл `received.txt` должен появиться в папке `cmake-build-debug` с тем же содержимым, что и `test_file.txt`.

## Запуск тестов
```powershell
cd cmake-build-debug
.\run_all_tests.exe
```

Или в CLion выберите конфигурацию `run_all_tests` и запустите.

## Структура проекта

```
cpptesting/
├── CMakeLists.txt           # Конфигурация сборки
├── README.md                # Подробная документация
├── QUICKSTART.md           # Этот файл
├── test_file.txt           # Тестовый файл для передачи
├── include/                # Заголовочные файлы
│   ├── sender.h
│   ├── receiver.h
│   └── utils.h
├── src/                    # Исходные файлы
│   ├── main_sender.cpp     # Точка входа sender
│   ├── main_receiver.cpp   # Точка входа receiver
│   ├── sender.cpp          # Логика отправки
│   ├── receiver.cpp        # Логика приёма
│   └── utils.cpp           # Утилиты (работа с файлами)
└── tests/                  # Тесты
    ├── sender_test.cpp
    ├── receiver_test.cpp
    └── utils_test.cpp
```

## Зависимости (автоматически загружаются через FetchContent)
- **spdlog** v1.11.0 - логирование
- **Standalone Asio** v1.28.0 (header-only) - сетевое взаимодействие
- **Google Test** v1.12.1 - тестирование

