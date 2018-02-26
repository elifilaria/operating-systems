#include <stdio.h>
#include <stdlib.h>

int input(char *s, int length);

int main()
{
  char *buffer;
  size_t buffsize = 32;
  size_t chars;

  buffer = (char *)malloc(buffsize * sizeof(char));
  if(buffer == NULL)
    {
      perror("Unable to allocate buffer");
      exit(1);
    }

  printf("Please type something: ");
  chars = getline(&buffer, &buffsize, stdin);
  printf("%zu characters were read. \n", chars);
  printf("You typed: %s\n", buffer);
  return(0);
}
