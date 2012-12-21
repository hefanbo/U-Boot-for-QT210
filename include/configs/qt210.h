/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <gj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK6400(mDirac-III) board.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_SAMSUNG
#define CONFIG_S5P
#define CONFIG_QT210

#include <asm/arch/cpu.h>

#define CONFIG_MACH_SMDKV210
#define CONFIG_MACH_TYPE	MACH_TYPE_SMDKV210
#define CONFIG_MCP_SINGLE
#define CONFIG_EVT1

#define CONFIG_SPL

#define CONFIG_ARCH_CPU_INIT
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_CMDLINE_TAG
#define CONFIG_ENV_OVERWRITE
#define BOARD_LATE_INIT

#define CONFIG_IDENT_STRING	" for ARMZONE-QT210"
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_BOOTDELAY	3
#define CONFIG_ZERO_BOOTDELAY_CHECK


#define CONFIG_PWM
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_S5P_MMC
#define CONFIG_SYS_DCACHE_OFF
#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_ENABLE_MMU
#endif
#ifndef CONFIG_ENABLE_MMU
#define virt_to_phys(x)		(x)
#endif

#define CONFIG_DOS_PARTITION

/* Console */
#define CONFIG_SYS_PROMPT	"U-Boot # "
#define CONFIG_SYS_CBSIZE	256	/* Console I/O Buffer Size*/
#define CONFIG_SYS_PBSIZE	384	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16	/* max number of command args */


/* Boot argument buffer size */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE


/* Commands */
#include <config_cmd_default.h>
#define CONFIG_CMD_FAT
#define CONFIG_CMD_MMC
#define CONFIG_CMD_MOVI
#define CONFIG_CMD_MOVINAND

#undef CONFIG_CMD_NET
#if defined(CONFIG_CMD_NET)
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#else
#undef CONFIG_CMD_NFS
#endif

#define CONFIG_BOOTCOMMAND	"movi read kernel 30008000; movi read rootfs 40A00000 180000; bootm 30008000 40A00000"


/* Clock */
#define CONFIG_SYS_CLK_FREQ	24000000
#define CONFIG_SYS_HZ		1000


/* Addresses */
#define CONFIG_SYS_SDRAM_BASE	0x30000000	/* README: "_Must_ be 0 here" ? */
#define CONFIG_SYS_TEXT_BASE	0x33E00000
#define CONFIG_PHY_UBOOT_BASE	(CONFIG_SYS_SDRAM_BASE + 0x3E00000)
#define CONFIG_PHY_KERNEL_BASE	(CONFIG_SYS_SDRAM_BASE + 0x8000)
#define CONFIG_SYS_LOAD_ADDR	PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR (CONFIG_SYS_LOAD_ADDR - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x3E00000)


/* Sizes */
#define CONFIG_STACKSIZE	0x40000		/* 256 kB */
#define CONFIG_SYS_MALLOC_LEN	(CONFIG_ENV_SIZE + (1 << 20))
#if defined(CONFIG_USE_IRQ)
#define CONFIG_STACKSIZE_IRQ	(4*1024)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4*1024)	/* FIQ stack */
#endif


/* DRAM */
#define CONFIG_NR_DRAM_BANKS	1
#define SDRAM_BANK_SIZE		0x20000000	/* 512 MB */
#define PHYS_SDRAM_1		CONFIG_SYS_SDRAM_BASE
#define PHYS_SDRAM_1_SIZE	SDRAM_BANK_SIZE
#if 0
#define PHYS_SDRAM_2		(CONFIG_SYS_SDRAM_BASE + 0x20000000)
#define PHYS_SDRAM_2_SIZE	SDRAM_BANK_SIZE
#endif


/* LCD */
#define CONFIG_LCD_QT210
#define CONFIG_LCD_FBUFFER	0x38000000


/* Serial */
#define CONFIG_SERIAL0
#define CONFIG_SERIAL_MULTI
#define CONFIG_BAUDRATE		115200
#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }


