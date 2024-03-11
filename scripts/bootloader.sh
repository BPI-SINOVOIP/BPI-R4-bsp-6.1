#!/bin/sh

#gunzip -c BPI_M3_1080P.img.gz | dd of=/dev/mmcblk0 conv=sync,noerror bs=1k

die() {
        echo "$*" >&2
        exit 1
}

[ -s "./env.sh" ] || die "please run ./configure first."
. ./env.sh
O=$1
if [ ! -z $O ] ; then
	BOARD=$O
fi
U=$TOPDIR/out/${TARGET_PRODUCT}/100MB

mkdir -p $U
TMP_FILE=${U}/${BOARD}.tmp
IMG_FILE=${U}/${BOARD}-${service}-boot.img

(sudo dd if=/dev/zero of=${TMP_FILE} bs=512 count=21503) >/dev/null 2>&1
LOOP_DEV=`sudo losetup -f --show ${TMP_FILE}`

GPT=$TOPDIR/mt-pack/mtk/bpi-r4/bin/gpt
BL2=$TOPDIR/atf-mt/build_sdmmc/mt7988/release/bl2.img
FIP=$TOPDIR/u-boot-mt/build_sdmmc/u-boot_sdmmc.fip


(sudo dd if=$GPT	of=${LOOP_DEV} ) >/dev/null 2>&1
(sudo dd if=$BL2	of=${LOOP_DEV} bs=512 seek=34) >/dev/null 2>&1
(sudo dd if=$FIP	of=${LOOP_DEV} bs=512 seek=13312) >/dev/null 2>&1

sudo sync

sudo losetup -d ${LOOP_DEV}

(dd if=${TMP_FILE} of=${IMG_FILE} bs=512 status=noxfer) >/dev/null 2>&1

rm -f ${IMG_FILE}.gz
echo "gzip ${IMG_FILE}"
gzip ${IMG_FILE}
rm -f ${TMP_FILE}
