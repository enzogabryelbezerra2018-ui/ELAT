/* kernel_handler.c
 *
 * Exemplo: handler para "no_command_error" no kernel ELAT.
 *
 * AVISO: adaptar à sua tree do kernel. Testar em dev/QEMU.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/reboot.h>
#include <linux/delay.h>
#include <linux/fs.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/uaccess.h>

/* forward: função que o resto do kernel pode chamar quando detectar o erro */
void elat_no_command_error_handler(const char *reason)
{
    pr_emerg("[ELAT][NO_CMD] Detected no_command_error: %s\n", reason ? reason : "unspecified");

    /* 1) Tentar sincronizar todos os sistemas de arquivos */
    pr_emerg("[ELAT][NO_CMD] Executando sync_filesystems()\n");
    /* sync_filesystems(wait) — wait = 0 (não espera) / 1 (espera)
       -- se a sua tree do kernel não expor essa função, substitua por uma chamada apropriada.
    */
    sync_filesystems(1);

    /* 2) Tentar remount read-only da raiz para minimizar corrupção.
       Atenção: remount pode não ser possível em alguns setups (root em initramfs, overlayfs, etc.)
    */
    pr_emerg("[ELAT][NO_CMD] Tentando remount '/' read-only\n");
    {
        struct path root_path;
        int err = kern_path("/", LOOKUP_REVAL, &root_path);
        if (!err) {
            err = vfs_remount_file(&root_path, MS_RDONLY, NULL);
            if (err)
                pr_emerg("[ELAT][NO_CMD] remount '/' -> RO falhou: %d\n", err);
            else
                pr_emerg("[ELAT][NO_CMD] remount '/' -> RO OK\n");
            path_put(&root_path);
        } else {
            pr_emerg("[ELAT][NO_CMD] Não foi possível localizar path '/': %d\n", err);
        }
    }

    /* 3) Dar um pequeno delay para garantir flush de buffers */
    msleep(500);

    /* 4) Se disponível, acionar mecanismos de export de logs (serial, network) aqui
       (ex.: iniciar thread para puxar dmesg/journal para /tmp antes de reboot) */

    pr_emerg("[ELAT][NO_CMD] Reiniciando de forma segura (kernel_restart)\n");
    /* Chamar reinício controlado */
    kernel_restart(NULL);

    /* Se kernel_restart não retornar, como fallback, usar emergency restart */
    pr_emerg("[ELAT][NO_CMD] fallback: emergency_restart\n");
    emergency_restart();
}
EXPORT_SYMBOL(elat_no_command_error_handler);
