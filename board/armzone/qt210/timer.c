/*
 * (C) Copyright 2003
 * Texas Instruments <www.ti.com>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Alex Zuepke <azu@sysgo.de>
 *
 * (C) Copyright 2002-2004
 * Gary Jennejohn, DENX Software Engineering, <gj@denx.de>
 *
 * (C) Copyright 2004
 * Philippe Robin, ARM Ltd. <philippe.robin@arm.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <asm/proc-armv/ptrace.h>
#include <s5pc110.h>

int timer_load_val = 0;

/* macro to read the 16 bit timer */
static inline ulong READ_TIMER(void)
{
	S5PC11X_TIMERS *const timers = S5PC11X_GetBase_TIMERS();

	return (timers->TCNTO4 & 0xffffffff);
}

static ulong timestamp;
static ulong lastdec;

int arch_interrupt_init(void)
{

	S5PC11X_TIMERS *const timers = S5PC11X_GetBase_TIMERS();

	/* use PWM Timer 4 because it has no output */
	/* prescaler for Timer 4 is 16 */
	timers->TCFG0 = 0x0f00;
	if (timer_load_val == 0) {
		/*
		 * for 10 ms clock period @ PCLK with 4 bit divider = 1/2
		 * (default) and prescaler = 16. Should be 10390
		 * @33.25MHz and  @ 66 MHz
		 */
		timer_load_val = get_PCLK() / (16 * 100);
	}

	/* load value for 10 ms timeout */
	lastdec = timers->TCNTB4 = timer_load_val;
	/* auto load, manual update of Timer 4 */
	timers->TCON = (timers->TCON & ~0x00700000) | TCON_4_AUTO | TCON_4_UPDATE;
	/* auto load, start Timer 4 */
	timers->TCON = (timers->TCON & ~0x00700000) | TCON_4_AUTO | COUNT_4_ON;
	timestamp = 0;


	return (0);
}

/*
 * timer without interrupts
 */

void reset_timer(void)
{
	reset_timer_masked();
}

void set_timer(ulong t)
{
	timestamp = t;
}

void udelay_masked(unsigned long usec)
{
	ulong tmo;
	ulong endtime;
	signed long diff;

	if (usec >= 1000) {
		tmo = usec / 1000;
		tmo *= (timer_load_val * 100);
		tmo /= 1000;
	}
	else {
		tmo = usec * (timer_load_val * 100);
		tmo /= (1000 * 1000);
	}

	endtime = get_timer_masked() + tmo;

	do {
		ulong now = get_timer_masked();
		diff = endtime - now;
	} while (diff >= 0);
}

