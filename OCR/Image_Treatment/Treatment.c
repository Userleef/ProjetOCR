#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "../Tools/Image_Tools.h"

void grayScale(SDL_Surface *surface)
{
  int w;
  int h;
  w = surface -> w;
  h = surface -> h;

  Uint8 r, g, b;
  int s;

  //surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, surface -> format);
  //SDL_LockSurface(surface);

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);
      //s = (r+g+b)/3;
      r = 0.3* r + 0.59 * g + 0.11 * b;
      g = 0.3* r + 0.59 * g + 0.11 * b;
      b = 0.3* r + 0.59 * g + 0.11 * b;
      Uint32 pix = SDL_MapRGB(surface->format, r, g, b);
      put_pixel(surface,i,j,pix);

    }
  }
}
