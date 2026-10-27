# GitLite: Minimal C++ Version-Control Demo

GitLite is a small C++17 command-line project that demonstrates file snapshots and a plain-text commit log. It is an educational example, not a Git-compatible version-control system.

## Commands implemented

- `init` creates the `.minigit/` directory, snapshot directory, commit counter, and log file.
- `commit "message"` copies regular files from the current directory into a numbered snapshot and appends the message and timestamp to the log.
- `log` prints the recorded commit entries.

## Build and run

```bash
g++ -std=c++17 main.cpp -o minigit
./minigit init
./minigit commit "First snapshot"
./minigit log
```

Run the commands from the directory you want to snapshot. The `.minigit/` directory itself is excluded from the copied files.

## Scope and limitations

This project snapshots only regular files directly inside the current directory; it does not recurse into subdirectories. It does not implement staging, diffs, restore, branches, merges, content-addressed objects, or Git compatibility. Treat it as a learning demo rather than a backup tool.
