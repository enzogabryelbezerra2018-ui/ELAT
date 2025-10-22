#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/reboot.h>
#include <linux/delay.h>
#include <linux/input.h>

extern void start_menu_ui(void);  // vem do código em C++ (modo gráfico)
extern int framebuffer_detectado(void);

static void elat_logo(void)
{
    printk("\n\n");
    printk("███████╗██╗      █████╗ ████████╗\n");
    printk("██╔════╝██║     ██╔══██╗╚══██╔══╝\n");
    printk("█████╗  ██║     ███████║   ██║   \n");
    printk("██╔══╝  ██║     ██╔══██║   ██║   \n");
    printk("██║     ███████╗██║  ██║   ██║   \n");
    printk("╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   \n\n");
    printk("=== ELAT KERNEL MENU MODE ===\n\n");
}

static void elat_menu_show_options(void)
{
    printk("┌───────────────────────────────┐\n");
    printk("│          MENU MODE            │\n");
    printk("├───────────────────────────────┤\n");
    printk("│ [1] Reboot System             │\n");
    printk("│ [2] Power Off                 │\n");
    printk("│ [3] Reset Kernel (SYSRESET)   │\n");
    printk("│ [4] Continue Boot (if safe)   │\n");
    printk("└───────────────────────────────┘\n");
    printk("\nSelecione uma opção com o número correspondente.\n");
}

static void elat_handle_option(int opt)
{
    switch (opt) {
    case '1':
        printk("[ELAT] Reiniciando o sistema...\n");
        msleep(1000);
        kernel_restart(NULL);
        break;

    case '2':
        printk("[ELAT] Desligando...\n");
        msleep(1000);
        kernel_power_off();
        break;

    case '3':
        printk("[ELAT] Resetando sistema (SYSRESET)...\n");
        msleep(1000);
        kernel_halt();
        break;

    case '4':
        printk("[ELAT] Tentando continuar a execução...\n");
        break;

    default:
        printk("[ELAT] Opção inválida.\n");
        break;
    }
}

void elat_menu_mode_start(void)
{
    elat_logo();

    if (framebuffer_detectado()) {
        printk("[ELAT] Framebuffer detectado, iniciando modo gráfico...\n");
        start_menu_ui();  // chama o modo gráfico em menu_mode_ui.cpp
        return;
    }

    printk("[ELAT] Nenhum framebuffer detectado, iniciando modo texto.\n");
    elat_menu_show_options();

    char opt = 0;
    printk("\nAguardando entrada do usuário...\n");

    while (!opt) {
        opt = printk_getchar();
        if (opt >= '1' && opt <= '4') {
            elat_handle_option(opt);
            break;
        }
        msleep(100);
    }

    printk("[ELAT] Menu encerrado.\n");
}
