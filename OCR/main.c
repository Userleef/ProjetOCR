#include "main.h"

int main()
{
  char path[30] = "./Image_Test/archi.png";
  SDL_Surface* surface = IMG_Load(path);

  grayScale(surface);
  binaryColor(surface);
  display(surface);
  VH(surface);
  findBloc_H(surface);
  display(surface);
  /*lineCut(surface);
  display(surface);
  charcut(surface);
  display(surface);
  isolateChar(surface);
  display(surface);*/


  Uint32 pixel;
  Uint8 r, g, b;
  int x = 0;
  int y = 0;
  for (int i = 0; i < surface -> w && !x; i++) {
    for (int j = 0; j < surface -> h && !x; j++) {
      pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      if(r == 0 && g == 0 && g == 0)
      {
        x = i;
        y = j;
      }
    }
  }
  printf("%d, %d\n",x , y);
  int xmin1 = x;
  int xmax1 = x;
  int ymin1 = y;
  int ymax1 = y;
  neigh(surface, x, y, &xmin1, &xmax1, &ymin1, &ymax1);

  SDL_Surface* img = copy_image(surface, xmin1, xmax1, ymin1, ymax1);
  display(img);
  //findBloc_V(surface);
  //lineCut(surface);
  //charcut(surface);
  //isolateChar(surface);

  return 0;
}
