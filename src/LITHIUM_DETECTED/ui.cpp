// ui.cpp — implementa desenho simples: se /dev/fb0 está presente usa framebuffer mapeado,
// senão cai para saída por printk/console (std::cout).
// Observação: para escrita correta em framebuffer real, ideal usar registered_fb or DRM.
// Aqui fazemos uma implementação simples e segura de fallback.

#include "ui.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <linux/fb.h>
#include <iostream>
#include <fstream>

static int fb_fd = -1;
static unsigned char* fb_mem = nullptr;
static fb_var_screeninfo vinfo;
static fb_fix_screeninfo finfo;
static long screensize = 0;

namespace LITH_UI {

bool framebuffer_available() {
    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) return false;
    close(fd);
    return true;
}

void init_ui() {
    if (framebuffer_available()) {
        fb_fd = open("/dev/fb0", O_RDWR);
        if (fb_fd < 0) {
            printf("[LITH_UI] /dev/fb0 open failed\n");
            fb_fd = -1;
            return;
        }
        ioctl(fb_fd, FBIOGET_FSCREENINFO, &finfo);
        ioctl(fb_fd, FBIOGET_VSCREENINFO, &vinfo);
        screensize = finfo.smem_len;
        fb_mem = (unsigned char*)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb_fd, 0);
        if (fb_mem == MAP_FAILED) {
            perror("[LITH_UI] mmap failed");
            fb_mem = nullptr;
            close(fb_fd);
            fb_fd = -1;
        }
    } else {
        // nothing to do for console mode
    }
}

// helper: clear top-left area (rectangle)
static void fb_clear_rect(int x, int y, int w, int h, uint32_t color) {
    if (!fb_mem) return;
    int width = vinfo.xres;
    for (int yy = y; yy < y + h; yy++) {
        uint32_t* row = (uint32_t*)(fb_mem + yy * finfo.line_length);
        for (int xx = x; xx < x + w; xx++) {
            row[xx] = color;
        }
    }
}

// simple block text: draw a "big" label by filling rectangles per char (not font)
static void fb_draw_label(int x, int y, const std::string &label, uint32_t color) {
    if (!fb_mem) return;
    // draw each char as a 10x16 block (very simple)
    int cx = x;
    for (char ch : label) {
        for (int yy = y; yy < y + 16; yy++) {
            uint32_t* row = (uint32_t*)(fb_mem + yy * finfo.line_length);
            for (int xx = cx; xx < cx + 10; xx++) {
                row[xx] = color;
            }
        }
        cx += 12;
    }
}

void show_lithium_warning(int severity) {
    // severity color: green(0), yellow(1), red(2)
    uint32_t color;
    switch (severity) {
        case 0: color = 0xFF00FF00; break; // green
        case 1: color = 0xFFFFFF00; break; // yellow
        default: color = 0xFFFF0000; break; // red
    }

    if (fb_mem) {
        // clear small area top-left
        fb_clear_rect(0, 0, 400, 100, 0xFF000000);
        // draw a colored rectangle at top-left background
        fb_clear_rect(0, 0, 400, 40, color);
        // draw label
        fb_draw_label(8, 8, "LITHIUM DETECTED", 0xFFFFFFFF);
    } else {
        // console fallback
        std::cout << "\n========================\n";
        std::cout << "LITHIUM DETECTED  (severity=" << severity << ")\n";
        std::cout << "========================\n";
    }
}

void show_no_command_and_menu() {
    if (fb_mem) {
        // draw "No command" below
        fb_clear_rect(0, 50, 400, 80, 0xFF000000);
        fb_draw_label(8, 60, "NO COMMAND", 0xFFFFFFFF);
    } else {
        std::cout << "NO COMMAND\n";
    }

    // show menu options on console
    std::cout << "\nAções seguras disponíveis:\n";
    std::cout << "1) Shutdown now (desligar)\n";
    std::cout << "2) Safe Mode (bloquear rádios temporariamente)\n";
    std::cout << "3) Show disposal instructions\n";
    std::cout << "4) Dismiss\n";
    std::cout << "Escolha uma opção (1-4): ";
}

void cleanup_ui() {
    if (fb_mem) {
        munmap(fb_mem, screensize);
        fb_mem = nullptr;
    }
    if (fb_fd >= 0) {
        close(fb_fd);
        fb_fd = -1;
    }
}

} // namespace LITH_UI
