#ifndef LITH_UI_H
#define LITH_UI_H

#include <string>

namespace LITH_UI {
    // inicializa acessos (framebuffer detect)
    void init_ui();

    // exibe o aviso principal no canto superior com cor
    // severity: 0 = green, 1 = yellow, 2 = red
    void show_lithium_warning(int severity);

    // exibe "No command" texto e o menu de ações usuário
    void show_no_command_and_menu();

    // limpa recursos
    void cleanup_ui();

    // detecta se framebuffer está disponível
    bool framebuffer_available();
}

#endif
