# Git-Lite: A Lightweight Version Control Engine in C++

Git-Lite is a minimal, command-line version control system built from scratch in modern C++. It mimics core Git behaviors by managing 
internal file snapshots, tracking directory states, and maintaining a structured commit history log without relying on external third-party 
libraries.

This project was built to master operating system file manipulations, low-level binary streams, and modern C++ system design paradigms 
required for high-performance software engineering roles.

## Key Features
* Repository Initialization (`init`):** Programmatically sets up an isolated data structure (`.minigit/`) to store configurations, history 
metadata logs, and atomic snapshots.
* State Commits (`commit`):** Deep-copies active system files into immutable version snapshots, tracking human-readable descriptions 
alongside absolute UNIX timestamps.
* **History Traversal (`log`):** Sequentially reads and parses continuous binary/text tracking log streams to output real-time historical 
timelines directly to the terminal.

##️ Technical Skills Demonstrated
* Modern C++ Architecture:** Leverages `std::filesystem` (C++17) for robust, platform-independent directory iterations and path handling.
* Resource Optimization:** Utilizes high-performance sequential File I/O input/output streams (`std::ifstream`, `std::ofstream`) ensuring 
stable memory performance even when tracking substantial assets.
* **Command-Line Interface Parsing:** Implements native execution argument processing (`argc`, `argv`) to handle responsive terminal 
commands.

## How to Build & Run

### 1. Compilation
Use any C++ compiler supporting C++17 or higher:
```bash
g++ -std=c++17 main.cpp -o minigit




