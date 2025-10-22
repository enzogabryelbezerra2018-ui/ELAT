# no_command_error

Descrição
---------
"no_command_error" é o nome dado para uma situação em que o sistema fica sem um processo/command responsável (ou entra num estado sem loop de comando),
passa a reiniciar/resetar aleatoriamente e causa corrupção de dados nos dispositivos de armazenamento.

Objetivo
--------
Fornecer:
- documentação do problema,
- medidas de mitigação imediatas,
- um handler kernel (exemplo) que tenta sincronizar e remount read-only antes de reiniciar,
- scripts userspace para tentativa de recuperação segura.

AVISO IMPORTANTE
----------------
- Teste TODO esse código em ambiente de desenvolvimento (QEMU, board de testes).
- Operações de reboot/forçado/remount podem causar perda de dados se usadas incorretamente.
- Ajuste o código ao seu kernel/arquitetura; algumas APIs de kernel podem variar.

Recomendações gerais
--------------------
1. Use um sistema de arquivos com journaling (ext4/journal, f2fs, etc).  
2. Considerar root em overlayfs (imagem raiz imutável + overlay para mudanças) para evitar corrupção do base.  
3. Habilitar watchdogs de userspace e kernel (watchdog hardware) para reinício controlado.  
4. Fazer backups regulares; configurar montagem read-only quando apropriado.  
5. Coletar logs (serial, journal) e enviar para servidor remoto antes de reinício (quando possível).

Conteúdo desta pasta
--------------------
- `kernel_handler.c`    — exemplo de handler kernel (sincroniza e tenta remount readonly antes de reiniciar)
- `recovery.sh`         — script userspace que tenta recuperar/limpar estado e reiniciar seguramente
- `no_command_recovery.service` — systemd service que executa `recovery.sh` automaticamente
- `notes.txt`           — observações rápidas e checklist de testes
