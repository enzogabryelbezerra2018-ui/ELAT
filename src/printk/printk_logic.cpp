#include "printk_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>

namespace PRINTK_Logic {

void display_and_wait(const char* title, const char* msg, int seconds){
    PRINTK_UI::init_ui();
    PRINTK_UI::show_message(title, msg);

    for(int i=seconds;i>0;i--){
        printk("[PRINTK_Logic] Continuando em %d segundos...\n", i);
        msleep(1000);
    }
}

} // namespace PRINTK_Logic
