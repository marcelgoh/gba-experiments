#include "tonc.h"
#include "map.h"
#include "walker.h"
#include "walker_left.h"

#define TILE_WIDTH 8
#define TILE_HEIGHT 8
#define INIT_TILE_X 12
#define INIT_TILE_Y 4
#define TURN_DELAY 3 /* measured in number of frames */

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

    // walker_left is shifted one over
    memcpy32(&tile_mem[4][16], walker_leftTiles, walker_leftTilesLen>>2);
    memcpy32(pal_obj_mem, walker_leftPal, walker_leftPalLen>>2);

    // (2) Initialize all sprites
    oam_init(obj_buffer, 128);

    obj_set_attr(walker,
            ATTR0_SQUARE,				// Square, regular sprite
            ATTR1_SIZE_16,					// 8x8p,
            ATTR2_PALBANK(palette_bank) | tile_id);		// palbank 0, tile 0

}

enum direction {LEFT, RIGHT, UP, DOWN, NEUTRAL};
enum direction heading = NEUTRAL;  /* direction walker is going */
enum direction key_heading = NEUTRAL;  /* direction player is holding */

int turn_timer = 0;

void update_key_heading() {
    /* no need to update key_heading if input state doesn't change */
    if (key_curr_state() != key_prev_state()) {
        if ((key_released(KEY_LEFT) && key_heading == LEFT) ||
            (key_released(KEY_RIGHT) && key_heading == RIGHT) ||
            (key_released(KEY_UP) && key_heading == UP) ||
            (key_released(KEY_DOWN) && key_heading == DOWN)) {
            key_heading = NEUTRAL;
        }

        if (key_is_down(KEY_LEFT)) key_heading = LEFT;
        if (key_is_down(KEY_RIGHT)) key_heading = RIGHT;
        if (key_is_down(KEY_UP)) key_heading = UP;
        if (key_is_down(KEY_DOWN)) key_heading = DOWN;

    }
    return;
}

int tile_x = INIT_TILE_X;
int tile_y = INIT_TILE_Y;
int x = INIT_TILE_X * TILE_WIDTH;
int y = INIT_TILE_Y * TILE_HEIGHT;
bool can_move = true;

void update_position() {
    int dest_x = tile_x * TILE_WIDTH;
    int dest_y = tile_y * TILE_HEIGHT;
    if (x == dest_x && y == dest_y) {
        /* reached destination, so can move again */
        can_move = true;
        return;
    }
    if (x != dest_x) {
        /* if haven't reached dest_x, move horizontally */
        x += (dest_x > x) ? 1 : -1;
    } else {
        /* if haven't reached dest_y, move vertically */
        y += (dest_y > y) ? 1 : -1;
    }

    return;
}

int main() {
    bg_init();
    sprite_init();
    REG_DISPCNT= DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    irq_init(NULL);
    irq_add(II_VBLANK, NULL);
    while(1) {
        VBlankIntrWait();
        key_poll();
        update_key_heading();
        if (can_move && key_heading != NEUTRAL) {
            can_move = false;
            if (key_heading != heading) turn_timer = TURN_DELAY;
            heading = key_heading;
            switch (heading) {
                case LEFT:
                    tile_id = 16;  /* switch to walker_left sprite */
                    --tile_x;
                    break;
                case RIGHT:
                    tile_id = 0;
                    ++tile_x;
                    break;
                case UP:
                    --tile_y;
                    break;
                case DOWN:
                    ++tile_y;
                    break;
                case NEUTRAL:
                   /* shouldn't happen */
                    break;
            }
        }
        if (turn_timer == 0) {
            update_position();
        } else {
            --turn_timer;
        }
        walker->attr2=ATTR2_BUILD(tile_id, palette_bank, 0);
        obj_set_pos(walker, x, y);

        oam_copy(oam_mem, obj_buffer, 1);
    }

    return 0;
}
