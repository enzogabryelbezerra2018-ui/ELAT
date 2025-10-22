#!/bin/sh
# recovery_kexec.sh - carrega uma imagem de recovery e executa
if [ ! -f /boot/recovery.img ]; then
  echo "recovery.img not found in /boot"
  exit 1
fi
if ! command -v kexec >/dev/null 2>&1; then
  echo "kexec not installed; install kexec-tools"
  exit 2
fi
kexec -l /boot/recovery.img --append='root=/dev/ram0 rw'
kexec -e
