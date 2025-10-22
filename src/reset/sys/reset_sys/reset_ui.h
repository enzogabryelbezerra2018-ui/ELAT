#ifndef RESET_UI_H
#define RESET_UI_H

#include <string>

namespace ResetUI {

    // Inicializa a UI do reset
    void init_ui();

    // Mostra o texto "ERASING" com os 3 pontinhos animados
    void show_erasing_animation(int duration_sec);

    // Limpa a tela / framebuffer (ou terminal)
    void clear_ui();

} // namespace ResetUI

#endif