/* Flash */
#define CONFIG_MX_LV640EB
#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_MAX_FLASH_SECT	135
#define PHYS_FLASH_SIZE			0x800000	/* 8MB */
#define CONFIG_SYS_FLASH_BASE		0x80000000
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_LEGACY
#define CONFIG_SYS_FLASH_LEGACY_512Kx16
#define CONFIG_SYS_FLASH_ERASE_TOUT	(5*CONFIG_SYS_HZ)	/* Timeout for Flash Erase */
#define CONFIG_SYS_FLASH_WRITE_TOUT	(5*CONGIF_SYS_HZ)	/* Timeout for Flash Write */


/* Environment */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV	0
#define RESERVE_BLOCK_SIZE	512
#define BL1_SIZE		(8 << 10)	/* 8 kB reserved for BL1 */
#define CONFIG_ENV_OFFSET	(RESERVE_BLOCK_SIZE + BL1_SIZE + ((16 + 512) * 1024))
#define CONFIG_ENV_SIZE		0x4000		/* 16 kB */
#define CONFIG_ENV_ADDR		0


/* Fastboot */
#define CONFIG_FASTBOOT	
#if defined(CONFIG_FASTBOOT)
#define CONFIG_FASTBOOT_TRANSFER_BUFFER		0x3F000000
#define CONFIG_FASTBOOT_TRANSFER_BUFFER_SIZE	0x11000000   /* 272MB */
#if 0
#define CONFIG_FASTBOOT_TRANSFER_BUFFER_SIZE	0x19000000   /* 400MB */
#endif
#define CONFIG_FASTBOOT_ADDR_KERNEL		0x30008000
#define CONFIG_FASTBOOT_ADDR_RAMDISK		0x30A00000
#define CONFIG_FASTBOOT_PAGESIZE		2048	/* Page size of booting device */
#define CONFIG_FASTBOOT_SDMMC_BLOCKSIZE		512	/* Block size of sdmmc */
#if 0
#define CONFIG_FASTBOOT_ONENANDBSP
#define CONFIG_FASTBOOT_NANDBSP
#endif
#define CONFIG_FASTBOOT_SDMMCBSP
#endif


/* DM9000 ethernet */
#if defined(CONFIG_CMD_NET)
#define DM9000_16BIT_DATA
#define CONFIG_DRIVER_DM9000
#define CONFIG_NET_MULTI
#define CONFIG_NET_RETRY_COUNT	10
#define CONFIG_DM9000_NO_SROM
#define CONFIG_DM9000_BASE	0x88000000
#define DM9000_IO		CONFIG_DM9000_BASE
#define DM9000_DATA		(CONFIG_DM9000_BASE + 0x8)
#define CONFIG_ETHADDR		00:40:5c:26:0a:5b
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.0.130
#define CONFIG_SERVERIP		192.168.0.102
#define CONFIG_GATEWAYIP	192.168.0.1
#endif


/* NAND */
#define CONFIG_CMD_NAND
#if defined(CONFIG_CMD_NAND)
#define CONFIG_MTD_DEVICE
#define CONFIG_CMD_MTDPARTS
#define CONFIG_CMD_NAND_YAFFS
#define CONFIG_CMD_NAND_YAFFS_SKIPFB
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE	0xB0E000000
#define NAND_MAX_CHIPS		1
#define NAND_DISABLE_CE()	(NFCONT_REG |= (1 << 1))
#define NAND_ENABLE_CE()	(NFCONT_REG &= ~(1 << 1))
#define NF_TRANSRnB()		do { while(!(NFSTAT_REG & (1 << 0))); } while(0)
#endif


#if 0
#define CONFIG_CLK_667_166_166_133
#define CONFIG_CLK_533_133_100_100
#define CONFIG_CLK_800_200_166_133
#define CONFIG_CLK_800_100_166_133
#endif
#define CONFIG_CLK_1000_200_166_133
#if 0
#define CONFIG_CLK_400_200_166_133
#define CONFIG_CLK_400_100_166_133
#endif

#if defined(CONFIG_CLK_667_166_166_133)
#define APLL_MDIV	0xfa
#define APLL_PDIV	0x6
#define APLL_SDIV	0x1
#elif defined(CONFIG_CLK_533_133_100_100)
#define APLL_MDIV	0x215
#define APLL_PDIV	0x18
#define APLL_SDIV	0x1
#elif defined(CONFIG_CLK_800_200_166_133) || \
	defined(CONFIG_CLK_800_100_166_133) || \
	defined(CONFIG_CLK_400_200_166_133) || \
	defined(CONFIG_CLK_400_100_166_133)
