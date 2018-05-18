/* test program for lib.c */
#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <linux/kernel.h>
#include "lib.h"
int main()
{
  int rv;
  int rv2;
  int rv3;
  char *msg = "Hello, world!\n";
  printf("This process has pid %d\n", rv = getpid());
  printf("Try copy getpid 3 %d\n", rv2 = eiy_getpid());
  printf("Testing helloworld.\n");
  helloworld();
 // helloworld();
  printf("Please use dmseg to check if this system call worked.\n");
  char *myname = "Elif Ilaria Yurtseven\n";
  printf("Testing listProcInfo\n");
  eiy_listProcInfo();
  printf("Please check dmesg make sure this system call worked\n");
  
  return 0;
}
