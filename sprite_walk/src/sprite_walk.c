#include "tonc.h"
#include "map.h"
#include "walker.h"

OBJ_ATTR obj_buffer[128];
u32 tile_id = 0;
u32 palette_bank = 0;
OBJ_ATTR *walker= &obj_buffer[0];

void bg_init() {
    // Load palette
    memcpy32(pal_bg_mem, mapPal, mapPalLen>>2);
    // Load tiles into CBB 0
    memcpy32(&tile_mem[0][0], mapTiles, mapTilesLen>>2);
    // Load map into SBB 31
    memcpy32(&se_mem[31][0], mapMap, mapMapLen>>2);

    // set up BG0 for a 4bpp 32x32t map, using
    //   using charblock 0 and screenblock 31
    REG_BG0CNT= BG_CBB(0) | BG_SBB(31) | BG_4BPP | BG_REG_32x32;
}

void sprite_init() {
    // (1) Places the tiles of the walker
    //   into LOW obj memory (CBB 4)
    memcpy32(&tile_mem[4][0], walkerTiles, walkerTilesLen>>2);
    memcpy32(pal_obj_mem, walkerPal, walkerPalLen>>2);

    // (2) Initialize all sprites
    oam_init(obj_buffer, 128);

    obj_set_attr(walker,
            ATTR0_SQUARE,				// Square, regular sprite
            ATTR1_SIZE_32,					// 8x8p,
            ATTR2_PALBANK(palette_bank) | tile_id);		// palbank 0, tile 0

}

int main() {
    bg_init();
    sprite_init();
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    int x = 96;
    int y = 32;
    while(1) {
        vid_vsync();
        key_poll();

        // -1 is a full mask
        x += 8*bit_tribool(key_hit(-1), KI_RIGHT, KI_LEFT);
        y += 8*bit_tribool(key_hit(-1), KI_DOWN, KI_UP);
        //x += 8*key_tri_horz();
        //y += 8*key_tri_vert();

        walker->attr2=ATTR2_BUILD(tile_id, palette_bank, 0);
        obj_set_pos(walker, x, y);

        oam_copy(oam_mem, obj_buffer, 1);
    }

    return 0;
}
