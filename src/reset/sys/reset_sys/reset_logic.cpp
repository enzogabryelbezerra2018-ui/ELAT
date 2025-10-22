#include "reset_ui.h"
#include <thread>
#include <chrono>

namespace ResetLogic {

    // Simula apagamento seguro dos dados
    void perform_reset() {
        ResetUI::init_ui();
        ResetUI::show_erasing_animation(5); // 5 segundos de animação

        // Simulação de "apagar dados"
        std::cout << "[RESET_SYS] Cleaning partitions..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "[RESET_SYS] Reset completed. System will restart." << std::endl;
    }

} // namespace ResetLogic
