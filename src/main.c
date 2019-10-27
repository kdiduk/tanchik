#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <z80.h>

#define INIT_FLAGS ( \
    SP1_IFLAG_MAKE_ROTTBL \
    | SP1_IFLAG_OVERWRITE_TILES \
    | SP1_IFLAG_OVERWRITE_DFILE)

#define SPRITE_HEIGHT (4)

extern unsigned char player_sprite1[];
extern unsigned char player_sprite2[];
extern unsigned char player_sprite3[];

extern unsigned char grass_a[];
extern unsigned char grass_b[];
extern unsigned char grass_c[];
extern unsigned char grass_d[];

struct sp1_Rect full_screen = {0, 0, 32, 24};

int i;
int j;

static void init_sprite_color(unsigned int count, struct sp1_cs *cs)
{
    (void)count;    /* Suppress compiler warning about unused parameter */

    cs->attr_mask = SP1_AMASK_INK;
    cs->attr      = INK_BLACK | PAPER_GREEN;
  
}


int main()
{
    struct sp1_ss *sprite;

    zx_border(INK_BLACK);

    sp1_Initialize(INIT_FLAGS, INK_BLACK | PAPER_GREEN, ' ');
    sp1_Invalidate(&full_screen);

    sprite = sp1_CreateSpr(SP1_DRAW_LOAD1LB,
            SP1_TYPE_1BYTE,
            SPRITE_HEIGHT,
            (int)player_sprite1,
            0);
    sp1_AddColSpr(sprite,
            SP1_DRAW_LOAD1,
            SP1_TYPE_1BYTE,
            (int)player_sprite2,
            0);
    sp1_AddColSpr(sprite,
            SP1_DRAW_LOAD1,
            SP1_TYPE_1BYTE,
            (int)player_sprite3,
            0);
    sp1_AddColSpr(sprite,
            SP1_DRAW_LOAD1RB,
            SP1_TYPE_1BYTE,
            0,
            0);

    sp1_IterateSprChar(sprite, init_sprite_color);

    sp1_TileEntry('a', grass_a);
    sp1_TileEntry('b', grass_b);
    sp1_TileEntry('c', grass_c);
    sp1_TileEntry('d', grass_d);

    for (i = 0; i < 32; i++) {
        for (j = 0; j < 24; j++) {
            sp1_PrintAt(
                    j,
                    i,
                    INK_YELLOW | PAPER_GREEN,
                    ('a' + i%2) + (j%2<<1));
       }
    }

    for (j = 23; j != 0; j--) {
        for (i = 8; i != 0; i--) {
            sp1_MoveSprAbs(sprite, &full_screen, 0, j, 7, i-1, 3);
            sp1_UpdateNow();
            z80_delay_ms(50);
        }
    }


    while(1);
}

