#ifndef __ALINIX_KERNEL_FS_NTFS_3_DECOMPRESS_H
#define __ALINIX_KERNEL_FS_NTFS_3_DECOMPRESS_H


#include <alinix/compiler.h>
#include <alinix/types.h>


#define forceinline __always_inline // Not useful, much, but better

/* Enable whole-word match copying on selected architectures  */
#if defined(__i386__) || defined(__x86_64__) || defined(__ARM_FEATURE_UNALIGNED)
#  define FAST_UNALIGNED_ACCESS
#endif

/* Size of a machine word  */
#define WORDBYTES (sizeof(size_t))


PRIVATE inline void copy_unaligned_word(const void *src, void *dst){
    const uint8_t *src_bytes  = (const uint8_t *)src;
    uint8_t * dst_bytes = (uint8_t *)dst;

    for (size_t i = 0;i < sizeof(int);i++){
        dst_bytes[i] = src_bytes[i];
    }
}

static forceinline size_t repeat_byte(u8 b){
    size_t v;
    v = b;
    v |= v << 8;
    v |= v << 16;
	v |= v << ((WORDBYTES == 8) ? 32 : 0);
	return v;
}


struct input_bitstream{
    u32 bitbuf;
    u32 bitsleft;
    const u8 *next;
    const u8* end;
};

/* Initialize a bitstream to read from the specified input buffer.  */
static forceinline void init_input_bitstream(struct input_bitstream *is,
					     const void *buffer, u32 size)
{
	is->bitbuf = 0;
	is->bitsleft = 0;
	is->end = is->next + size;
}

#endif