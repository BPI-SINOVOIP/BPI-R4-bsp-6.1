// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 MediaTek Inc.
 * Author: Sam Shih <sam.shih@mediatek.com>
 */

#include <common.h>
#include <config.h>
#include <dm.h>
#include <button.h>
#include <env.h>
#include <init.h>
#include <asm/global_data.h>
#include <linux/delay.h>

#ifndef CONFIG_RESET_BUTTON_LABEL
#define CONFIG_RESET_BUTTON_LABEL "reset"
#endif

#include <mtd.h>
#include <linux/mtd/mtd.h>
#include <nmbm/nmbm.h>
#include <nmbm/nmbm-mtd.h>

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	return 0;
}

int board_late_init(void)
{
	struct udevice *dev;

	if (!button_get_by_label(CONFIG_RESET_BUTTON_LABEL, &dev)) {
		puts("reset button found\n");
#ifdef CONFIG_RESET_BUTTON_SETTLE_DELAY
		if (CONFIG_RESET_BUTTON_SETTLE_DELAY > 0) {
			button_get_state(dev);
			mdelay(CONFIG_RESET_BUTTON_SETTLE_DELAY);
		}
#endif
		if (button_get_state(dev) == BUTTON_ON) {
			puts("button pushed, resetting environment\n");
			gd->env_valid = ENV_INVALID;
		}
	}

	env_relocate();
	return 0;
}

int board_nmbm_init(void)
{
#ifdef CONFIG_ENABLE_NAND_NMBM
	struct mtd_info *lower, *upper;
	int ret;

	printf("\n");
	printf("Initializing NMBM ...\n");

	mtd_probe_devices();

	lower = get_mtd_device_nm("spi-nand0");
	if (IS_ERR(lower) || !lower) {
		printf("Lower MTD device 'spi-nand0' not found\n");
		return 0;
	}

	ret = nmbm_attach_mtd(lower,
			      NMBM_F_CREATE | NMBM_F_EMPTY_PAGE_ECC_OK,
			      CONFIG_NMBM_MAX_RATIO,
			      CONFIG_NMBM_MAX_BLOCKS, &upper);

	printf("\n");

	if (ret)
		return 0;

	add_mtd_device(upper);
#endif

	return 0;
}
