#ifndef RESET_UI_H
#define RESET_UI_H

#include <linux/types.h>

namespace ResetUI {

    void init_ui();
    void clear_ui();
    void draw_text_centered(const char* str, int y, uint32_t color);
    void show_erasing_animation(int duration_sec);

} // namespace ResetUI

#endif
