/*
 * Copyright (c) 2023, MediaTek Inc. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>
#include <drivers/mmc.h>
#include <drivers/mmc/mtk-sd.h>
#include <lib/mmio.h>
#include <mt7981_gpio.h>
#include <platform_def.h>

struct msdc_gpio_mux_info {
	const uint32_t *pins;
	uint32_t count;
	uint32_t mux;
	const uint32_t *pupd;
};

static const struct msdc_compatible mt7981_msdc0_compat = {
	.clk_div_bits = 12,
	.pad_tune0 = true,
	.async_fifo = true,
	.data_tune = true,
	.busy_check = true,
	.stop_clk_fix = true,
};

static const uint32_t msdc0_pins[] = {
	GPIO15, GPIO16, GPIO17, GPIO18,
	GPIO19, GPIO20, GPIO21, GPIO22,
	GPIO23, GPIO24, GPIO25,
};

static const uint32_t msdc0_pupd[] = {
        MT_GPIO_PULL_UP, MT_GPIO_PULL_UP, MT_GPIO_PULL_UP, MT_GPIO_PULL_UP,
        MT_GPIO_PULL_UP, MT_GPIO_PULL_UP, MT_GPIO_PULL_UP, MT_GPIO_PULL_UP,
        MT_GPIO_PULL_UP, MT_GPIO_PULL_UP, MT_GPIO_PULL_DOWN,
};


static const struct msdc_gpio_mux_info msdc0_pinmux = {
	.pins = msdc0_pins,
	.count = ARRAY_SIZE(msdc0_pins),
	.mux = 2,
	.pupd = msdc0_pupd,
};

static const struct mt7981_msdc_conf {
	uintptr_t base;
	uintptr_t top_base;
	uint32_t bus_width;
	enum mmc_device_type type;
	uint32_t src_clk;
	const struct msdc_compatible *dev_comp;
	const struct msdc_gpio_mux_info *pinmux;
} mt7981_msdc[] = {
	{
		.base = MSDC0_BASE,
		.top_base = MSDC0_TOP_BASE,
		.bus_width = MMC_BUS_WIDTH_8,
		.type = MMC_IS_EMMC,
		.src_clk = 40000000,
		.dev_comp = &mt7981_msdc0_compat,
		.pinmux = &msdc0_pinmux,
	},
	{
		.base = MSDC0_BASE,
		.top_base = MSDC0_TOP_BASE,
		.bus_width = MMC_BUS_WIDTH_4,
		.type = MMC_IS_SD,
		.src_clk = 40000000,
		.dev_comp = &mt7981_msdc0_compat,
		.pinmux = &msdc0_pinmux,
	}
};

static void mmc_gpio_setup(void)
{

       /* GPIO IES */
       mmio_clrsetbits_32(MSDC_GPIO_IES_CFG0,
		0x7ff << EMMC45_GPIO_IES_S, 0x7ff << EMMC45_GPIO_IES_S);

       /* GPIO SMT */
       mmio_clrsetbits_32(MSDC_GPIO_SMT_CFG0,
		0x7ff << EMMC45_GPIO_SMT_S, 0x7ff << EMMC45_GPIO_SMT_S);

       /* GPIO R0 */
       mmio_clrsetbits_32(MSDC_GPIO_R0_CFG0,
		0x7ff << EMMC45_GPIO_R0_S, 0x6ff << EMMC45_GPIO_R0_S);

       /* GPIO R1 */
       mmio_clrsetbits_32(MSDC_GPIO_R1_CFG0,
		0x7ff << EMMC45_GPIO_R1_S, 0x100 << EMMC45_GPIO_R1_S);

        /* GPIO driving */
       mmio_clrsetbits_32(MSDC_GPIO_DRV_CFG0,
		0x7 << EMMC45_RSTB_DRV_S | 0x7 << EMMC45_DAT0_DRV_S |
		0x7 << EMMC45_DAT3_DRV_S | 0x7 << EMMC45_DAT4_DRV_S |
		0x7 << EMMC45_DAT2_DRV_S | 0x7 << EMMC45_DAT1_DRV_S |
		0x7 << EMMC45_DAT5_DRV_S | 0x7 << EMMC45_DAT6_DRV_S |
		0x7 << EMMC45_CLK_DRV_S  | 0x7 << EMMC45_CMD_DRV_S,

		0x1 << EMMC45_RSTB_DRV_S | 0x1 << EMMC45_DAT0_DRV_S |
		0x1 << EMMC45_DAT3_DRV_S | 0x1 << EMMC45_DAT4_DRV_S |
		0x1 << EMMC45_DAT2_DRV_S | 0x1 << EMMC45_DAT1_DRV_S |
		0x1 << EMMC45_DAT5_DRV_S | 0x1 << EMMC45_DAT6_DRV_S |
		0x1 << EMMC45_CLK_DRV_S  | 0x1 << EMMC45_CMD_DRV_S);

       mmio_clrsetbits_32(MSDC_GPIO_DRV_CFG1,
		0x7 << EMMC45_DAT7_DRV_S, 0x1 << EMMC45_DAT7_DRV_S);
}

int mtk_plat_mmc_setup(void)
{
	const struct mt7981_msdc_conf *conf = &mt7981_msdc[MSDC_INDEX];
	uint32_t i;

	for (i = 0; i < conf->pinmux->count; i++) {
		mt_set_pinmux_mode(conf->pinmux->pins[i], conf->pinmux->mux);
		mt_set_gpio_pull(conf->pinmux->pins[i], conf->pinmux->pupd[i]);
	}

	mmc_gpio_setup();

	mtk_mmc_init(conf->base, conf->top_base, conf->dev_comp,
		     conf->src_clk, conf->type, conf->bus_width);

	return 0;
}
