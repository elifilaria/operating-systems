#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAXTOKS 100

struct name {
  char **tok;
  int count;
  int status;
};

int read_name(struct name* input, char **envp, const char *line)
{
	enum status_value { NORMAL, EOF_OR_ERROR, TOO_MANY_TOKENS };

	input -> tok = malloc(MAXTOKS* sizeof(char *));
	char *buffer = NULL;
  	size_t buffsize = 0;
  	size_t chars;

	chars = strlen(line);//getline(&buffer, &buffsize, stdin);
	buffsize = chars;


	int N = 0;
	int N0 = 0;
	int i;
	int j;
	
	for (i = 0; i < chars; i++)
	{
		if (isspace(line[i]) || line[i] == '\0')
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
						cc = line[i-N+j+1];
					else
						cc = line[i-N+j];
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
	input -> tok[N0+1] = "\0";


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
  /*
snprintf(input -> tok[0], MAXTOKS, 
     "GET /%s HTTP/1.1\r\n"  // POST or GET, both tested and works. Both HTTP 1.0 HTTP 1.1 works, but sometimes 
     "Host: %s\r\n"     // but sometimes HTTP 1.0 works better in localhost type
     "Content-type: application/x-www-form-urlencoded\r\n"
     "Content-length: %d\r\n\r\n"
     "%s\r\n", "hello", "rns202-6.cs.stolaf.edu", buffsize, &buffer);
int n;
/*char *ptr;
/// Write the request
if (write(input, input->tok[0], buffsize)>= 0) 
{
    /// Read the response
    while ((n = read(input, input->tok[1], MAXTOKS)) > 0) 
    {
        input->tok[1][n] = '\0';

        if(fputs(input->tok[1],stdout) == EOF) { printf("fputs erros"); }
        /// Remove the trailing chars
        ptr = strstr(input->tok[1], "\r\n\r\n");

        // check len for OutResponse here ?
        //snprintf(OutResponse, MAXRESPONSE,"%s", ptr);
    }
}          
*/
  
   FILE *pFile1;
 //  FILE *pFile2;
   char *buff = NULL;
   size_t bufflen = 0; 
   //printf("%s\n", input->tok[0][0]);

   pFile1 = fopen(input->tok[1], "r");
   //printf("%s\n", input->tok[0]);
   //pFile2 = fopen(input->tok[1], "w");
   if (pFile1 == NULL) 
     perror ("Error opening file.\n");
   //else if (pFile2 == NULL) 
     //perror ("Error opening second file.\n");
   else {
    while (getline(&buff, &bufflen, pFile1) >= 0)
       //fprintf(stdout, "%s\n", pFile1);
    	fprintf(stdout, "%s\n", buff);
     fclose(pFile1);
    // fclose(pFile2);
   }
   return 0;
}

/*
  
  int main(int argc, char **argv, char **envp)
  {
  	printf("Please enter a GET request: \n");
    struct name buffer;
    read_name(&buffer, envp);

  }


*/