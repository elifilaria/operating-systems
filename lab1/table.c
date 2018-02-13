#include <stdio.h>
#include <stdlib.h>


int main()
{
		int n;
		int a;
		printf("Enter a positive integer: ");
		scanf("%d", &n);
		printf("N\t|N*N\n");
		for (a=1; a <= n; a++) {
			printf("%d\t|%d", a, a*a);
			printf("\n");
		}
		
}