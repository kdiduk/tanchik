#pragma output REGISTER_SP = 0xD000

#include <arch/zx.h>
#include <arch/zx/sp1.h>

#define INIT_FLAGS ( \
    SP1_IFLAG_MAKE_ROTTBL \
    | SP1_IFLAG_OVERWRITE_TILES \
    | SP1_IFLAG_OVERWRITE_DFILE)

#define SPRITE_HEIGHT (4)

extern unsigned char player_sprite1[];
extern unsigned char player_sprite2[];
extern unsigned char player_sprite3[];

struct sp1_Rect full_screen = {0, 0, 32, 24};

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
    sp1_AddColSpr(sprite, SP1_DRAW_LOAD1, SP1_TYPE_1BYTE, (int)player_sprite2, 0);
    sp1_AddColSpr(sprite, SP1_DRAW_LOAD1, SP1_TYPE_1BYTE, (int)player_sprite3, 0);
    sp1_AddColSpr(sprite, SP1_DRAW_LOAD1RB, SP1_TYPE_1BYTE, 0, 0);

    sp1_MoveSprAbs(sprite, &full_screen, 0, 4, 5, 0, 0);

    sp1_UpdateNow();

    while(1);
}

