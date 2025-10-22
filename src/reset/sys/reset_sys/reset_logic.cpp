#include "reset_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>

namespace ResetLogic {

void perform_reset() {
    ResetUI::init_ui();
    ResetUI::show_erasing_animation(5); // 5 segundos animados

    printk("[RESET_SYS] Apagando dados do sistema...\n");
    msleep(2000); // simulação de limpeza
    printk("[RESET_SYS] Reset concluído, reiniciando...\n");

    // Reinicia o sistema via kernel
    kernel_restart(NULL);
}

} // namespace ResetLogic
