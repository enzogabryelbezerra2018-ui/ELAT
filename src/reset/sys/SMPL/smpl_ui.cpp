#include "smpl_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>

namespace SMPL_UI {

void init_ui(){
    printk("[SMPL_UI] Inicializando interface de erro SMPL...\n");
}

void show_error_message(){
    printk("\n========================\n");
    printk("      SMPL ERROR\n");
    printk("========================\n");
    printk("Sistema detectou erro crítico SMPL.\n");
    printk("O kernel irá reiniciar em breve...\n\n");
}

} // namespace SMPL_UI
