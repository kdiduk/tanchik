#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <z80.h>
#include "player.h"

#define INIT_FLAGS ( \
                SP1_IFLAG_MAKE_ROTTBL \
                | SP1_IFLAG_OVERWRITE_TILES \
                | SP1_IFLAG_OVERWRITE_DFILE)

extern unsigned char grass_a[];
extern unsigned char grass_b[];
extern unsigned char grass_c[];
extern unsigned char grass_d[];

struct sp1_Rect full_screen = { 0, 0, 32, 24 };

int i;
int j;


int main()
{
        zx_border(INK_BLACK);

        sp1_Initialize(INIT_FLAGS, INK_BLACK | PAPER_GREEN, ' ');
        sp1_Invalidate(&full_screen);

        player_init();

        sp1_TileEntry('a', grass_a);
        sp1_TileEntry('b', grass_b);
        sp1_TileEntry('c', grass_c);
        sp1_TileEntry('d', grass_d);

        for (i = 0; i < 32; i++) {
                for (j = 0; j < 24; j++) {
                        sp1_PrintAt(j, i, INK_YELLOW | PAPER_GREEN,
                                        ('a' + i%2) + (j%2<<1));
                }
        }

        while (1) {
                player_update(&full_screen);
                sp1_UpdateNow();
                z80_delay_ms(50);
        }
}

