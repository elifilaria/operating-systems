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
#include <string.h>
//#include "copyfile.c"
#include <time.h>
#define MAXBUFF 100
#define MAXTOKS 100

struct name {
  char **tok;
  int count;
  int status;
};
enum status_value { NORMAL, EOF_OR_ERROR, TOO_MANY_TOKENS };

int main(int argc, char **argv, char **envp) {

  char *prog = argv[0];
  int port;
  int serverd;  /* socket descriptor for receiving new connections */
  FILE *pFile2;
  time_t now;
  char timestamp[30];
  now = time(NULL);

  pFile2 = fopen("log.txt", "a");
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
  while(1){
  printf("Waiting for a incoming connection...\n");
  if ((clientd = accept(serverd, (struct sockaddr*) &ca, &size)) < 0) {
    printf("%s ", prog);
    perror("accept()");
    return 1;
  }
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
  if(pFile2 == NULL)
    perror("Error appending to file.\n");
  else{
    //printf("%s\n", "yayyy");
    fprintf(pFile2, "%s ", buff);
    //printf("%s\n", "still yayyy");
}
  if(strftime(timestamp, 30, "%a, %d %b %Y %T %Z", gmtime(&now)) == 0)
    printf("Error getting the timestamp\n");
  else
    fprintf(pFile2, "%s\n", timestamp);
 
 //printf("blah blhauhygvt");
 // buffer.tok = buff;
  //struct name *input;
  buffer . tok = malloc(MAXTOKS* sizeof(char *));
  //char *buffer5 = NULL;
  size_t buffsize = 0;
  size_t chars;

  chars = strlen(buff);//getline(&buffer, &buffsize, stdin);
  buffsize = chars;

  int N = 0;
  int N0 = 0;
  int i;
  int j;

  for (i = 0; i < chars; i++)
  {
    if (isspace(buff[i]) || buff[i] == '\0')
    {
      if(N != 0)
      {
        if (i == '\0')
          N++;
        if(N0 >= MAXTOKS)
        {
          buffer . status == TOO_MANY_TOKENS;
          break;
        }
        buffer . tok[N0] = malloc((N+1) * sizeof(char));

        for(j = 0; j < N; j++)
        {
          char cc;
          if(i == '\0')
            cc = buff[i-N+j+1];
          else
            cc = buff[i-N+j];
          buffer . tok[N0][j] = cc;
        }
        buffer . tok[N0][N] = 0;
        N0++;
      }
      N = 0;
      continue;
    }
    N++;
  }
  buffer . count = N0;
  buffer . tok[N0+1] = "\0";


  if(chars == -1)
  {
    if (buffer . tok[0][0] == 4)
    {
      buffer . status = EOF_OR_ERROR;
      printf("You have entered too many tokens\n");
    }

  }
  else if (N0 >= MAXTOKS)
  {
    buffer . status = EOF_OR_ERROR;
    printf("There was an error.\n");
  }
  else {
      buffer . status = NORMAL;
  }

//printf("blah blha");
  execve(buffer . tok[0], buffer . tok, envp);
//printf("blah blha3");
   FILE *pFile1;
//   char *buffbuff;
   i = 0;
 //  FILE *pFile2;
   char *buff7 = NULL;
   size_t bufflen = 0; 
   //printf("%s\n", input.tok[0][0]);

   pFile1 = fopen(buffer.tok[1], "r");
   //printf("%s\n", input.tok[0]);
   //pFile2 = fopen(input.tok[1], "w");
   if (pFile1 == NULL) 
     perror ("Error opening file.\n");
   //else if (pFile2 == NULL) 
     //perror ("Error opening second file.\n");
   else {
    while (getline(&buff7, &bufflen, pFile1) >= 0){
      //printf("blah blha");
      fprintf(stdout, "%s\n", buff7);
    //  printf("is this working?");
      if ((ret = send(clientd, buff7, MAXBUFF-1, 0)) < 0) {
       // printf("lalalallala");
        printf("%s ", buff7);/*
        perror("send()");
        return 1;
  }*/
      //printf("different blah");
  }
    fclose(pFile1);
}
}


  /*char *buffbuff = *///read_name(&buffer, envp, buff);
  //printf("%s\n", "heloooooo");


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
  fclose(pFile2);
  return 0;
}