// main.cpp
// Menu de emergência safe — sys_error_NKJDKs
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

static void print_header() {
    std::cout << "========================================\n";
    std::cout << "          ELAT - SYS_ERROR_NKJDKs       \n";
    std::cout << "========================================\n\n";
}

static int prompt_choice() {
    std::cout << "Erro crítico detectado.\n\n";
    std::cout << "Ações seguras disponíveis:\n";
    std::cout << "  1) RESET (Entrar em modo de recuperação / Factory Reset de dados)\n";
    std::cout << "  2) RECOVER KERNEL (Reinstalar ou recuperar kernel de forma segura)\n";
    std::cout << "  3) Mostrar logs (dmesg) e instruções de recuperação manual\n";
    std::cout << "  4) Cancelar / Sair\n\n";
    std::cout << "Escolha (1-4): ";
    int c = 0;
    if (!(std::cin >> c)) {
        std::cin.clear();
        std::cin.ignore(1024, '\n');
        return 4;
    }
    return c;
}

static void run_action(const std::string &cmd) {
    std::cout << "[EXEC] " << cmd << "\n";
    int r = system(cmd.c_str());
    std::cout << "[EXEC] comando retornou: " << r << "\n";
}

int main() {
    if (geteuid() != 0) {
        std::cerr << "Aviso: execute como root para executar ações (sudo).\n\n";
    }

    print_header();

    int choice = prompt_choice();

    switch (choice) {
        case 1:
            std::cout << "\n-- RESET selecionado --\n";
            std::cout << "Iremos INVOCAR ações seguras de recuperação.\n";
            std::cout << "Opções: (a) Entrar em recovery via kexec; (b) Factory reset (apagar dados de usuário).\n";
            std::cout << "CONFIRMA executar recovery (y/N)? ";
            {
                char c='n';
                std::cin >> c;
                if (c=='y' || c=='Y') {
                    // chama actions.sh reset
                    run_action("bash actions.sh reset");
                } else {
                    std::cout << "Operação cancelada.\n";
                }
            }
            break;

        case 2:
            std::cout << "\n-- RECOVER KERNEL selecionado --\n";
            std::cout << "Iremos tentar recuperar ou reinstalar o kernel de maneira segura.\n";
            std::cout << "Isso tenta: (1) reinstalar via package manager; (2) usar imagem local recovery.\n";
            std::cout << "CONFIRMA iniciar recovery do kernel (y/N)? ";
            {
                char c='n';
                std::cin >> c;
                if (c=='y' || c=='Y') {
                    run_action("bash actions.sh recover_kernel");
                } else {
                    std::cout << "Operação cancelada.\n";
                }
            }
            break;

        case 3:
            std::cout << "\n-- MOSTRAR LOGS --\n\n";
            std::cout << "[dmesg] (as últimas 200 linhas):\n\n";
            run_action("dmesg | tail -n 200");
            std::cout << "\nSe precisar coletar logs para análise, copie o output para um arquivo e envie para diagnóstico.\n";
            break;

        default:
            std::cout << "Saindo sem executar ações.\n";
            break;
    }

    std::cout << "\nMenu encerrado.\n";
    return 0;
}
