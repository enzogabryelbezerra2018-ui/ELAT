#include <linux/kernel.h>
#include <linux/delay.h>
#include "menu_mode.c"

void elat_panic_handler(const char *reason)
{
    printk("\n[ELAT PANIC] Kernel detectou falha crítica: %s\n", reason);
    msleep(500);
    elat_menu_mode_start();
}
