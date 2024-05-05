#ifndef __ALINIX_KERNEL_NLS_H
#define __ALINIX_KERNEL_NLS_H

struct nls_table {
	const char *charset;
	const char *alias;
	int (*uni2char) (int uni, unsigned char *out, int boundlen);
	int (*char2uni) (const unsigned char *rawstring, int boundlen,
			 int *uni);
	const unsigned char *charset2lower;
	const unsigned char *charset2upper;
	// struct module *owner;
	// struct nls_table *next;
};


#endif