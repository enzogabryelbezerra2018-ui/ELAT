#ifndef RESET_UI_H
#define RESET_UI_H

#include <linux/types.h>

namespace ResetUI {

    // Inicializa framebuffer (kernel-space)
    void init_ui();

    // Mostra o texto "ERASING" com animação dos 3 pontinhos
    void show_erasing_animation(int duration_sec);

    // Limpa framebuffer
    void clear_ui();

} // namespace ResetUI

#endif
