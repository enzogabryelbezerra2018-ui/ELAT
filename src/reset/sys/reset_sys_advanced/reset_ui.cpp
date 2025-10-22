#include "reset_ui.h"
#include "fonts/bitmap_font_complete.h"
#include <linux/kernel.h>
#include <linux/vmalloc.h>
#include <linux/delay.h>
#include <linux/string.h>

namespace ResetUI {

struct FrameBuffer {
    unsigned int width,height,bpp;
    unsigned long screensize;
    uint32_t* fbmem;
} fb;

static void fb_init(){
    fb.width=640; fb.height=480; fb.bpp=32;
    fb.screensize=fb.width*fb.height*(fb.bpp/8);
    fb.fbmem=(uint32_t*)vmalloc(fb.screensize);
    if(!fb.fbmem) printk("[RESET_SYS_UI] Falha framebuffer\n");
    memset(fb.fbmem,0,fb.screensize);
}

void clear_ui(){ if(fb.fbmem) memset(fb.fbmem,0,fb.screensize); }

static void draw_pixel(int x,int y,uint32_t color){
    if(x>=0 && x<(int)fb.width && y>=0 && y<(int)fb.height)
        fb.fbmem[y*fb.width+x]=color;
}

static void draw_char(char c,int x,int y,uint32_t color){
    const uint8_t* bitmap=nullptr;
    if(c>='A' && c<='Z') bitmap=font8x8_complete[c-'A'];
    else if(c=='.') bitmap=font_dot;
    if(!bitmap) return;
    for(int row=0;row<8;row++)
        for(int col=0;col<8;col++)
            if(bitmap[row] & (1<<(7-col))) draw_pixel(x+col,y+row,color);
}

void draw_text_centered(const char* str,int y,uint32_t color){
    int len=strlen(str);
    int text_width=len*10;
    int x=(fb.width-text_width)/2;
    int offset=0;
    for(int i=0;str[i];i++){
        draw_char(str[i],x+offset,y,color);
        offset+=10;
    }
}

void init_ui(){
    fb_init();
    for(int intensity=0;intensity<=255;intensity+=15){
        clear_ui();
        uint32_t color=(intensity<<16)|(intensity<<8)|intensity;
        draw_text_centered("ERASING",200,color);
        msleep(50);
    }
}

void show_erasing_animation(int duration_sec){
    const char* dots[]={"",".","..","..."};
    int steps=duration_sec*2;
    for(int i=0;i<steps;i++){
        clear_ui();
        draw_text_centered("ERASING",200,0xFFFFFFFF);
        draw_text_centered(dots[i%4],240,0xFFFFFFFF);
        msleep(500);
    }
}

} // namespace ResetUI
