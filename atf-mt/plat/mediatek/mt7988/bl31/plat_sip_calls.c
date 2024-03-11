/*
 * copyright (c) 2023, mediatek inc. all rights reserved.
 *
 * spdx-license-identifier: bsd-3-clause
 */

#include <common/runtime_svc.h>
#include <mtk_sip_svc.h>
#include <plat_sip_calls.h>
#include <rng.h>
#ifdef FWDL
#include <fwdl.h>
#endif

static uintptr_t mt7988_sip_trng_get_rnd(uint32_t smc_fid, u_register_t x1,
					 u_register_t x2, u_register_t x3,
					 u_register_t x4, void *cookie,
					 void *handle, u_register_t flags)
{
	uint32_t value = 0;
	uintptr_t ret;

	ret = plat_get_rnd(&value);
	SMC_RET2(handle, ret, value);
}

#ifdef FWDL
static uintptr_t mt7988_sip_fwdl_load(uint32_t smc_fid, u_register_t x1,
				      u_register_t x2, u_register_t x3,
				      u_register_t x4, void *cookie,
				      void *handle, u_register_t flags)
{
	uintptr_t ret;

	ret = fw_load(x1, x2, x3);
	SMC_RET1(handle, ret);
}
#endif

struct mtk_sip_call_record mtk_plat_sip_calls[] = {
	MTK_SIP_CALL_RECORD(MTK_SIP_TRNG_GET_RND, mt7988_sip_trng_get_rnd),
#ifdef FWDL
	MTK_SIP_CALL_RECORD(MTK_SIP_FWDL_LOAD, mt7988_sip_fwdl_load),
#endif
};

const uint32_t mtk_plat_sip_call_num = ARRAY_SIZE(mtk_plat_sip_calls);
