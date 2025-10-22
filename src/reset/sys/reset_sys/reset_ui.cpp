#include "reset_ui.h"
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/vmalloc.h>
#include <linux/uaccess.h>
#include <linux/string.h>

namespace ResetUI {

struct FrameBuffer {
    unsigned int width, height;
    unsigned int bpp;
    unsigned long screensize;
    unsigned int* fbmem;
} fb;

// Simulação simples: define tamanho fixo para demo
static void fb_init() {
    fb.width = 640;
    fb.height = 480;
    fb.bpp = 32;
    fb.screensize = fb.width * fb.height * (fb.bpp/8);
    fb.fbmem = (unsigned int*)vmalloc(fb.screensize);
    if (!fb.fbmem)
        printk("[RESET_SYS][UI] Erro ao alocar framebuffer\n");
}

void clear_ui() {
    if (!fb.fbmem) return;
    memset(fb.fbmem, 0x00, fb.screensize); // fundo preto
}

static void draw_text_big(int x, int y, const char* text, unsigned int color) {
    // Simulação: cada letra ocupa um "bloco" de pixels 16x16
    int i, j;
    for (i = 0; text[i]; i++) {
        int px = x + i * 18;
        int py = y;
        for (int yy=py; yy<py+16; yy++)
            for (int xx=px; xx<px+16; xx++)
                if (xx<fb.width && yy<fb.height)
                    fb.fbmem[yy*fb.width + xx] = color;
    }
}

void init_ui() {
    fb_init();
    clear_ui();
    draw_text_big(50, 50, "ERASING", 0xFFFFFFFF);
}

void show_erasing_animation(int duration_sec) {
    const char* dots[] = {"", ".", "..", "..."};
    int steps = duration_sec * 2; // 500ms por frame
    int i;

    for (i = 0; i < steps; i++) {
        clear_ui();
        draw_text_big(50, 50, "ERASING", 0xFFFFFFFF);
        draw_text_big(200, 80, dots[i % 4], 0xFFFFFFFF); // desenha pontinhos
        msleep(500);
    }
}

} // namespace ResetUI
