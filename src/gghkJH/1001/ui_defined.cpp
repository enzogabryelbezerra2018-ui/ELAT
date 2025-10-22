#include <string>
#include <iostream>

namespace sys_ui_1001 {

    // Caminho base da UI
    const std::string ui_path = "/sys_ui_1001/";

    // Nome da interface inicial (a distro pode mudar)
    const std::string default_ui_name = "main_ui";

    // Função para registrar a interface inicial
    void define_ui() {
        std::cout << "[UI_DEFINED] Interface inicial definida:\n";
        std::cout << " - Pasta da UI: " << ui_path << "\n";
        std::cout << " - Nome padrão da UI: " << default_ui_name << "\n";
        std::cout << "[UI_DEFINED] ELAT continua sendo só o kernel; cada distro pode usar sua própria UI.\n";
    }

} // namespace sys_ui_1001

// Função C-callable para o kernel/init chamar
extern "C" void register_initial_ui() {
    sys_ui_1001::define_ui();
}
