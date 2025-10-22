#include "reset_transition.h"
#include "reset_ui.h"
#include <linux/delay.h>
#include <linux/kernel.h>

namespace ResetTransition {

void fade_in_text(const char* str,int y,int duration_ms){
    int steps=duration_ms/50;
    for(int i=0;i<=steps;i++){
        ResetUI::clear_ui();
        uint32_t intensity=(i*255)/steps;
        uint32_t color=(intensity<<16)|(intensity<<8)|intensity;
        ResetUI::draw_text_centered(str,y,color);
        msleep(50);
    }
}

void fade_out_text(const char* str,int y,int duration_ms){
    int steps=duration_ms/50;
    for(int i=steps;i>=0;i--){
        ResetUI::clear_ui();
        uint32_t intensity=(i*255)/steps;
        uint32_t color=(intensity<<16)|(intensity<<8)|intensity;
        ResetUI::draw_text_centered(str,y,color);
        msleep(50);
    }
}

void animate_dots(int y,int duration_sec){
    const char* dots[]={"",".","..","..."};
    int steps=duration_sec*2;
    for(int i=0;i<steps;i++){
        ResetUI::clear_ui();
        ResetUI::draw_text_centered("ERASING",200,0xFFFFFFFF);
        ResetUI::draw_text_centered(dots[i%4],y,0xFFFFFFFF);
        msleep(500);
    }
}

void transition_boot_to_reset(){
    fade_in_text("ELAT BOOT",150,1000);
    msleep(500);
    fade_out_text("ELAT BOOT",150,800);

    fade_in_text("MENU MODE",150,800);
    msleep(800);
    fade_out_text("MENU MODE",150,500);

    ResetUI::init_ui();
    animate_dots(240,5);
}

} // namespace ResetTransition
