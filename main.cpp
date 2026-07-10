#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iomanip>

namespace fs = std::filesystem;

class MiniGit {
private:
    const fs::path repo_dir = ".minigit";
    const fs::path snapshot_dir = ".minigit/snapshots";
    const fs::path log_file = ".minigit/log.txt";
    const fs::path config_file = ".minigit/repo_config.txt";

    // Reads the current commit number from config
    int get_next_commit_id() {
        int id = 1;
        std::ifstream config(config_file);
        if (config.is_open()) {
            config >> id;
        }
        return id;
    }

    // Increments the internal commit tracker counter
    void increment_commit_id(int current_id) {
        std::ofstream config(config_file);
        if (config.is_open()) {
            config << (current_id + 1);
        }
    }

public:
    // Command 1: Initialize the repository structure
    bool init() {
        if (fs::exists(repo_dir)) {
            std::cout << "Repository already initialized.\n";
            return false;
        }

        fs::create_directory(repo_dir);
        fs::create_directory(snapshot_dir);

        std::ofstream config(config_file);
        if (config.is_open()) config << 1;

        std::ofstream log(log_file); // Creates empty log file

        std::cout << "Initialized empty MiniGit repository successfully.\n";
        return true;
    }

    // Command 2: Snapshot the directory status
    bool commit(const std::string& message) {
        if (!fs::exists(repo_dir)) {
            std::cout << "Error: Not a minigit repository. Run 'init' first.\n";
            return false;
        }

        int current_id = get_next_commit_id();
        fs::path current_snapshot = snapshot_dir / ("commit_" + std::to_string(current_id));
        fs::create_directory(current_snapshot);

        // Copy working files into the snapshot directory, ignoring the .minigit folder itself
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (entry.path().filename() != repo_dir && !entry.is_directory()) {
                fs::copy(entry.path(), current_snapshot / entry.path().filename());
            }
        }

        // Append tracking details to history log file
        std::ofstream log(log_file, std::ios::app);
        if (log.is_open()) {
            auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            log << "COMMIT_ID: " << current_id << "\n";
            log << "MESSAGE: " << message << "\n";
            log << "TIMESTAMP: " << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "\n";
            log << "-------------------------------------\n";
        }

        increment_commit_id(current_id);
        std::cout << "Changes committed successfully. Commit ID: " << current_id << "\n";
        return true;
    }

    // Command 3: Print historical data
    void print_log() {
        if (!fs::exists(log_file)) {
            std::cout << "Error: Not a minigit repository.\n";
            return;
        }

        std::ifstream log(log_file);
        std::string line;
        bool has_commits = false;
        
        while (std::getline(log, line)) {
            has_commits = true;
            std::cout << line << "\n";
        }
        
        if (!has_commits) {
            std::cout << "No commits recorded yet.\n";
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: minigit <command> [message]\n";
        std::cout << "Commands:\n  init\n  commit \"your message\"\n  log\n";
        return 1;
    }

    std::string command = argv[1];
    MiniGit git;

    if (command == "init") {
        git.init();
    } else if (command == "commit") {
        if (argc < 3) {
            std::cout << "Error: Please provide a commit message description.\n";
            return 1;
        }
        git.commit(argv[2]);
    } else if (command == "log") {
        git.print_log();
    } else {
        std::cout << "Unknown command: " << command << "\n";
    }

    return 0;
}