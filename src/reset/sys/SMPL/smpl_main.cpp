#include "smpl_ui.h"
#include "smpl_logic.cpp"

extern "C" void start_smpl_error(){
    printk("[SMPL_MAIN] SMPL Error iniciado.\n");
    SMPL_Logic::handle_smpl_error();
}
