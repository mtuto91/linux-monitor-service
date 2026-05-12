# linux-monitor-service

A Linux system monitoring service that continuously reads CPU temperature and logs structured output.

## Features

- Reads CPU temperature every 1 second
- Displays temperature status (OK or WARN if > 80°C)
- Timestamp with millisecond precision
- Clean shutdown handling (SIGINT/SIGTERM)

## Building

```bash
cmake -B build
cmake --build build
```

## Running

```bash
./build/monitor-service
```

To stop the service gracefully, press `Ctrl+C` or send `SIGTERM`.

## Output Example

```
[INFO] Monitor service starting...
2026-05-11 21:13:20.067 [OK] Temperature: 67°C
2026-05-11 21:13:21.068 [OK] Temperature: 67°C
2026-05-11 21:13:22.069 [OK] Temperature: 66°C
[INFO] Shutdown signal received. Cleaning up...
[INFO] Monitor service stopped.
```
