#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>
#include <iomanip>
#include <ctime>
#include "src /monitor/temperaure_reader.h"

// Global flag for clean shutdown
std::atomic<bool> shutdown_requested(false);

// Signal handler for SIGINT and SIGTERM
void signal_handler(int signal) {
    if (signal == SIGINT || signal == SIGTERM) {
        std::cout << "\n[INFO] Shutdown signal received. Cleaning up..." << std::endl;
        shutdown_requested = true;
    }
}

int main() {
    // Register signal handlers
    std::signal(SIGINT, signal_handler);
    std::signal(SIGTERM, signal_handler);

    std::cout << "[INFO] Monitor service starting..." << std::endl;

    // Main monitoring loop
    while (!shutdown_requested) {
        // Get current timestamp
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            now.time_since_epoch()) % 1000;

        // Read temperature
        int temp = get_max_cpu_temp();

        // Determine status
        std::string status = (temp > 80) ? "WARN" : "OK";

        // Print structured log
        std::cout << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
                  << "." << std::setfill('0') << std::setw(3) << ms.count()
                  << " [" << status << "] Temperature: " << temp << "°C" << std::endl;

        // Sleep for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "[INFO] Monitor service stopped." << std::endl;
    return 0;
}