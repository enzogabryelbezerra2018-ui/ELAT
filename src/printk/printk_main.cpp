#include "printk_ui.h"
#include "printk_logic.cpp"

extern "C" void start_printk_message(const char* title, const char* msg, int wait_seconds){
    printk("[PRINTK_MAIN] Iniciando mensagem printk animada...\n");
    PRINTK_Logic::display_and_wait(title, msg, wait_seconds);
}
