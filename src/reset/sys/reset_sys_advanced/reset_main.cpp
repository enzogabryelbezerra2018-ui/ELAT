#include "reset_ui.h"
#include "reset_logic.cpp"
#include "reset_transition.h"

extern "C" void start_reset_sys(){
    printk("[RESET_SYS] Iniciando reset avançado completo...\n");

    ResetUI::init_ui();
    ResetTransition::transition_boot_to_reset();
    ResetLogic::perform_reset();
}
