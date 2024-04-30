#include <alinix/build_bug.h>
#include <alinix/kernel.h>
#include <alinix/uapi/connector.h>
#include <alinix/types.h>

static inline struct cn_msg *buffer_to_cn_message(u8 *buffer){
    BUILD_BUG_ON(sizeof(struct cn_msg) != 20);
    return (struct cn_msg *)(buffer + 4);
}

static atomic_t proc_event_num_listeners = ATOMIC_INIT(0);
static struct cb_id cn_proc_event_id = { CN_IDX_PROC, CN_VAL_PROC };

