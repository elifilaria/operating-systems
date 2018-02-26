#include <stdio.h>
#include <stdlib.h>


int main()
{
    char *line;
    size_t size;
    size_t chars;

    printf("Type something: ");
    line = (char *)malloc(size * sizeof(char));
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

