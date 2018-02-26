#include <stdio.h>
#include <stdlib.h>

struct name {
  char **tok;
  int count;
  int status;
};

int read_name(struct name* input) {
  char *line;
    size_t size;
    size_t chars;
    chars = getline(&line, &size, stdin);

    if (chars == -1) {
      printf("There is no input.\n");
    }
    else {
      printf("%zu characters were read.\n", chars-1); 
      printf("you typed : %s \n", line);    
    }
    return 0;
}


int main()
{
  struct name buffer;
  read_name(&buffer);

}

