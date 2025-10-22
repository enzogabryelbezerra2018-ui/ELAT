// main.cpp — interação principal (usuário-espaço)
#include "ui.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

int run_tts(const std::string &msg) {
    // chama tts.sh em background (não bloquante)
    std::string cmd = "./tts.sh \"" + msg + "\" &";
    return system(cmd.c_str());
}

int do_safe_mode() {
    // tenta bloquear rádios via rfkill (não permanente)
    if (system("which rfkill >/dev/null 2>&1") == 0) {
        std::cout << "[Action] Bloqueando rádios (rfkill block all)\n";
        system("rfkill block all");
        std::cout << "[Action] Radios bloqueados temporariamente.\n";
        return 0;
    } else {
        std::cout << "[Action] rfkill não disponível.\n";
        return -1;
    }
}

int do_shutdown() {
    std::cout << "[Action] Executando shutdown now.\n";
    // chama shutdown - safe; requer privilégios de root
    system("shutdown -h now");
    return 0;
}

int main() {
    using namespace LITH_UI;
    init_ui();

    // severities: show red by default
    show_lithium_warning(2);

    // show No command and menu
    show_no_command_and_menu();

    // TTS message (calm, robotic) — safe content (no destruct)
    std::string tts_msg = "Attention. The device has detected a lithium related error. "
                          "This is a serious condition. Please power down the device immediately "
                          "and seek professional assistance. If the device is damaged, "
                          "follow safe disposal procedures. Shutdown now.";

    run_tts(tts_msg);

    int choice = 0;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        choice = 4;
    }

    switch (choice) {
        case 1:
            do_shutdown();
            break;
        case 2:
            do_safe_mode();
            std::cout << "Recommended: remove power and seek service.\n";
            break;
        case 3:
        {
            // show disposal.txt
            std::ifstream f("disposal.txt");
            if (f) {
                std::cout << "\n--- Disposal instructions ---\n";
                std::string line;
                while (std::getline(f, line)) std::cout << line << "\n";
                f.close();
            } else {
                std::cout << "disposal.txt not found.\n";
            }
            break;
        }
        default:
            std::cout << "Dismissed. Returning to idle.\n";
            break;
    }

    cleanup_ui();
    return 0;
}
