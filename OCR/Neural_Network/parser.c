#include <stdio.h>
#include "parser.h"
#include <stdlib.h>

void parser(float T[28 * 28], char *path)
{
  int caractereActuel = 0;
  FILE* txt = fopen(path, "r");
  int i = 0;
  if (txt != NULL)
  {
    while (i < 28 * 28)
    {
      caractereActuel = fgetc(txt); // On lit le caractère
      if(caractereActuel != 10)
      {
        T[i] = caractereActuel - 48;
        i++;
      }
    }
  }
  fclose(txt);
}
