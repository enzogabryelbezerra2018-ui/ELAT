#!/bin/sh
# actions.sh - ações seguras para sys_error_NKJDKs
# Uso: actions.sh reset | recover_kernel

set -e

ACTION="$1"

log() { echo "[actions] $*"; }

case "$ACTION" in
    reset)
        log "Tentando entrar em modo de recuperação (kexec -> /boot/recovery.img) ..."
        if [ -f /boot/recovery.img ]; then
            if command -v kexec >/dev/null 2>&1; then
                log "Carregando /boot/recovery.img via kexec..."
                kexec -l /boot/recovery.img --append='root=/dev/ram0 rw' && \
                log "Executando kexec -e (vai reiniciar agora)" && kexec -e
                # se kexec -e retornar algo, saia
                log "kexec retornou; verifique mensagens."
            else
                log "kexec não disponível. Considere instalar pacote kexec-tools."
                exit 2
            fi
        else
            log "Imagem /boot/recovery.img não encontrada. Opcão: criar initramfs de recuperação ou reinstalar kernel."
            exit 3
        fi
        ;;
    recover_kernel)
        log "Iniciando procedimento de recuperação do kernel (não destrutivo)."
        # Tenta detectar gestor de pacote e reinstalar kernel-pacote (ex.: apt, dnf, pacman)
        if command -v apt >/dev/null 2>&1; then
            log "APT detectado: tentando 'apt-get install --reinstall linux-image-$(uname -r)' (pode requerer internet)"
            apt-get update
            apt-get install --reinstall -y "linux-image-$(uname -r)" || \
              log "Falha em reinstalar via apt, verifique conectividade/repositório."
        elif command -v dnf >/dev/null 2>&1; then
            log "DNF detectado: tentando 'dnf reinstall kernel' (ou ajuste conforme distro)"
            dnf reinstall -y kernel || log "Falha em dnf reinstall kernel"
        elif command -v pacman >/dev/null 2>&1; then
            log "Pacman detectado: tentando 'pacman -S linux' (ajuste conforme sua pkg)"
            pacman -S --noconfirm linux || log "Falha em pacman -S linux"
        else
            log "Nenhum gerenciador de pacotes suportado detectado. Forneça uma imagem de recovery em /boot/recovery.img ou reinstale manualmente."
            exit 4
        fi
        log "Operação de recuperação do kernel finalizada (verifique o bootloader e arquivos em /boot)."
        ;;
    *)
        echo "Usage: $0 {reset|recover_kernel}"
        exit 1
        ;;
esac
