# File Transfer with Standalone Asio

A simple utility for transferring files over TCP using standalone Asio (header-only library).

## Build

From the project root (recommended):

```powershell
cmake -S . -B cmake-build-debug -G "Ninja"
cmake --build cmake-build-debug --config Debug
```

In CLion: press Ctrl+F9 (Rebuild Project).

## Usage

This project provides two small console programs:

- `receiver.exe` — listens on a port and saves an incoming file
- `sender.exe` — connects to the receiver and sends a file

Both examples below assume you run them from the `cmake-build-debug` directory on Windows.

### 1) Start the receiver

Open a terminal and run:

```powershell
cd cmake-build-debug
.\receiver.exe 8080 received_file.txt
```

Parameters:
- `8080` — port to listen on
- `received_file.txt` — path where the incoming file will be saved

Expected receiver output (example):
```
[info] Receiver started
[info] Listening on port 8080...
```

### 2) Start the sender

In another terminal run:

```powershell
cd cmake-build-debug
.\sender.exe 127.0.0.1 8080 test_file.txt
```

Parameters:
- `127.0.0.1` — receiver IP address (use the actual IP when running across machines)
- `8080` — receiver port
- `test_file.txt` — file to send

Expected sender output (example):
```
[info] Sender started
[info] Reading file: test_file.txt
[info] File size: 1024 bytes
[info] Connecting to 127.0.0.1:8080...
[info] Connected successfully
[info] Sending file data...
[info] File sent successfully: 1024 bytes
```

And the receiver should show something like:
```
[info] Client connected from 127.0.0.1
[info] Receiving file: 1024 bytes
[info] File received and saved to: received_file.txt
```

## Example across machines

On the receiving machine (IP: `192.168.1.100`):

```powershell
.\receiver.exe 8080 received_document.pdf
```

On the sending machine:

```powershell
.\sender.exe 192.168.1.100 8080 document.pdf
```

## How it works

1. The receiver opens a TCP socket on the provided port and waits for a connection.
2. The sender connects to the receiver by IP and port.
3. The sender transmits:
   - First the file size (8 bytes, uint64_t)
   - Then the file content
4. The receiver reads the file size, then the file content, and writes it to disk.
5. All operations are logged via `spdlog`.

## Troubleshooting

- "Connection refused"
  - Make sure the receiver is running before the sender.
  - Ensure the port is not blocked or used by another program.
  - Check firewall settings.

- "Failed to read file"
  - Verify the file exists and the sender has read permission.

- "Address already in use"
  - The port is already occupied; choose another port or wait a short while for the OS to release it.

## Architecture

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

## Technologies

- **C++20** — modern C++ standard
- **Standalone Asio** (header-only) — networking (no full Boost dependency required)
- **spdlog** — fast logging library
- **Google Test** — unit testing framework
- **ws2_32** — Windows Sockets library (used on Windows builds)

## Running tests

After building, run the aggregated test binary:

```powershell
cd cmake-build-debug
.\run_all_tests.exe
```

Or use CTest:

```powershell
cd cmake-build-debug
ctest --output-on-failure
```

## Quickstart (Windows)

1. Rebuild the project in CLion (Ctrl+F9), or use the cmake commands above.
2. Start `receiver.exe` in one terminal.
3. Start `sender.exe` in another terminal to send a file to the receiver.

If you want, I can also create a short PowerShell script that launches the receiver and sender for a quick local demo.
