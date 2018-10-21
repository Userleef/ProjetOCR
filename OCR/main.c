#include "main.h"

int main()
{
  char path[30] = "./Image_Test/ocr.png";
  SDL_Surface* surface = IMG_Load(path);

  grayScale(surface);
  binaryColor(surface);

  VH(surface);
  findBloc_H(surface);
  //findBloc_V(surface);
  lineCut(surface);
  charcut(surface);

  display(surface);

  isolateChar(surface);

  return 0;
}
