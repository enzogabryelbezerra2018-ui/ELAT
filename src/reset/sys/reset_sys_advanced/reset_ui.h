#ifndef RESET_UI_H
#define RESET_UI_H

#include <linux/types.h>

namespace ResetUI {

    void init_ui();
    void show_erasing_animation(int duration_sec);
    void clear_ui();

} // namespace ResetUI

#endif
