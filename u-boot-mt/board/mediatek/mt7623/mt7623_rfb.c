// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2018 MediaTek Inc.
 */

#include <common.h>
#include <dm.h>
#include <button.h>
#include <env.h>
#include <init.h>
#include <mmc.h>
#include <part.h>
#include <asm/global_data.h>
#include <linux/delay.h>

#ifndef CONFIG_RESET_BUTTON_LABEL
#define CONFIG_RESET_BUTTON_LABEL "reset"
#endif

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = CFG_SYS_SDRAM_BASE + 0x100;

	return 0;
}

#ifdef CONFIG_MMC
int mmc_get_boot_dev(void)
{
	int g_mmc_devid = -1;
	char *uflag = (char *)0x81DFFFF0;
	struct blk_desc *desc;

	if (blk_get_device_by_str("mmc", "1", &desc) < 0)
		return 0;

	if (strncmp(uflag,"eMMC",4)==0) {
		g_mmc_devid = 0;
		printf("Boot From Emmc(id:%d)\n\n", g_mmc_devid);
	} else {
		g_mmc_devid = 1;
		printf("Boot From SD(id:%d)\n\n", g_mmc_devid);
	}
	return g_mmc_devid;
}

int mmc_get_env_dev(void)
{
	return mmc_get_boot_dev();
}
#endif

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
