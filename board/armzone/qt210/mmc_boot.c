#include <common.h>

extern void movi_bl2_copy(void);

void board_init_f(unsigned long bootflag)
{
        __attribute__((noreturn)) void (*uboot)(void);
        movi_bl2_copy();

        /* Jump to U-Boot image */
        uboot = (void *)CONFIG_SYS_TEXT_BASE;
        (*uboot)();
        /* Never returns Here */
}

/* Place Holders */
void board_init_r(gd_t *id, ulong dest_addr)
{
        /* Function attribute is no-return */
        /* This Function never executes */
        while (1)
                ;
}

void save_boot_params(u32 r0, u32 r1, u32 r2, u32 r3) {}

