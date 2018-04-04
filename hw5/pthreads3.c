#include <stdio.h>
#include <pthread.h>

pthread_mutex_t val_mutex;

void *createpthread(void *val_void_ptr)
{
	printf("I am the PTHREAD. My pid is %d\n", getpid());
	int *val_ptr = (int *) val_void_ptr;
	pthread_mutex_lock(&val_mutex);
	*val_ptr += 1;
	pthread_mutex_unlock(&val_mutex);
}

int main ()
{
	int val = 10;
	printf("I am the MAIN. My pid is %d \n ", getpid());
	
	pthread_t thread0;

	if (pthread_create(&thread0, NULL, createpthread, &val))
	{
		printf("Error creating thread.\n");
		return 1;
	}

	printf("I am MAIN, and I successfully launched a pthread.\n");

	pthread_mutex_lock(&val_mutex);
	val += 2;
	pthread_mutex_unlock(&val_mutex);

	if (pthread_join(thread0, NULL))
	{
		printf("Error joining thread.\n");
		return 2;
	}

	printf("I am the MAIN, and the pthread has finished.\n");

	printf("%d\n", val);
}

//Yes, it does return 13 constantly.