lzma_compress-objs := LzFind.o LzmaEnc.o
lzma_decompress-objs := LzmaDec.o

obj-$(CONFIG_LZMA_COMPRESS) += lzma_compress.o
obj-$(CONFIG_LZMA_DECOMPRESS) += lzma_decompress.o

EXTRA_CFLAGS += -I $(srctree)/include/linux -I $(srctree)/include/linux/lzma -include $(srctree)/include/linux/types.h
