#include <stdio.h>

int main()
{
    char *line;
    size_t size;

    if (getline(&line, &size, stdin) == -1) {
      printf("There is no input.\n");
    }
    else {
      printf("%s\n", line);
    }
    return 0;
}

