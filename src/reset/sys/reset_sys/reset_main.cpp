#include "reset_ui.h"
#include "reset_logic.cpp" // chama a lógica do reset
#include <iostream>
#include <cstdlib>

int main() {
    std::cout << "[RESET_SYS] Starting reset sequence..." << std::endl;
    ResetLogic::perform_reset();

    // Reinicia o sistema após reset (simulação)
    std::cout << "[RESET_SYS] Rebooting system..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::system("reboot"); // ou kernel_restart no kernel
    return 0;
}
