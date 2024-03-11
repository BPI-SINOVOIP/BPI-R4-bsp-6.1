#
# Copyright (c) 2023, MediaTek Inc. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#

include lib/xlat_tables_v2/xlat_tables.mk

# Include GICv3 driver files
include drivers/arm/gic/v3/gicv3.mk

BL31_SOURCES		+=	drivers/arm/cci/cci.c				\
				$(GICV3_SOURCES)				\
				drivers/delay_timer/delay_timer.c		\
				drivers/delay_timer/generic_delay_timer.c	\
				lib/cpus/aarch64/aem_generic.S			\
				lib/cpus/aarch64/cortex_a53.S			\
				plat/common/plat_gicv3.c			\
				$(APSOC_COMMON)/drivers/uart/aarch64/hsuart.S	\
				$(APSOC_COMMON)/drivers/efuse/mtk_efuse.c	\
				$(APSOC_COMMON)/drivers/trng/rng.c		\
				$(APSOC_COMMON)/drivers/wdt/mtk_wdt.c		\
				$(APSOC_COMMON)/bl31/mtk_sip_svc.c		\
				$(APSOC_COMMON)/bl31/mtk_boot_next.c		\
				$(APSOC_COMMON)/bl31/bl31_common_setup.c	\
				$(APSOC_COMMON)/bl31/apsoc_sip_svc_common.c	\
				$(APSOC_COMMON)/bl31/plat_topology.c		\
				$(APSOC_COMMON)/bl31/mtk_gic_v3.c		\
				$(APSOC_COMMON)/bl31/plat_pm.c			\
				$(MTK_PLAT_SOC)/aarch64/plat_helpers.S		\
				$(MTK_PLAT_SOC)/aarch64/platform_common.c	\
				$(MTK_PLAT_SOC)/bl31/bl31_plat_setup.c		\
				$(MTK_PLAT_SOC)/bl31/bl31_plat_pm.c		\
				$(MTK_PLAT_SOC)/bl31/plat_sip_calls.c		\
				$(MTK_PLAT_SOC)/drivers/spmc/mtspmc.c		\
				$(MTK_PLAT_SOC)/drivers/timer/timer.c		\
				$(MTK_PLAT_SOC)/drivers/spmc/mtspmc.c

BL31_SOURCES		+=	lib/xlat_tables/xlat_tables_common.c		\
				lib/xlat_tables/aarch64/xlat_tables.c
BL31_CPPFLAGS		+=	-DPLAT_XLAT_TABLES_DYNAMIC
BL31_CPPFLAGS		+=	-I$(APSOC_COMMON)/bl31

MTK_SIP_KERNEL_BOOT_ENABLE := 1
$(eval $(call add_define,MTK_SIP_KERNEL_BOOT_ENABLE))
