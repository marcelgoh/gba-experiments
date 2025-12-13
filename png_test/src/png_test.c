#include "tonc.h"
#include "ahoy.h"
#include "string.h"

int main()
{
    // Load palette
    memcpy(pal_bg_mem, ahoyPal, ahoyPalLen);
    // Load tiles into CBB 0
    memcpy(&tile_mem[0][0], ahoyTiles, ahoyTilesLen);
    // Load map into SBB 30
    memcpy(&se_mem[30][0], ahoyMap, ahoyMapLen);

    // set up BG0 for a 4bpp 64x32t map, using
    //   using charblock 0 and screenblock 31
    REG_BG0CNT= BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_64x64;
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0;

    // Scroll around some
    int x= 192, y= 64;
    while(1)
    {
        vid_vsync();
        key_poll();

        x += key_tri_horz();
        y += key_tri_vert();

        REG_BG0HOFS= x;
        REG_BG0VOFS= y;
    }

    return 0;
}
