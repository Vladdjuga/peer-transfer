# File Transfer with Boost.Asio

Простая утилита для передачи файлов по TCP с использованием Boost.Asio.

## Сборка проекта

```bash
cmake -S . -B cmake-build-debug -G "Ninja"
cmake --build cmake-build-debug --config Debug
```

В CLion просто нажмите **Ctrl+F9** для пересборки.

## Использование

### 1. Запустите получатель (receiver)

Сначала запустите программу-получатель, которая будет ждать входящее соединение:

```bash
cd cmake-build-debug
./receiver.exe 8080 received_file.txt
```

Где:
- `8080` - порт для прослушивания
- `received_file.txt` - путь для сохранения полученного файла

Вы увидите:
```
[2025-12-22 22:08:26.373] [info] Receiver started
[2025-12-22 22:08:26.373] [info] Listening on port 8080...
```

### 2. Отправьте файл (sender)

В другом терминале запустите отправителя:

```bash
cd cmake-build-debug
./sender.exe 127.0.0.1 8080 test_file.txt
```

Где:
- `127.0.0.1` - IP адрес получателя (localhost для локального теста)
- `8080` - порт получателя (должен совпадать с портом receiver)
- `test_file.txt` - файл для отправки

Вы увидите:
```
[2025-12-22 22:08:30.123] [info] Sender started
[2025-12-22 22:08:30.124] [info] Reading file: test_file.txt
[2025-12-22 22:08:30.125] [info] File size: 1024 bytes
[2025-12-22 22:08:30.126] [info] Connecting to 127.0.0.1:8080...
[2025-12-22 22:08:30.127] [info] Connected successfully
[2025-12-22 22:08:30.128] [info] Sending file data...
[2025-12-22 22:08:30.150] [info] File sent successfully: 1024 bytes
```

А получатель покажет:
```
[2025-12-22 22:08:30.127] [info] Client connected from 127.0.0.1
[2025-12-22 22:08:30.150] [info] Receiving file: 1024 bytes
[2025-12-22 22:08:30.151] [info] File received and saved to: received_file.txt
```

## Пример использования по сети

### На компьютере-получателе (IP: 192.168.1.100):
```bash
./receiver.exe 8080 received_document.pdf
```

### На компьютере-отправителе:
```bash
./sender.exe 192.168.1.100 8080 document.pdf
```

## Как это работает

1. **Receiver** открывает TCP-сокет на указанном порту и ждёт подключения
2. **Sender** подключается к receiver по IP и порту
3. Sender отправляет:
   - Сначала размер файла (8 байт, uint64_t)
   - Затем содержимое файла
4. Receiver принимает данные и сохраняет в файл
5. Логирование всех операций через spdlog

## Возможные проблемы

### "Connection refused"
- Убедитесь, что receiver запущен первым
- Проверьте, что порт не занят другой программой
- Проверьте firewall настройки

### "Failed to read file"
- Убедитесь, что файл существует
- Проверьте права доступа к файлу

### "Address already in use"
- Порт уже занят, выберите другой порт
- Или подождите ~30 секунд, пока система освободит порт

## Архитектура

```
┌──────────┐                    ┌──────────┐
│  Sender  │                    │ Receiver │
│          │                    │          │
│ readFile │                    │ Listen   │
│    ↓     │                    │  :8080   │
│ Connect  │ ───── TCP ────→    │ Accept   │
│    ↓     │                    │    ↓     │
│ Send Size│ ────────────────→  │ Read Size│
│    ↓     │                    │    ↓     │
│ Send Data│ ────────────────→  │ Read Data│
│          │                    │    ↓     │
│          │                    │ writeFile│
└──────────┘                    └──────────┘
```

## Технологии

- **C++20** - современный стандарт C++
- **Boost.Asio** - асинхронный ввод-вывод и сетевое взаимодействие
- **spdlog** - быстрое логирование
- **Google Test** - модульное тестирование
