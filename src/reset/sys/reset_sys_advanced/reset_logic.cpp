#include "reset_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>

namespace ResetLogic {

void perform_reset(){
    ResetUI::init_ui();
    ResetUI::show_erasing_animation(5);

    printk("[RESET_SYS] Simulação de limpeza de dados...\n");
    msleep(2000);
    printk("[RESET_SYS] Reset pronto, reiniciando...\n");

    // Reinício kernel-space
    kernel_restart(NULL);
}

} // namespace ResetLogic
