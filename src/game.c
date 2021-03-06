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
#include <intrinsic.h>

#include "interrupt.h"
#include "level.h"
#include "game.h"
#include "player.h"

#define INIT_FLAGS (SP1_IFLAG_MAKE_ROTTBL \
                | SP1_IFLAG_OVERWRITE_TILES \
                | SP1_IFLAG_OVERWRITE_DFILE)

struct sp1_Rect full_screen = { 0, 0, 32, 24 };

void game_init(void)
{
        interrupt_init();
        zx_border(INK_BLACK);

        sp1_Initialize(INIT_FLAGS, INK_BLACK | PAPER_GREEN, ' ');
        sp1_Invalidate(&full_screen);

        player_init();
}

void game_run(void)
{
        level_load(&full_screen);

        while (1) {
                player_update();
                player_render(&full_screen);
                intrinsic_halt();
                sp1_UpdateNow();
                intrinsic_halt();
        }
}

void game_shutdown(void)
{
}

