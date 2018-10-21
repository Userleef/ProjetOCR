#include "main.h"

int main()
{
  char path[30] = "./Image_Test/grand.png";
  SDL_Surface* surface = IMG_Load(path);

  grayScale(surface);
  binaryColor(surface);
  display(surface);
  VH(surface);
  findBloc_H(surface);
  display(surface);
  //findBloc_V(surface);
  lineCut(surface);
  display(surface);
  charcut(surface);

  display(surface);

  isolateChar(surface);

  apply_xor();

  return 0;
}
