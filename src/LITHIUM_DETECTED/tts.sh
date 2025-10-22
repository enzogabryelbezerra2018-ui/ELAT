#!/bin/sh
# tts.sh — usa espeak-ng se disponível, senão usa printf como fallback
MSG="$1"

# calm voice params for espeak-ng (adjust per system)
if command -v espeak-ng >/dev/null 2>&1; then
    espeak-ng --stdout -v en-us+f3 -s 130 "$MSG" | aplay --quiet 2>/dev/null || espeak-ng -v en-us+f3 -s 130 "$MSG"
elif command -v espeak >/dev/null 2>&1; then
    espeak -v en-us -s 130 "$MSG"
else
    # fallback: print message
    printf "%s\n" "$MSG"
fi
