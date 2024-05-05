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

#endif