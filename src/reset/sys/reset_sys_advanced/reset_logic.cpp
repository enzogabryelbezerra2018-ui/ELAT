#include "reset_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>

namespace ResetLogic {

void perform_reset(){
    ResetUI::init_ui();
    ResetUI::show_erasing_animation(5);

    printk("[RESET_SYS] Limpando dados do sistema...\n");
    msleep(2000);
    printk("[RESET_SYS] Reset concluído, reiniciando...\n");

    kernel_restart(NULL);
}

} // namespace ResetLogic
