/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Stefan Roese <sr@denx.de>
 */

#ifndef __CONFIG_RAVPOWER_RP_WD009_H
#define __CONFIG_RAVPOWER_RP_WD009_H

/* RAM */
#define CFG_SYS_SDRAM_BASE		0x80000000

#define CFG_SYS_INIT_SP_OFFSET		0x400000

/* UART */
#define CFG_SYS_BAUDRATE_TABLE		{ 9600, 19200, 38400, 57600, 115200, \
					  230400, 460800, 921600 }
#endif /* __CONFIG_RAVPOWER_RP_WD009_H */
