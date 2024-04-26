#ifndef __ALINIX_KERNEL_COMPILER_ATTRIBUTES_H
#define __ALINIX_KERNEL_COMPILER_ATTRIBUTES_H

#define __used                          __attribute__((__used__))

/*
 *   gcc: https://gcc.gnu.org/onlinedocs/gcc/Common-Function-Attributes.html#index-warn_005funused_005fresult-function-attribute
 * clang: https://clang.llvm.org/docs/AttributeReference.html#nodiscard-warn-unused-result
 */
#define __must_check                    __attribute__((__warn_unused_result__))

#endif /*__ALINIX_KERNEL_COMPILER_ATTRIBUTES_H*/