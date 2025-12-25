# File Transfer with Asio

A simple TCP file transfer utility using Asio.

## Building the project

```bash
cmake -S . -B cmake-build-debug -G "Ninja"
cmake --build cmake-build-debug --config Debug
```

In CLion you can simply press Ctrl+F9 to rebuild the project.

## Usage

### 1. Start the receiver

Run the receiver first; it will wait for an incoming connection:

```bash
cd cmake-build-debug
./receiver.exe 8080 received_file.txt
```

Where:
- `8080` is the listening port
- `received_file.txt` is the path to save the incoming file

You should see logs like:
```
[2025-12-22 22:08:26.373] [info] Receiver started
[2025-12-22 22:08:26.373] [info] Listening on port 8080...
```

### 2. Send a file

In another terminal run the sender:

```bash
cd cmake-build-debug
./sender.exe 127.0.0.1 8080 test_file.txt
```

Where:
- `127.0.0.1` is the receiver IP (use localhost for local testing)
- `8080` is the receiver port (must match the receiver)
- `test_file.txt` is the file to send

Sender output example:
```
[2025-12-22 22:08:30.123] [info] Sender started
[2025-12-22 22:08:30.124] [info] Reading file: test_file.txt
[2025-12-22 22:08:30.125] [info] File size: 1024 bytes
[2025-12-22 22:08:30.126] [info] Connecting to 127.0.0.1:8080...
[2025-12-22 22:08:30.127] [info] Connected successfully
[2025-12-22 22:08:30.128] [info] Sending file data...
[2025-12-22 22:08:30.150] [info] File sent successfully: 1024 bytes
```

Receiver output example:
```
[2025-12-22 22:08:30.127] [info] Client connected from 127.0.0.1
[2025-12-22 22:08:30.150] [info] Receiving file: 1024 bytes
[2025-12-22 22:08:30.151] [info] File received and saved to: received_file.txt
```

## Example over a network

On the receiving machine (IP: `192.168.1.100`):
```bash
./receiver.exe 8080 received_document.pdf
```

On the sending machine:
```bash
./sender.exe 192.168.1.100 8080 document.pdf
```

## How it works

1. The receiver opens a TCP socket on the specified port and waits for a connection.
2. The sender connects to the receiver using IP and port.
3. The sender sends:
   - First, the file size (8 bytes, uint64_t)
   - Then the file content
4. The receiver reads the data and writes it to a file.
5. All operations are logged using spdlog.

## Common issues and troubleshooting

"Connection refused"
- Make sure the receiver is started first.
- Check that the port is not in use by another program.
- Verify firewall settings.

"Failed to read file"
- Ensure the file exists.
- Check file permissions.

"Address already in use"
- The port is already taken; choose a different port.
- Or wait ~30 seconds for the OS to free the port.

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

- C++20
- Asio (standalone header-only, used instead of Boost.Asio)
- spdlog for logging
- Google Test for unit testing

## Notes

- The project uses Asio in standalone mode (ASIO_STANDALONE). If you want to use Boost.Asio instead, adjust `CMakeLists.txt` accordingly.
- On Windows the executables link to the WinSock libraries (`ws2_32`, `mswsock`).
