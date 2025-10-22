#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>

// Função C da lógica de espera
extern "C" void wait_for_system_load(int seconds);

namespace BootLogo {

    // Função que mostra o texto grande do ELAT
    void show_large_text() {
        std::cout << "\n\n";
        std::cout << "███████╗██╗      █████╗ ████████╗\n";
        std::cout << "██╔════╝██║     ██╔══██╗╚══██╔══╝\n";
        std::cout << "█████╗  ██║     ███████║   ██║   \n";
        std::cout << "██╔══╝  ██║     ██╔══██║   ██║   \n";
        std::cout << "██║     ███████╗██║  ██║   ██║   \n";
        std::cout << "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   \n";
        std::cout << "\n=== ELAT KERNEL BOOT ===\n\n";
    }

    // Função que simula o bootloader embutido
    void bootloader_embedded() {
        std::cout << "[BOOTLOADER] Iniciando bootloader embutido...\n";
        std::cout << "[BOOTLOADER] Detectando hardware...";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << " OK\n";
        std::cout << "[BOOTLOADER] Inicializando drivers...";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << " OK\n";
        std::cout << "[BOOTLOADER] Preparando sistema...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    void start_boot_logo() {
        bootloader_embedded();
        show_large_text();
        wait_for_system_load(5); // espera 5 segundos simulando boot
        std::cout << "[BOOT_LOGO] Sistema pronto para iniciar.\n";
    }

} // namespace BootLogo

extern "C" void start_boot_logo() {
    BootLogo::start_boot_logo();
}