#define APLL_MDIV	0x64
#define APLL_PDIV	0x3
#define APLL_SDIV	0x1
#elif defined(CONFIG_CLK_1000_200_166_133)
#define APLL_MDIV	0x7d
#define APLL_PDIV	0x3
#define APLL_SDIV	0x1
#endif

#define APLL_LOCKTIME_VAL	0x2cf

#if defined(CONFIG_EVT1)
#define AFC_ON		0x00000000
#define AFC_OFF		0x10000010
#endif

#if defined(CONFIG_CLK_533_133_100_100)
#define MPLL_MDIV	0x190
#define MPLL_PDIV	0x6
#define MPLL_SDIV	0x2
#else
#define MPLL_MDIV	0x29b
#define MPLL_PDIV	0xc
#define MPLL_SDIV	0x1
#endif

#define EPLL_MDIV	0x60
#define EPLL_PDIV	0x6
#define EPLL_SDIV	0x2

#define VPLL_MDIV	0x6c
#define VPLL_PDIV	0x6
#define VPLL_SDIV	0x3

/* CLK_DIV0 */
#define APLL_RATIO	0
#define A2M_RATIO	4
#define HCLK_MSYS_RATIO	8
#define PCLK_MSYS_RATIO	12
#define HCLK_DSYS_RATIO	16
#define PCLK_DSYS_RATIO 20
#define HCLK_PSYS_RATIO	24
#define PCLK_PSYS_RATIO 28

#define CLK_DIV0_MASK	0x7fffffff

#define set_pll(mdiv, pdiv, sdiv)	(1<<31 | mdiv<<16 | pdiv<<8 | sdiv)

#define APLL_VAL	set_pll(APLL_MDIV,APLL_PDIV,APLL_SDIV)
#define MPLL_VAL	set_pll(MPLL_MDIV,MPLL_PDIV,MPLL_SDIV)
#define EPLL_VAL	set_pll(EPLL_MDIV,EPLL_PDIV,EPLL_SDIV)
#define VPLL_VAL	set_pll(VPLL_MDIV,VPLL_PDIV,VPLL_SDIV)

#if defined(CONFIG_CLK_667_166_166_133)
#define CLK_DIV0_VAL	((0<<APLL_RATIO)|(3<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_533_133_100_100)
#define CLK_DIV0_VAL	((0<<APLL_RATIO)|(3<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(3<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_800_200_166_133)
#define CLK_DIV0_VAL	((0<<APLL_RATIO)|(3<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_800_100_166_133)
#define CLK_DIV0_VAL	((0<<APLL_RATIO)|(7<<A2M_RATIO)|(7<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_400_200_166_133)
#define CLK_DIV0_VAL	((1<<APLL_RATIO)|(3<<A2M_RATIO)|(1<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_400_100_166_133)
#define CLK_DIV0_VAL	((1<<APLL_RATIO)|(7<<A2M_RATIO)|(3<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#elif defined(CONFIG_CLK_1000_200_166_133)
#define CLK_DIV0_VAL	((0<<APLL_RATIO)|(4<<A2M_RATIO)|(4<<HCLK_MSYS_RATIO)|(1<<PCLK_MSYS_RATIO)\
			|(3<<HCLK_DSYS_RATIO)|(1<<PCLK_DSYS_RATIO)|(4<<HCLK_PSYS_RATIO)|(1<<PCLK_PSYS_RATIO))
#endif

#define CLK_DIV1_VAL	((1<<16)|(1<<12)|(1<<8)|(1<<4))
#define CLK_DIV2_VAL	(1<<0)

#if defined(CONFIG_CLK_533_133_100_100)

#if defined(CONFIG_MCP_SINGLE)

#define DMC0_TIMINGA_REF	0x40e
#define DMC0_TIMING_ROW		0x10233206
#define DMC0_TIMING_DATA	0x12130005
#define	DMC0_TIMING_PWR		0x0E100222

