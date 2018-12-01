#include "main.h"

int main()
{
  char path[30] = "./Image_Test/ocr.png";
  SDL_Surface* surface = IMG_Load(path);

  grayScale(surface);
  binaryColor(surface);
  display(surface);
  lineCut(surface);
  display(surface);
  charcut(surface);
  display(surface);
  isolateChar(surface);

  return 0;
}
