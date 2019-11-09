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
#include "level.h"

#define TILE_SHIFT(tile, row, col) \
                ((tile) + (row) % 2) + ((col) % 2 << 1)

void level_load(void)
{
        int row;
        int col;

        for (row = 0; row < 32; row++) {
                for (col = 0; col < 24; col++) {
                        sp1_PrintAt(col,
                                    row,
                                    INK_YELLOW | PAPER_GREEN,
                                    TILE_SHIFT('a', row, col));
                }
        }

        for (row = 2; row < 6; row++) {
                for (col = 0; col < 24; col++) {
                        sp1_PrintAt(col,
                                    row,
                                    INK_BLACK | PAPER_WHITE,
                                    'w' + row - 2);
                }
        }
}

/* eof */
