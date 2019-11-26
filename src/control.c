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

#include <input.h>
#include "control.h"

bool control_pressed(enum control c)
{
        switch (c) {
        case CONTROL_UP:
                return in_key_pressed(IN_KEY_SCANCODE_q);
        case CONTROL_DOWN:
                return in_key_pressed(IN_KEY_SCANCODE_a);
        case CONTROL_LEFT:
                return in_key_pressed(IN_KEY_SCANCODE_o);
        case CONTROL_RIGHT:
                return in_key_pressed(IN_KEY_SCANCODE_p);
        case CONTROL_FIRE:
                return in_key_pressed(IN_KEY_SCANCODE_SPACE);
        }

        return false;
}

