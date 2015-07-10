#ifndef _mylib_h
#define _mylib_h

#include <stdio.h>
typedef void (*my_fun_pt)(int);
void my_func(int i);/* __attribute__((section(".foo"), noinline));*/

#endif
