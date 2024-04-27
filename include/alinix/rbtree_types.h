#ifndef __ALINIX_KERNEL_BR_TREE_TYPES_H
#define __ALINIX_KERNEL_BR_TREE_TYPES_H


struct rb_node {
	unsigned long  __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
} __attribute__((aligned(sizeof(long))));


#endif // __ALINIX_KERNEL_BR_TREE_TYPES_H