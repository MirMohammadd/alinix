#ifndef TESTING_H
#define TESTING_H

void try_strtok();
void try_kmalloc();
void try_printmem(void);
void do_fault();
void help_tester();
void try_module();
void try_open();
void try_ocreat();
void try_syscall();
void try_check();
void show_fd();
void test_stat();
void try_shadow();
//void try_newheap();
void try_mapaddress();
void try_tasksetup();
void try_taskdel();
void try_taskadd();
int task_testsecond(void *);
void task_testthird();
int task_test(void *);

#endif