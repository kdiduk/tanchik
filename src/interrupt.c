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
#include <im2.h>
#include <intrinsic.h>
#include <string.h>
#include <z80.h>
#include "interrupt.h"

#define TABLE_HIGH_BYTE        ((unsigned int)0xD0)
#define JUMP_POINT_HIGH_BYTE   ((unsigned int)0xD1)

#define UI_256          ((unsigned int)256)
#define TABLE_ADDR      ((void*)(TABLE_HIGH_BYTE * UI_256))
#define JUMP_POINT      ((unsigned char*)( \
                (unsigned int)(JUMP_POINT_HIGH_BYTE * UI_256) \
                + JUMP_POINT_HIGH_BYTE))

IM2_DEFINE_ISR(isr)
{
}

void interrupt_init(void)
{
        memset(TABLE_ADDR, JUMP_POINT_HIGH_BYTE, 257);
        z80_bpoke(JUMP_POINT, 195);
        z80_wpoke(JUMP_POINT+1, (unsigned int)isr);
        im2_init(TABLE_ADDR);
        intrinsic_ei();
}

/* EOF */