#define DMC1_TIMINGA_REF	0x40e
#define DMC1_TIMING_ROW		0x10233206
#define DMC1_TIMING_DATA	0x12130005
#define	DMC1_TIMING_PWR		0x0E100222

#else

#error "You should define memory type (AC type or H type or B type)"

#endif

#elif defined(CONFIG_CLK_800_200_166_133) || \
	defined(CONFIG_CLK_1000_200_166_133) || \
	defined(CONFIG_CLK_800_100_166_133) || \
	defined(CONFIG_CLK_400_200_166_133) || \
	defined(CONFIG_CLK_400_100_166_133)

#if defined(CONFIG_MCP_SINGLE)

#define DMC0_MEMCONTROL		0x00202400	// MemControl	BL=4, 1Chip, DDR2 Type, dynamic self refresh, force precharge, dynamic power down off
#define DMC0_MEMCONFIG_0	0x20E01323	// MemConfig0	256MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC0_MEMCONFIG_1	0x40F01323	// MemConfig1
#define DMC0_TIMINGA_REF	0x00000618	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)
#define DMC0_TIMING_ROW		0x28233287	// TimingRow	for @200MHz
#define DMC0_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC0_TIMING_PWR		0x09C80232	// TimingPower

#define	DMC1_MEMCONTROL		0x00202400	// MemControl	BL=4, 2 chip, DDR2 type, dynamic self refresh, force precharge, dynamic power down off
#define DMC1_MEMCONFIG_0	0x40C01323	// MemConfig0	512MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC1_MEMCONFIG_1	0x00E01323	// MemConfig1
#define DMC1_TIMINGA_REF	0x00000618	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4
#define DMC1_TIMING_ROW		0x28233289	// TimingRow	for @200MHz
#define DMC1_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC1_TIMING_PWR		0x08280232	// TimingPower
#if defined(CONFIG_CLK_800_100_166_133) || defined(CONFIG_CLK_400_100_166_133)
#define DMC0_MEMCONFIG_0	0x20E01323	// MemConfig0	256MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC0_MEMCONFIG_1	0x40F01323	// MemConfig1
#define DMC0_TIMINGA_REF	0x0000030C	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4E)
#define DMC0_TIMING_ROW		0x28233287	// TimingRow	for @200MHz
#define DMC0_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC0_TIMING_PWR		0x09C80232	// TimingPower

#define	DMC1_MEMCONTROL		0x00202400	// MemControl	BL=4, 2 chip, DDR2 type, dynamic self refresh, force precharge, dynamic power down off
#define DMC1_MEMCONFIG_0	0x40C01323	// MemConfig0	512MB config, 8 banks,Mapping Method[12:15]0:linear, 1:linterleaved, 2:Mixed
#define DMC1_MEMCONFIG_1	0x00E01323	// MemConfig1
#define DMC1_TIMINGA_REF	0x0000030C	// TimingAref	7.8us*133MHz=1038(0x40E), 100MHz=780(0x30C), 20MHz=156(0x9C), 10MHz=78(0x4
#define DMC1_TIMING_ROW		0x28233289	// TimingRow	for @200MHz
#define DMC1_TIMING_DATA	0x23240304	// TimingData	CL=3
#define	DMC1_TIMING_PWR		0x08280232	// TimingPower
#endif

#else

#error "You should define memory type (AC type or H type)"

#endif

#else

#define DMC0_TIMINGA_REF	0x50e
#define DMC0_TIMING_ROW		0x14233287
#define DMC0_TIMING_DATA	0x12130005
#define	DMC0_TIMING_PWR		0x0E140222

#define DMC1_TIMINGA_REF	0x618
#define DMC1_TIMING_ROW		0x11344309
#define DMC1_TIMING_DATA	0x12130005
#define	DMC1_TIMING_PWR		0x0E190222

#endif


#if defined(CONFIG_CLK_533_133_100_100)
#define UART_UBRDIV_VAL		26
#define UART_UDIVSLOT_VAL	0x0808
#else
#define UART_UBRDIV_VAL		34
#define UART_UDIVSLOT_VAL	0xDDDD
#endif


#endif	/* __CONFIG_H */
