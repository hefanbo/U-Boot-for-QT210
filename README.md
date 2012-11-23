U-Boot for QT210
================

QT210 is a Cortex A8 dev-board featured Samsung S5PV210.  
This is U-Boot for QT210 based on [Linaro U-Boot][1] 12.09 ([Das U-Boot][2] version 2012.07)  
Ported from [opencsbc-u-boot-mini210_linaro-2011.10-stable][3]

By HE Fanbo, Nov. 2012

Features
--------
* Boot from SD card

Todo
----
* Make fastboot fully functional
* PWM output for LCD backlight is not correct. see board/armzone/qt210/qt210.c - pwm_pre_init()
* LAN adapter
* (Should we?) try MMU
* Tidy the codes
  - Fastboot
  - (Should we?) merge `include/s5pc11x.h` and `include/s5pc110.h` to `arch/arm/include/asm/arch-s5pc1xx/cpu.h`
  - ...

Toolchain
---------
Linaro toolchain (https://wiki.linaro.org/WorkingGroups/ToolChain)  
Linaro toolchain binaries (https://launchpad.net/linaro-toolchain-binaries)

Install the Linaro toolchain on Ubuntu:

    # apt-get install gcc-arm-linux-gnueabi

or for hard-float toolchain:

    # apt-get install gcc-arm-linux-gnueabihf

Build
-----

    $ make CROSS_COMPILE=arm-linux-gnueabihf- O=out/qt210 qt210

Burn
----
Assuming **/dev/sdb** is the device name corresponding to the SD card.

    # dd iflag=dsync oflag=dsync if=out/qt210/spl/qt210-spl.bin of=/dev/sdb seek=1
    # dd iflag=dsync oflag=dsync if=out/qt210/u-boot.bin of=/dev/sdb seek=49

List of Modifications
---------------------
### *I. BASICS*
#### 1. Modify file: `boards.cfg`
Add line

    qt210                        arm         armv7       qt210               armzone        s5pc1xx

#### 2. Create directories
* board/armzone/qt210
* board/armzone/qt210/tools

#### 3. Add files
* board/armzone/qt210/Makefile
* board/armzone/qt210/lowlevel_init.S
* board/armzone/qt210/mem_setup.S
* board/armzone/qt210/mmc_boot.c
* board/armzone/qt210/movi.c
* board/armzone/qt210/qt210.c
* board/armzone/qt210/tools/mkv210_image.c
* common/cmd_movi.c
* include/movi.h
* include/s5pc11x.h
* include/s5pc110.h
* include/configs/qt210.h
* arch/arm/include/asm/arch-s5pc1xx/hardware.h
* drivers/mtd/nand/s5pc1xx_nand.c

#### 4. Modify file: `common/Makefile`
Add

    COBJS-$(CONFIG_CMD_MOVI) += cmd_movi.o

#### 5. Modify file: `common/cmd_nand.c`
Replace `WITH_INLINE_OOB` with `WITH_YAFFS_OOB`

#### 6. Modify file: `drivers/mtd/nand/Makefile`
Add

    OBJS-y += s5pc1xx_nand.o

behind

    OBJS-y += nand_util.o

### *II. ADD FASTBOOT SUPPORT*
#### 1. Add files
* board/armzone/qt210/fastboot.c
* board/armzone/qt210/fimd.c
* board/armzone/qt210/usbd-otg-hs.h
* board/armzone/qt210/usbd-otg-hs.c
* common/cmd_fastboot.c
* common/cmd_mmc_fdisk.c
* include/fastboot.h

#### 2. Modify file: `common/Makefile`
Add

    COBJS-$(CONFIG_FASTBOOT) += cmd_fastboot.o
    COBJS-$(CONFIG_FASTBOOT) += cmd_mmc_fdisk.o

Other Notes
-----------
Here is the code to light the LEDs.

Assembly:

    ldr r0, =0xE0200C00
    ldr r1, =0x1111
    str r1, [r0]
    ldr r1, =0x0F
    str r1, [r0, #4]

C code:

    *(volatile unsigned int *) 0xE0200C00 = 0x00001111;
    *(volatile unsigned int *) 0xE0200C04 = 0x0000000F;

References
----------
* [OpenCSBC U-Boot for mini210][4]
* [Official U-Boot support for QT210][5]

[1]: https://launchpad.net/u-boot-linaro/
[2]: http://www.denx.de/wiki/U-Boot
[3]: http://gitorious.org/opencsbc/u-boot/archive-tarball/mini210_linaro-2011.10-stable
[4]: http://gitorious.org/opencsbc/u-boot/trees/mini210_linaro-2011.10-stable
[5]: https://github.com/yjc/qt210_ics_uboot
