#include "printk_ui.h"
#include <linux/kernel.h>

namespace PRINTK_UI {

void init_ui(){
    printk("[PRINTK_UI] Inicializando interface de console printk...\n");
}

void show_message(const char* title, const char* msg){
    printk("\n========================\n");
    printk("     %s\n", title);
    printk("========================\n");
    printk("%s\n\n", msg);
}

} // namespace PRINTK_UI
