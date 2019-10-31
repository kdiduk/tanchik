#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>
#include "player.h"

#define SPRITE_HEIGHT (4)

extern unsigned char player_sprite1[];
extern unsigned char player_sprite2[];
extern unsigned char player_sprite3[];

static struct sp1_ss *sprite;
static int posx;
static int posy;

static void init_sprite_color(unsigned int count, struct sp1_cs *cs)
{
        (void)count; /* Suppress compiler warning about unused parameter */

        cs->attr_mask = SP1_AMASK_INK;
        cs->attr = INK_BLACK | PAPER_GREEN;
}


void player_init(void)
{
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

        posx = 7 * 8;
        posy = 23 * 8;
}

void player_update(struct sp1_Rect* rect)
{
        if (posy > 0 && in_key_pressed(IN_KEY_SCANCODE_q))
                posy--;
        else if (posy < 23 * 8 && in_key_pressed(IN_KEY_SCANCODE_a))
                posy++;
        else if (posx > 0 && in_key_pressed(IN_KEY_SCANCODE_o))
                posx--;
        else if (posx < 31 * 8 && in_key_pressed(IN_KEY_SCANCODE_p))
                posx++;
        else
                return;

        sp1_MoveSprAbs(sprite, rect, 0, posy/8, posx/8, posy%8, posx%8);
}

/* EOF */
