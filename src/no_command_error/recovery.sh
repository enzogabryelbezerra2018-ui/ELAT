#!/bin/sh
# recovery.sh — tentativa userspace segura para "no_command_error"
# Coloque em /usr/local/sbin/recovery_no_command.sh e torne executável.

LOG=/var/log/no_command_recovery.log

echo "[no_command_recovery] detectado - iniciando procedimento" >> $LOG

# 1) avisar e tentar enviar logs via rede (se tiver link) — opcional
# nc/ssh scp etc; aqui só logamos
date >> $LOG
dmesg -T >> $LOG

# 2) rodar sync repetido para maior chance de flush
sync
sleep 1
sync

# 3) tentar remount read-only da raiz (padrão)
if mountpoint -q /; then
    echo "[no_command_recovery] tentando remount / ro" >> $LOG
    mount -o remount,ro /
    if [ $? -eq 0 ]; then
        echo "[no_command_recovery] remount / ro OK" >> $LOG
    else
        echo "[no_command_recovery] remount / ro FALHOU" >> $LOG
    fi
fi

# 4) sincronizar de novo e aguardar
sync
sleep 1

# 5) reboot controlado (se systemctl disponível, use)
if command -v systemctl >/dev/null 2>&1; then
    echo "[no_command_recovery] reiniciando via systemctl" >> $LOG
    systemctl reboot || reboot -f
else
    echo "[no_command_recovery] reiniciando via reboot -f" >> $LOG
    reboot -f
fi

# fallback — se não reiniciou, forçar
sleep 5
echo "[no_command_recovery] fallback: reboot emergency" >> $LOG
reboot -f
