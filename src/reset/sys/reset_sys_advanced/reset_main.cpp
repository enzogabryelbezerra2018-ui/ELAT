#include "reset_ui.h"
#include "reset_logic.cpp"

extern "C" void start_reset_sys(){
    printk("[RESET_SYS] Iniciando reset avançado - primeira parte...\n");
    ResetLogic::perform_reset();
}
