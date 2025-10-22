#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include "menu_mode_ui.h"

struct FrameBuffer {
    int fd;
    unsigned int width, height, bpp;
    unsigned long screensize;
    unsigned char* fbmem;
    fb_fix_screeninfo fix;
    fb_var_screeninfo var;
} fb;

int framebuffer_detectado(void) {
    int fd = open("/dev/fb0", O_RDWR);
    if (fd < 0) return 0;
    close(fd);
    return 1;
}

int input_fd = -1;

static void fb_init() {
    fb.fd = open("/dev/fb0", O_RDWR);
    if (fb.fd < 0) {
        perror("[ELAT] Erro ao abrir framebuffer");
        exit(1);
    }

    ioctl(fb.fd, FBIOGET_FSCREENINFO, &fb.fix);
    ioctl(fb.fd, FBIOGET_VSCREENINFO, &fb.var);

    fb.width = fb.var.xres;
    fb.height = fb.var.yres;
    fb.bpp = fb.var.bits_per_pixel;
    fb.screensize = fb.fix.line_length * fb.height;

    fb.fbmem = (unsigned char*)mmap(0, fb.screensize,
                                   PROT_READ | PROT_WRITE,
                                   MAP_SHARED, fb.fd, 0);
    if ((intptr_t)fb.fbmem == -1) {
        perror("[ELAT] Erro ao mapear framebuffer");
        exit(2);
    }
}

static void fb_clear(unsigned int color) {
    unsigned int* ptr = (unsigned int*)fb.fbmem;
    for (unsigned long i = 0; i < fb.screensize / 4; i++)
        ptr[i] = color;
}

static void fb_draw_rect(int x, int y, int w, int h, unsigned int color) {
    unsigned int* ptr = (unsigned int*)fb.fbmem;
    for (int yy = y; yy < y + h; yy++) {
        unsigned int* row = ptr + yy * fb.width + x;
        for (int xx = 0; xx < w; xx++)
            row[xx] = color;
    }
}

static void fb_draw_text(int x, int y, const char* text, unsigned int color) {
    for (int i = 0; text[i]; i++) {
        fb_draw_rect(x + i * 18, y, 14, 22, color);
    }
}

static void draw_menu_ui(int selected) {
    fb_clear(0xFF202020); // fundo
    fb_draw_text(60, 40, "⚡  ELAT MENU MODE ⚡", 0xFFFFFFFF);

    unsigned int normal = 0xFFAAAAAA;
    unsigned int highlight = 0xFF00FFFF;

    fb_draw_text(100, 150, "⟳  Reboot", selected == 0 ? highlight : normal);
    fb_draw_text(100, 210, "⏻  Power Off", selected == 1 ? highlight : normal);
    fb_draw_text(100, 270, "↻  Reset SYS", selected == 2 ? highlight : normal);
}

static int find_input_device() {
    DIR* dir = opendir("/dev/input");
    if (!dir) return -1;

    struct dirent* ent;
    while ((ent = readdir(dir)) != nullptr) {
        if (strncmp(ent->d_name, "event", 5) == 0) {
            char path[128];
            snprintf(path, sizeof(path), "/dev/input/%s", ent->d_name);
            int fd = open(path, O_RDONLY | O_NONBLOCK);
            if (fd >= 0) {
                closedir(dir);
                return fd;
            }
        }
    }
    closedir(dir);
    return -1;
}

static void execute_action(int selected) {
    switch (selected) {
        case 0: system("reboot"); break;
        case 1: system("poweroff"); break;
        case 2: system("reboot --sysreset"); break;
    }
}

extern "C" void start_menu_ui(void) {
    fb_init();
    fb_clear(0xFF000000);

    printf("\n[ELAT] Iniciando modo gráfico do menu...\n");
    printf("███████╗██╗      █████╗ ████████╗\n");
    printf("██╔════╝██║     ██╔══██╗╚══██╔══╝\n");
    printf("█████╗  ██║     ███████║   ██║   \n");
    printf("██╔══╝  ██║     ██╔══██║   ██║   \n");
    printf("██║     ███████╗██║  ██║   ██║   \n");
    printf("╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   \n\n");

    draw_menu_ui(0);

    input_fd = find_input_device();
    if (input_fd < 0)
        printf("[ELAT] Nenhum input encontrado. Interface ficará estática.\n");

    int selected = 0;
    bool running = true;

    while (running) {
        struct input_event ev;
        ssize_t n = read(input_fd, &ev, sizeof(ev));

        if (n == sizeof(ev) && ev.type == EV_KEY && ev.value == 1) {
            switch (ev.code) {
                case KEY_UP:
                    selected = (selected - 1 + 3) % 3;
                    draw_menu_ui(selected);
                    break;
                case KEY_DOWN:
                    selected = (selected + 1) % 3;
                    draw_menu_ui(selected);
                    break;
                case KEY_ENTER:
                case KEY_SPACE:
                    execute_action(selected);
                    running = false;
                    break;
                default:
                    break;
            }
        }
        usleep(50000);
    }

    munmap(fb.fbmem, fb.screensize);
    close(fb.fd);
    if (input_fd >= 0) close(input_fd);
}
