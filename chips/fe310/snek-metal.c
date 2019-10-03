/*
 * Copyright © 2019 Keith Packard <keithp@keithp.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <metal/tty.h>
#include <snek.h>
#include "snek-io.h"

static int
snek_metal_putc(char c, FILE *f)
{
	(void) f;
	return metal_tty_putc(c);
}

int
snek_metal_getc(FILE *f)
{
	(void) f;
	int c;
	for (;;) {
		if (metal_tty_getc(&c) != 0)
			return EOF;
		if (c != -1)
			return c;
	}
}

static int
snek_metal_flush(FILE *f)
{
	(void) f;
	return 0;
}

static FILE __stdio = FDEV_SETUP_STREAM(snek_metal_putc, snek_io_getc, snek_metal_flush, _FDEV_SETUP_RW);

FILE *const __iob[3] = { &__stdio, &__stdio, &__stdio };

int main(void)
{
	snek_init();
	printf("Welcome to snek " SNEK_VERSION "\n");
	fflush(stdout);
	snek_interactive = true;
	for (;;)
		snek_parse();
}
