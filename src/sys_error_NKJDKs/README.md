# sys_error_NKJDKs - Safe Emergency Menu

Descrição:
- Menu de emergência que aparece em caso de erro grave.
- Oferece duas opções seguras: RESET (entrar em recovery / factory reset) ou RECOVER KERNEL (reinstalar / recuperar kernel de forma controlada).
- **NÃO** apaga o kernel nem realiza operações irreversíveis.

Como compilar:
  g++ main.cpp -o sys_error_menu -std=c++17

Uso (teste):
  sudo ./sys_error_menu

Aviso:
  Teste em QEMU / ambiente de desenvolvimento primeiro. Algumas ações requerem privilégios root.
