#include <stdio.h>
#include <stdlib.h>
#define MAXTOKS

struct name {
  char **tok;
  int count;
  int status;
};

int read_name(struct name* input) {
  
  input -> tok = malloc(MAXTOKS sizeof(char *));
  char *line; 
  size_t size;
  size_t chars;
  chars = getline(&line, &size, stdin);
  input -> tok[0] = line;
  enum status_value { NORMAL, EOF_OR_ERROR };
  if (chars == -1) {
    input -> status = EOF_OR_ERROR;
  }
  else {
    input -> status = NORMAL;
    printf("%zu characters were read.\n", chars-1); 
    printf("you typed : %s \n", input->tok[0]);    
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
