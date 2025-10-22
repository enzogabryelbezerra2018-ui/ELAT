#include "reset_ui.h"
#include <iostream>
#include <thread>
#include <chrono>

namespace ResetUI {

    void clear_ui() {
        // Simples terminal clear
        std::cout << "\033[2J\033[H"; 
        std::cout.flush();
    }

    void init_ui() {
        clear_ui();
        std::cout << "\n\n";
        std::cout << "███████╗███████╗ █████╗ ████████╗███████╗\n";
        std::cout << "██╔════╝██╔════╝██╔══██╗╚══██╔══╝██╔════╝\n";
        std::cout << "█████╗  ███████╗███████║   ██║   █████╗  \n";
        std::cout << "██╔══╝  ╚════██║██╔══██║   ██║   ██╔══╝  \n";
        std::cout << "███████╗███████║██║  ██║   ██║   ███████╗\n";
        std::cout << "╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝\n\n";
        std::cout << "[RESET_SYS] ERASING DATA...\n\n";
        std::cout.flush();
    }

    void show_erasing_animation(int duration_sec) {
        const std::string base_text = "[RESET_SYS] ERASING";
        const std::string dots[] = {"", ".", "..", "..."};
        int steps = duration_sec * 2; // 500ms por frame
        for (int i = 0; i < steps; ++i) {
            std::cout << "\r" << base_text << dots[i % 4] << "   ";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        std::cout << "\r" << base_text << "..." << std::endl;
    }

} // namespace ResetUI
