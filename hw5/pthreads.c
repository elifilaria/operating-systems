#include <stdio.h>
#include <pthread.h>

void *createpthread()
{
	printf("I am the PTHREAD. My pid is %d\n", getpid());
}

int main ()
{
	int x = 0;
	printf("I am the MAIN. My pid is %d \n ", getpid());
	
	pthread_t thread0;

	if (pthread_create(&thread0, NULL, createpthread, NULL))
	{
		printf("Error creating thread.\n");
		return 1;
	}

	printf("I am MAIN, and I successfully launched a pthread.\n");

	if (pthread_join(thread0, NULL))
	{
		printf("Error joining thread.\n");
		return 2;
	}

	printf("I am the MAIN, and the pthread has finished.\n");
}


//Yes the main and the pthread share the same pid in my system. 
//The pthread message and the middle message by main always appear in the same order.