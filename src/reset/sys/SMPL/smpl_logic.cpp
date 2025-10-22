#include "smpl_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>

namespace SMPL_Logic {

void handle_smpl_error(){
    SMPL_UI::init_ui();
    SMPL_UI::show_error_message();

    /* Pausa simulando animação ou limpeza */
    for(int i=3;i>0;i--){
        printk("[SMPL_Logic] Reiniciando em %d...\n", i);
        msleep(1000);
    }

    /* Reinício do kernel seguro */
    printk("[SMPL_Logic] Reiniciando agora.\n");
    kernel_restart(NULL);
}

} // namespace SMPL_Logic
