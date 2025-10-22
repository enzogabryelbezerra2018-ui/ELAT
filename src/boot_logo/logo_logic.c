#include <stdio.h>
#include <unistd.h>

// Função de espera simulando carregamento do sistema
void wait_for_system_load(int seconds) {
    printf("[BOOT_LOGO] Sistema carregando");
    for (int i = 0; i < seconds; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf(" ✅\n");
}
