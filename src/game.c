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
#include <z80.h>

#include "level.h"
#include "game.h"
#include "player.h"

#define INIT_FLAGS (SP1_IFLAG_MAKE_ROTTBL \
                | SP1_IFLAG_OVERWRITE_TILES \
                | SP1_IFLAG_OVERWRITE_DFILE)

extern unsigned char grass_a[];
extern unsigned char grass_b[];
extern unsigned char grass_c[];
extern unsigned char grass_d[];

struct sp1_Rect full_screen = { 0, 0, 32, 24 };

void game_init(void)
{
        zx_border(INK_BLACK);

        sp1_Initialize(INIT_FLAGS, INK_BLACK | PAPER_GREEN, ' ');
        sp1_Invalidate(&full_screen);

        sp1_TileEntry('a', grass_a);
        sp1_TileEntry('b', grass_b);
        sp1_TileEntry('c', grass_c);
        sp1_TileEntry('d', grass_d);

        player_init();
}

void game_run(void)
{
        level_load();

        while (1) {
                player_update(&full_screen);
                sp1_UpdateNow();
                z80_delay_ms(50);
        }
}

void game_shutdown(void)
{
}

