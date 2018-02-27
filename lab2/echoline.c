#include <stdio.h>
#include <stdlib.h>
#define MAXTOKS


struct name {
  char **tok;
  int count;
  int status;
};


int read_name(struct name* input) {
  
  int N = 0;
  // input -> tok = malloc((N+1)* sizeof(char**));
  input -> tok = malloc(MAXTOKS sizeof(char **));
  char *line; 
  size_t size;
  size_t chars;
  
  // int N = 0;
  //  int i = 0;
  chars = getline(&line, &size, stdin);
  //  input -> tok[0] = malloc((N+1)* sizeof(char));
  while(!isspace(line[N])){
    N++;
    input -> tok[0] = malloc((N+1)* sizeof(char));
  }  
 
  int i = 0;
  while(i < N+1){
    input -> tok[0] = &line[i]; 
    i++;
    input -> tok[N+1] == NULL;
  }
  // input -> tok[N+1] == NULL;
 
  
  enum status_value { NORMAL, EOF_OR_ERROR };
  if (chars == -1) {
    input -> status = EOF_OR_ERROR;
  }
  else {
    input -> status = NORMAL;
    printf("%zu characters were read.\n", chars-1); 
    printf("you typed : %s \n", line);    
  }
  if (input -> status = NORMAL) 
    return 1;
  else
    return 0;
}


int main()
{
  struct name buffer;
  read_name(&buffer);
}
