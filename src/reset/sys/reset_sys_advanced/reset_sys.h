#ifndef RESET_SYS_H
#define RESET_SYS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Função principal exportada — chamada pelo kernel/menu/panic */
void start_reset_sys(void);

#ifdef __cplusplus
}
#endif

#endif /* RESET_SYS_H */
