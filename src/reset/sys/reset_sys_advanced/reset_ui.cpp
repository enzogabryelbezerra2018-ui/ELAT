#include "reset_ui.h"
#include "fonts/bitmap_font_part1.h"
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/vmalloc.h>
#include <linux/string.h>

namespace ResetUI {

struct FrameBuffer {
    unsigned int width, height;
    unsigned int bpp;
    unsigned long screensize;
    uint32_t* fbmem;
} fb;

static void fb_init() {
    fb.width = 640;
    fb.height = 480;
    fb.bpp = 32;
    fb.screensize = fb.width*fb.height*(fb.bpp/8);
    fb.fbmem = (uint32_t*)vmalloc(fb.screensize);
    if (!fb.fbmem)
        printk("[RESET_SYS_UI] Falha framebuffer\n");
    memset(fb.fbmem,0,fb.screensize);
}

void clear_ui() {
    if (!fb.fbmem) return;
    memset(fb.fbmem,0,fb.screensize);
}

static void draw_pixel(int x,int y,uint32_t color){
    if(x>=0 && x<(int)fb.width && y>=0 && y<(int)fb.height)
        fb.fbmem[y*fb.width + x] = color;
}

static void draw_char(char c,int x,int y,uint32_t color){
    const uint8_t* bitmap = nullptr;
    switch(c){
        case 'E': bitmap = font8x8_partial[0]; break;
        case 'R': bitmap = font8x8_partial[1]; break;
        case 'A': bitmap = font8x8_partial[2]; break;
        case 'S': bitmap = font8x8_partial[3]; break;
        case 'I': bitmap = font8x8_partial[4]; break;
        case 'N': bitmap = font8x8_partial[5]; break;
        case 'G': bitmap = font8x8_partial[6]; break;
        case '.': bitmap = font_dot; break;
        default: return;
    }

    for(int row=0;row<8;row++)
        for(int col=0;col<8;col++)
            if(bitmap[row] & (1<<(7-col)))
                draw_pixel(x+col, y+row, color);
}

static void draw_text(const char* str,int x,int y,uint32_t color){
    int offset=0;
    for(int i=0;str[i];i++){
        draw_char(str[i], x+offset, y, color);
        offset += 10; // 8px + 2px spacing
    }
}

void init_ui(){
    fb_init();
    clear_ui();
    draw_text("ERASING", 200, 200, 0xFFFFFFFF);
}

void show_erasing_animation(int duration_sec){
    const char* dots[]={"",".","..","..."};
    int steps = duration_sec*2;
    for(int i=0;i<steps;i++){
        clear_ui();
        draw_text("ERASING", 200, 200, 0xFFFFFFFF);
        draw_text(dots[i%4], 320, 220, 0xFFFFFFFF);
        msleep(500);
    }
}

} // namespace ResetUI
