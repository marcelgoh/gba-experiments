#include "tonc.h"

inline int modulo(int a, int b) {
  const int result = a % b;
  return result >= 0 ? result : result + b;
}

int main() {
    signed int dot_x = 120;
    signed int dot_y = 80;
    int start_menu = 0;
    COLOR clr = 0xB38F;

    REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;


    while (1) {
        vid_vsync();
        key_poll();
        dot_x += key_tri_horz();
        dot_y += key_tri_vert();
        if (key_hit(KEY_START)) {
            if (start_menu) {
                m3_fill(CLR_BLACK);
                start_menu = 0;
            } else {
                m3_fill(CLR_BLUE);
                start_menu = 1;
            }
            continue;
        }
        if (key_hit(KEY_A)) {
            clr = (clr << 1) | (clr >> 15);
        } else if (key_hit(KEY_B)) {
            clr = (clr >> 1) | (clr << 15);
        }
        if (!start_menu) m3_plot(modulo(dot_x, SCREEN_WIDTH),
                modulo(dot_y, SCREEN_HEIGHT), clr);
    }

    return 0;
}
