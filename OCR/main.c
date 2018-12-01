#include "main.h"

int main()
{
  char path[30] = "./Image_Test/ocr.png";
  SDL_Surface* surface = IMG_Load(path);

  /*grayScale(surface);
  binaryColor(surface);
  display(surface);
  VH(surface);
  findBloc_H(surface);
  display(surface);
  discover_line(surface);
  lineCut(surface);
  display(surface);
  charcut(surface);
  display(surface);
  isolateChar(surface);*/
  int T[28 * 28];
  convert_txt_to_array(T, "Character/a/0.txt");

  print_matrice(28, 28, T);


  /*Uint32 pixel;
  Uint8 r, g, b;
  int x = 0;
  int y = 0;
  for (int i = 0; i < surface -> h && !x; i++) {
    for (int j = 0; j < surface -> w && !x; j++) {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      if(r == 0 && g == 0 && g == 0)
      {
        x = i;
        y = j;
      }
    }
  }
  int xmin = x;
  int xmax = x;
  int ymin = y;
  int ymax = y;
  neigh(surface, x, y, &xmin, &xmax, &ymin, &ymax);
  printf("%d, %d, %d, %d\n",xmin , xmax, ymin, ymax);

  SDL_Surface* img = copy_image(surface, xmin, xmax, ymin, ymax);
  display(img);*/
  //findBloc_V(surface);
  //lineCut(surface);
  //charcut(surface);
  //isolateChar(surface);

  return 0;
}
