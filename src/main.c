#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"

int main(int argc, char **argv)
{
  IS is;
  int i;

  /* Open the file as an inputstruct.  Error check. */
  is = new_inputstruct(NULL);
  if (is == NULL)
  {
    perror(argv[1]);
    exit(1);
  }

  /* Read each line with get_line().  Print out each word. */
  while (get_line(is) >= 0)
  {
    for (i = 0; i < is->NF; i++)
    {
      printf("%d: %s\n", is->line, is->fields[i]);
    }
  }

  jettison_inputstruct(is);
  return 0;
}
