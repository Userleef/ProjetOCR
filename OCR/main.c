#include "main.h"

int main()
{
  char path[30] = "./Image_Test/archi.png";
  SDL_Surface* surface = IMG_Load(path);

  grayScale(surface);
  binaryColor(surface);
  display(surface);
  lineCut(surface);
  display(surface);
  charcut(surface);
  display(surface);

  char * result = isolateChar(surface);

  printf("!!!Result :\n");
  printf("%s", result);
  printf("\n");

  return 0;
}
