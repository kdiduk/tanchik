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

#include "tileset.h"
#include <arch/zx/sp1.h>

static const unsigned char tiles[] = {
        0x95, 0xAA, 0x95, 0xAA, 0x95, 0xAA, 0x95, 0xAA, /* y:0, x:0 (128) */
        0x56, 0xaa, 0x56, 0xab, 0x57, 0xaa, 0x56, 0xaa, /* y:0, x:1 (129) */
        0x6A, 0x55, 0x6A, 0xD5, 0xEA, 0x55, 0x6A, 0x55, /* y:0, x:2 (130) */
        0xA9, 0x55, 0xA9, 0x55, 0xA9, 0x55, 0xA9, 0x55, /* y:0, x:3 (131) */
        0x18, 0x44, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, /* y:0, x:4 (132) */
        0x56, 0xab, 0xAA, 0xaa, 0xAA, 0xaa, 0xAA, 0xaa, /* y:2, x:3 (133) */
        0x00, 0xff, 0xAA, 0xaa, 0xAA, 0xaa, 0xAA, 0xaa, /* y:2, x:4 (134) */
        0x95, 0xAA, 0x95, 0xd5, 0xea, 0xAA, 0x7f, 0x18, /* y:3, x:2 (135) */
        0xAA, 0xaa, 0xAA, 0xaa, 0xAA, 0xaa, 0x00, 0xe7, /* y:3, x:3 (136) */
        0x18, 0x7f, 0x95, 0xd5, 0xea, 0xAA, 0x95, 0xAA, /* y:4, x:2 (137) */
        0x18, 0xff, 0xaa, 0xAA, 0xaa, 0xAA, 0xaa, 0xAA, /* y:4, x:3 (138) */
        0xAA, 0xaa, 0xAA, 0xaa, 0xAA, 0xaa, 0x57, 0xaa, /* y:5, x:3 (139) */
        0xAA, 0xaa, 0xAA, 0xaa, 0xAA, 0xaa, 0xff, 0x00, /* y:5, x:4 (140) */
};

void tileset_init(void)
{
        unsigned char i;
        const unsigned char* pt = tiles;

        for (i = 0; i < TILES_LEN; i++, pt += 8) {
                sp1_TileEntry(TILES_BASE + i, pt);
        }
}

/* EOF */

