#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXTOKS 100

struct name {
  char **tok;
  int count;
  int status;
};

int read_name(struct name* input, char **envp)
{
	enum status_value { NORMAL, EOF_OR_ERROR, TOO_MANY_TOKENS };

	input -> tok = malloc(MAXTOKS* sizeof(char *));
	char *buffer = NULL;
  	size_t buffsize = 0;
  	size_t chars;

	chars = getline(&buffer, &buffsize, stdin);
	
	int N = 0;
	int N0 = 0;
	int i;
	int j;
	
	for (i = 0; i < chars; i++)
	{
		if (isspace(buffer[i]) || buffer[i] == '\0')
		{
			if(N != 0)
			{
				if (i == '\0')
					N++;
				if(N0 >= MAXTOKS)
				{
					input -> status == TOO_MANY_TOKENS;
					break;
				}
				input -> tok[N0] = malloc((N+1) * sizeof(char));

				for(j = 0; j < N; j++)
				{
					char cc;
					if(i == '\0')
						cc = buffer[i-N+j+1];
					else
						cc = buffer[i-N+j];
					input -> tok[N0][j] = cc;
				}
				input -> tok[N0][N] = 0;
				N0++;
			}
			N = 0;
			continue;
		}
		N++;
	}
	input -> count = N0;
	input -> tok[N0+1] = NULL;


	if(chars == -1)
	{
		if (input -> tok[0][0] == 4)
		{
			input -> status = EOF_OR_ERROR;
			printf("You have entered too many tokens\n");
		}

	}
	else if (N0 >= MAXTOKS)
	{
		input -> status = EOF_OR_ERROR;
		printf("There was an error.\n");
	}
	else {
	    input -> status = NORMAL;
	}


	execve(input -> tok[0], input -> tok, envp);
  
   FILE *pFile1;
   FILE *pFile2;
   char *buff = NULL;
   size_t bufflen = 0; 

   pFile1 = fopen(input->tok[0], "r");
   pFile2 = fopen(input->tok[1], "w");
   if (pFile1 == NULL) 
     perror ("Error opening first file.\n");
   else if (pFile2 == NULL) 
     perror ("Error opening second file.\n");
   else {
     while (getline(&buff, &bufflen, pFile1) >= 0)
       fprintf(pFile2, "%s", buff);
     fclose(pFile1);
     fclose(pFile2);
   }
   return 0;
}


  
  int main(int argc, char **argv, char **envp)
  {
  	printf("Please enter two file names: ");
    struct name buffer;
    read_name(&buffer, envp);

  }


