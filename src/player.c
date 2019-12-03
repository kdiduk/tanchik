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
#include "control.h"
#include "direction.h"
#include "player.h"

#define SPRITE_HEIGHT (4)
#define MAX_POSX ((32-SPRITE_HEIGHT+1) * 8)
#define MAX_POSY ((24-SPRITE_HEIGHT+1) * 8)


extern unsigned char player_sprite_f1[];
extern unsigned char player_sprite_f2[];
extern unsigned char player_sprite_f3[];
extern unsigned char player_sprite_f4[];

extern unsigned char player_sprite1[];
extern unsigned char player_sprite2[];
extern unsigned char player_sprite3[];

static const unsigned char* frames[] = { player_sprite_f1,
                                         player_sprite_f2,
                                         player_sprite_f4,
                                         player_sprite_f3 };

static struct sp1_ss *sprite;
static enum direction direction;
static int posx;
static int posy;

void player_init(void)
{
        sprite = sp1_CreateSpr(SP1_DRAW_MASK2LB,
                               SP1_TYPE_2BYTE,
                               SPRITE_HEIGHT,
                               0,
                               0);
        sp1_AddColSpr(sprite,
                      SP1_DRAW_MASK2,
                      SP1_TYPE_2BYTE,
                      player_sprite2-player_sprite1,
                      0);
        sp1_AddColSpr(sprite,
                      SP1_DRAW_MASK2,
                      SP1_TYPE_2BYTE,
                      player_sprite3-player_sprite1,
                      0);
        sp1_AddColSpr(sprite,
                      SP1_DRAW_MASK2RB,
                      SP1_TYPE_2BYTE,
                      0,
                      0);

        posx = 4;
        posy = MAX_POSY - 4;
        direction = DIR_UP;
}

void player_update(void)
{
        if (posy > 0 && control_pressed(CONTROL_UP)) {
                player_move(DIR_UP);
        } else if (posy < MAX_POSY && control_pressed(CONTROL_DOWN)) {
                player_move(DIR_DOWN);
        } else if (posx > 0 && control_pressed(CONTROL_LEFT)) {
                player_move(DIR_LEFT);
        } else if (posx < MAX_POSX && control_pressed(CONTROL_RIGHT)) {
                player_move(DIR_RIGHT);
        }
}

void player_render(struct sp1_Rect* rect)
{
        sp1_MoveSprPix(sprite, rect, frames[direction], posx, posy);
}

void player_move(enum direction d)
{
        direction = d;
        switch (d) {
        case DIR_UP:
                posy--;
                break;
        case DIR_DOWN:
                posy++;
                break;
        case DIR_LEFT:
                posx--;
                break;
        case DIR_RIGHT:
                posx++;
                break;
        }
}

/* EOF */
