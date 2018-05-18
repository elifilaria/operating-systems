#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <linux/kernel.h>
#include "lib.h"


int main(int argc, char **argv)
{
	printf("Testing kernel log.\n");
	if(argc <= 1) 
	{
		printf("Provide a string please.\n");
		return -1;
	}
	char *argument = argv[1];
	printf("You are making a system call with \"%s\".\n", argument);
	long result = eiy_kernellog(argument);
	printf("Sytem call returned %ld.\n Please use the dmseg command to see the result.\n", result);
	return result;
}