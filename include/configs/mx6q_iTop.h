/*
 * Copyright (C) 2012-2016 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Freescale i.MX6Q SabreSD board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MX6Q_ITOP_CONFIG_H
#define __MX6Q_ITOP_CONFIG_H

#ifdef CONFIG_SPL
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#include "imx6_spl.h"
#endif

#define CONFIG_MACH_TYPE	3980
#define CONFIG_MXC_UART_BASE	UART1_BASE
#define CONFIG_CONSOLE_DEV		"ttymxc0"
#define CONFIG_MMCROOT			"/dev/mmcblk3p1"  /* SDHC4 */

#if defined(CONFIG_MX6QP)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6Q)
#define PHYS_SDRAM_SIZE		(2u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6DL)
#define PHYS_SDRAM_SIZE		(1u * 1024 * 1024 * 1024)
#elif defined(CONFIG_MX6SOLO)
#define PHYS_SDRAM_SIZE		(512u * 1024 * 1024)
#endif

#include "mx6sabre_common.h"

#define CONFIG_SYS_FSL_USDHC_NUM	3
#define CONFIG_SYS_MMC_ENV_DEV		1	/* SDHC3 */
#define CONFIG_SYS_MMC_ENV_PART                0       /* user partition */

#ifdef CONFIG_SYS_USE_SPINOR
#define CONFIG_SF_DEFAULT_CS   0
#endif

/*  Load file config  */
#ifdef CONFIG_LOADADDR
#undef CONFIG_LOADADDR
#endif
#define CONFIG_LOADADDR		0x10800000

#define CONFIG_DEFAULT_FDT_FILE     "imx6q-sabresd.dtb"
/*  end of Load file config  */

/*  Net config  */
#ifdef CONFIG_PHY_ATHEROS
#undef CONFIG_PHY_ATHEROS
#endif
#ifndef CONFIG_PHY_REALTEK
#define CONFIG_PHY_REALTEK
#endif
#ifdef CONFIG_FEC_MXC_PHYADDR
#undef CONFIG_FEC_MXC_PHYADDR
#endif
#define CONFIG_FEC_MXC_PHYADDR      4
#ifdef CONFIG_ETHPRIME
#undef CONFIG_ETHPRIME
#endif
#define CONFIG_ETHPRIME         "FEC"

#define CONFIG_ETHADDR          "12:34:56:78:90:AB"
#define CONFIG_IPADDR           192.168.6.6
#define CONFIG_SERVERIP         192.168.6.66
#define CONFIG_NETMASK          255.255.255.0
#define CONFIG_GATEWAYIP        192.168.6.1



/*  end of Net config  */

/*  env setting config  */
#ifdef CONFIG_EXTRA_ENV_SETTINGS
#undef CONFIG_EXTRA_ENV_SETTINGS
#endif
#define	CONFIG_EXTRA_ENV_SETTINGS					\
		"netdev=eth0\0"						\
    "ethaddr="CONFIG_ETHADDR"\0"        \
		"uboot=u-boot.imx\0"			\
		"kernel=uImage\0"				\
		"dtb_file=imx6q-iTop.dtb\0"	\
    "fdt_high=0xffffffff\0"     \
    "fdt_addr=0x12000000\0"     \
		"rootpath=/home/neo/share/nfs/rootfs\0"				\
		"bootargs_base=setenv bootargs console="CONFIG_CONSOLE_DEV",115200\0"	\
		"bootargs_nfs=setenv bootargs ${bootargs} root=/dev/nfs "	\
			"rw nfsroot=${serverip}:${rootpath},v3,tcp "	\
			"ip=${ipaddr}:${serverip}:${gateway}:${netmask}::eth0::off "	\
			"init=linuxrc;\0"	\
		"bootcmd_net=run bootargs_base bootargs_nfs; "		\
			"tftpboot ${loadaddr} ${kernel};"	\
			"tftpboot ${fdt_addr} ${dtb_file};"	\
			"fdt addr ${fdt_addr};"     \
			"bootm ${loadaddr} - ${fdt_addr};\0"	\
		"bootargs_mmc=setenv bootargs ${bootargs} ip=dhcp "     \
			"root="CONFIG_MMCROOT" rootwait\0"                \
		"bootcmd_mmc=run bootargs_base bootargs_mmc; "   \
			"mmc dev 2; "	\
			"mmc read ${loadaddr} 0x800 0x4000;"       \
      "mmc read ${fdt_addr} 0x4800 0x800;" 	\
      "fdt addr ${fdt_addr};"     \
      "bootm ${loadaddr} - ${fdt_addr};\0"	\
		"bootcmd=run bootcmd_net\0"                             \
/*  end of env setting config  */

/*
 * imx6 q/dl/solo pcie would be failed to work properly in kernel, if
 * the pcie module is iniialized/enumerated both in uboot and linux
 * kernel.
 * rootcause:imx6 q/dl/solo pcie don't have the reset mechanism.
 * it is only be RESET by the POR. So, the pcie module only be
 * initialized/enumerated once in one POR.
 * Set to use pcie in kernel defaultly, mask the pcie config here.
 * Remove the mask freely, if the uboot pcie functions, rather than
 * the kernel's, are required.
 */
/* #define CONFIG_CMD_PCI */
#ifdef CONFIG_CMD_PCI
#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(3, 19)
#endif

/* USB Configs */
#define CONFIG_CMD_USB
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC		(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS		0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1 /* Enabled USB controller number */
#endif

/*#define CONFIG_SPLASH_SCREEN*/
/*#define CONFIG_MXC_EPDC*/

/*
 * SPLASH SCREEN Configs
 */
#if defined(CONFIG_SPLASH_SCREEN) && defined(CONFIG_MXC_EPDC)
	/*
	 * Framebuffer and LCD
	 */
	#define CONFIG_CMD_BMP
	#define CONFIG_LCD
	#define CONFIG_SYS_CONSOLE_IS_IN_ENV
	#undef LCD_TEST_PATTERN
	/* #define CONFIG_SPLASH_IS_IN_MMC			1 */
	#define LCD_BPP					LCD_MONOCHROME
	/* #define CONFIG_SPLASH_SCREEN_ALIGN		1 */

	#define CONFIG_WAVEFORM_BUF_SIZE		0x200000
#endif /* CONFIG_SPLASH_SCREEN && CONFIG_MXC_EPDC */

#undef CONFIG_LDO_BYPASS_CHECK


#endif                         /* __MX6Q_ITOP_CONFIG_H */
