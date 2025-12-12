#include "tonc.h"

int main() {
    int dot_x = 120;
    int dot_y = 80;
    int dx = 1;
    int dy = 1;

    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;


    while (1) {
        vid_vsync();
        key_poll();
        if (key_is_down(KEY_RIGHT)) dot_x += dx;
        if (key_is_down(KEY_LEFT)) dot_x -= dx;
        if (key_is_down(KEY_UP)) dot_y -= dy;
        if (key_is_down(KEY_DOWN)) dot_y += dy;

        m3_plot( dot_x % SCREEN_WIDTH, dot_y % SCREEN_HEIGHT, CLR_RED );
    }

    return 0;
}
