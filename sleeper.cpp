#include <iostream>
#include <chrono>
#include <thread>

int main() {
    std::cout << "Long-running process started." << std::endl;

    // Enter an infinite loop
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Sleep for 1 second
        std::cout << "Running..." << std::endl;
    }

    // The program will never reach this point
    return 0;
}