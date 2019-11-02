/*
 * MIT License
 *
 * Copyright (c) 2019 Kirill Diduk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <arch/zx.h>
#include <arch/zx/sp1.h>
#include <input.h>
#include "player.h"

#define SPRITE_HEIGHT (4)
#define MAX_POSX ((32-SPRITE_HEIGHT+1) * 8)
#define MAX_POSY ((24-SPRITE_HEIGHT+1) * 8)

enum Direction {
        DIRECTION_UP,
        DIRECTION_DOWN,
        DIRECTION_RIGHT,
        DIRECTION_LEFT
};

extern unsigned char player_sprite_f1[];
extern unsigned char player_sprite_f2[];
extern unsigned char player_sprite_f3[];
extern unsigned char player_sprite_f4[];

extern unsigned char player_sprite1[];
extern unsigned char player_sprite2[];
extern unsigned char player_sprite3[];

static const unsigned char* frames[] = { player_sprite_f1,
                                         player_sprite_f2,
                                         player_sprite_f3,
                                         player_sprite_f4 };

static struct sp1_ss *sprite;
static enum Direction direction;
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
                               0,
                               0);
        sp1_AddColSpr(sprite,
                      SP1_DRAW_LOAD1,
                      SP1_TYPE_1BYTE,
                      player_sprite2-player_sprite1,
                      0);
        sp1_AddColSpr(sprite,
                      SP1_DRAW_LOAD1,
                      SP1_TYPE_1BYTE,
                      player_sprite3-player_sprite1,
                      0);
        sp1_AddColSpr(sprite,
                      SP1_DRAW_LOAD1RB,
                      SP1_TYPE_1BYTE,
                      0,
                      0);

        sp1_IterateSprChar(sprite, init_sprite_color);

        posx = 7 * 8;
        posy = MAX_POSY;
        direction = DIRECTION_UP;
}

void player_update(struct sp1_Rect* rect)
{
        if (posy > 0 && in_key_pressed(IN_KEY_SCANCODE_q)) {
                posy--;
                direction = DIRECTION_UP;
        } else if (posy < MAX_POSY && in_key_pressed(IN_KEY_SCANCODE_a)) {
                posy++;
                direction = DIRECTION_DOWN;
        } else if (posx > 0 && in_key_pressed(IN_KEY_SCANCODE_o)) {
                posx--;
                direction = DIRECTION_LEFT;
        } else if (posx < MAX_POSX && in_key_pressed(IN_KEY_SCANCODE_p)) {
                posx++;
                direction = DIRECTION_RIGHT;
        }

        sp1_MoveSprPix(sprite, rect, frames[direction], posx, posy);
}

/* EOF */
