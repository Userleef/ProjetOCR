#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../Tools/Image_Tools.h"

//Transfom the image in a grey scale
void grayScale(SDL_Surface *surface)
{
  //Variables
  int w;
  int h;
  w = surface -> w;
  h = surface -> h;
  Uint8 r, g, b;

  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      r = 0.3* r + 0.59 * g + 0.11 * b;
      g = 0.3* r + 0.59 * g + 0.11 * b;
      b = 0.3* r + 0.59 * g + 0.11 * b;
      Uint32 pix = SDL_MapRGB(surface -> format, r, g, b);
      put_pixel(surface, i, j, pix);
    }
  }
}

//Each pixel is transformed in a pixel black or white
void binaryColor(SDL_Surface *surface)
{
  //Variables
  int w;
  int h;
  w = surface -> w;
  h = surface -> h;
  Uint8 r, g, b;

  for (int i = 0; i < w; i++)
  {
    for (int j = 0; j < h; j++)
    {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r >= 128)
      {
        Uint32 pix = SDL_MapRGB(surface -> format, 255, 255, 255);
        put_pixel(surface, i, j, pix);
      }

      else
      {
        Uint32 pix = SDL_MapRGB(surface -> format, 0, 0, 0);
        put_pixel(surface, i, j, pix);
      }
    }
  }
}
