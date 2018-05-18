/* library source for new system calls */

#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <sys/types.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/sched.h>
#include "lib.h"


extern int errno;

#define __NR_dub2		 33

int dub2(int fd, int fd2) {
  return syscall(__NR_dub2, fd, fd2);
}

#define __NR_eiy_getpid 333

int eiy_getpid()
{
	return syscall (333);
}

#define __NR_eiy_helloworld 334

int eiy_helloworld()
{
	return syscall (334);
}

#define __NR_eiy_kernellog 335

long eiy_kernellog()
{
	return syscall (335);
}

#define __NR_eiy_listProcInfo 336

int eiy_listProcInfo()
{
	return syscall (336);
}