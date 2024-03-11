#!/bin/sh

# make partition table by fdisk command
# root@BPI-R4:~# blkid
# /dev/mmcblk0p1: PARTLABEL="bl2" PARTUUID="5452574f-2211-4433-5566-778899aabb01"
# /dev/mmcblk0p2: PARTLABEL="ubootenv" PARTUUID="5452574f-2211-4433-5566-778899aabb02"
# /dev/mmcblk0p3: PARTLABEL="factory" PARTUUID="5452574f-2211-4433-5566-778899aabb03"
# /dev/mmcblk0p4: PARTLABEL="fip" PARTUUID="5452574f-2211-4433-5566-778899aabb04"
# /dev/mmcblk0p5: SEC_TYPE="msdos" LABEL_FATBOOT="BPI-BOOT" LABEL="BPI-BOOT" UUID="61C6-47AA" BLOCK_SIZE="512" TYPE="vfat" PARTLABEL="BPI-BOOT" PARTUUID="bb362f04-3d07-4a45-b6de-82f4c3a501a3"
# /dev/mmcblk0p6: LABEL="BPI-ROOT" UUID="4ff2b310-fd68-41fe-ad5c-2b414d705fe6" BLOCK_SIZE="4096" TYPE="ext4" PARTLABEL="BPI-ROOT" PARTUUID="3843210e-088a-4711-b662-8a79e00272e4"

die() {
        echo "$*" >&2
        exit 1
}

[ $# -eq 1 ] || die "Usage: $0 /dev/sdc"

[ -s "./env.sh" ] || die "please run ./configure first."

. ./env.sh

O=$1

GPT=$TOPDIR/mt-pack/mtk/bpi-r4/bin/gpt
BL2=$TOPDIR/atf-mt/build_sdmmc/mt7988/release/bl2.img
FIP=$TOPDIR/u-boot-mt/build_sdmmc/u-boot_sdmmc.fip

sudo dd if=$GPT 	of=$O

sudo dd if=$BL2 	of=$O bs=512 seek=34

sudo dd if=$FIP 	of=$O bs=512 seek=13312

