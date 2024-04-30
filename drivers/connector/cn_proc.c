#include <alinix/build_bug.h>
#include <alinix/kernel.h>
#include <alinix/uapi/connector.h>

static inline struct cn_msg *buffer_to_cn_message(u8 *buffer){
    BUILD_BUG_ON(sizeof(struct cn_msg) != 20);
    return (struct cn_msg *)(buffer + 4);
}

