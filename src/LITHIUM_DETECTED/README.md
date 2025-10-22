# LITHIUM_DETECTED - Safe Warning UI

Descrição:
- Programa de usuário que mostra aviso "LITHIUM DETECTED" no canto da tela (framebuffer se disponível, senão terminal),
  indica nível de gravidade (Vermelho/Amarelo/Verde), mostra "No command" e reproduz mensagem TTS calma.
- Fornece opções seguras: Shutdown now, Safe Mode (bloquear rádios), Mostrar instruções de descarte.
- **Não** realiza operações destrutivas ou irreversíveis.

Pré-requisitos:
- espeak-ng (para TTS) ou outro TTS instalado (ou comute tts.sh para `aplay`).
- Permissões root para executar ações como shutdown / rfkill.

Como compilar:
g++ main.cpp ui.cpp -o lith_detect -std=c++17
sudo ./lith_detect
