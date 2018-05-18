#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscalls.h>
#include <unistd.h>

int main()
{

printf("Test listProcInfo system call.");
  long int ret_val = eiy_listProcInfo();
  if(ret_val == 0)
    printf("listProcInfo executed correctly. Use dmesg to check process information.\n");
  else
    printf("listProcInfo did not execute correctly.");

}