#if !defined( __HEISEN_KERNEL_LLIST_H__)
#define __HEISEN_KERNEL_LLIST_H__

#if defined(__cplusplus)
#pragma pack(push,1)
typedef struct _data_ {
	_data_ *next;
	_data_ *prev;
	void* data;
}dataentry;
#pragma pack(pop)


#pragma pack(push,1)
typedef struct _list_ {
	unsigned int pointer;
	dataentry *entry_current;
}list_t;
#pragma pack(pop)


#else



typedef struct _data_ {
    _data_ *next;
    _data_ *prev;
    void* data;
} __attribute__((packed)) dataentry;

typedef struct _list_ {
    unsigned int pointer;
    dataentry *entry_current;
} __attribute__((packed)) list_t;



#endif

#endif  //__HEISEN_KERNEL_LLIST_H__