/* Server-side use of Berkeley socket calls -- receive one message and print 
   Requires one command line arg:  
     1.  port number to use (on this machine). 
   RAB 3/12 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include "copyfile.c"
#define MAXBUFF 100
#define MAXTOKS 100
/*
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

  chars = getline(&buffer, &buffsize, stdout);
  
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

  
   FILE *pFile1;
 //  FILE *pFile2;
   char *buff = NULL;
   size_t bufflen = 0; 

   pFile1 = fopen(input->tok[1], "r");
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

*/
int main(int argc, char **argv, char **envp) {
  char *prog = argv[0];
  int port;
  int serverd;  /* socket descriptor for receiving new connections */

  if (argc < 2) {
    printf("Usage:  %s port\n", prog);
    return 1;
  }
  port = atoi(argv[1]);

  if ((serverd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("%s ", prog);
    perror("socket()");
    return 1;
  }
  
  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = INADDR_ANY;

  if (bind(serverd, (struct sockaddr*) &sa, sizeof(sa)) < 0) {
    printf("%s ", prog);
    perror("bind()");
    return 1;
  }
  if (listen(serverd, 5) < 0) {
    printf("%s ", prog);
    perror("listen()");
    return 1;
  }

  
  int clientd;  /* socket descriptor for communicating with client */
  struct sockaddr_in ca;
  int size = sizeof(struct sockaddr);

  printf("Waiting for a incoming connection...\n");
  if ((clientd = accept(serverd, (struct sockaddr*) &ca, &size)) < 0) {
    printf("%s ", prog);
    perror("accept()");
    return 1;
  }

  struct name buffer;
  //buffer.tok[0] = "hello.c";
  //buffer.tok[1] = "hello.c";  
  //buffer.count = 2;
 // buffer.status = 1;
  char buff[MAXBUFF];  /* message buffer */
  int ret;  /* return value from a call */
  if ((ret = recv(clientd, buff, MAXBUFF-1, 0)) < 0) {
    printf("%s ", prog);
    perror("recv()");
    return 1;
  }

  buff[ret] = '\0';  // add terminating nullbyte to received array of char
  printf("Received message (%d chars):\n%s\n", ret, buff);
  //printf("%s\n", envp);
  
 
 // buffer.tok = buff;
  read_name(&buffer, envp, buff);

  if ((ret = close(clientd)) < 0) {
    printf("%s ", prog);
    perror("close(clientd)");
    return 1;
  }
  if ((ret = close(serverd)) < 0) {
    printf("%s ", prog);
    perror("close(serverd)");
    return 1;
  }
  return 0;
}
