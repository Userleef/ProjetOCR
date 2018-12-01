#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img, int x1, int x2, int y1, int y2);
void pause();
void displayPicture(SDL_Surface *surface);

//Give the pixel with the coordinates x and y for the functions getpixel()
//and put_pixel()
Uint8* pixelref(SDL_Surface *surface, unsigned x, unsigned y)
{
 int bpp = surface -> format -> BytesPerPixel;
 return (Uint8*)surface -> pixels + y * surface -> pitch + x * bpp;
}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
 Uint8 *p = pixelref(surface, x, y);
 return p[0] << 16 | p[1] << 8 | p[2];
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
   Uint8 *p = pixelref(surface, x, y);
   p[2] = (pixel >> 16) & 0xff;
   p[1] = (pixel >> 8) & 0xff;
   p[0] = pixel & 0xff;
}

//Create a matrice of a character
SDL_Surface* copy_image(SDL_Surface *img, int x1, int x2, int y1, int y2)
{
  //Variables
  Uint32 pixel;
  SDL_Surface* copy;
  x2++;
  copy = SDL_CreateRGBSurface(SDL_HWSURFACE, x2 - x1, y2 - y1,
                              img -> format -> BitsPerPixel,0,0,0,0);

  for(int i = x1; i < x2; i++)
  {
    for(int j = y1;j < y2; j++)
    {
      pixel = getpixel(img, i, j);
      put_pixel(copy, i - x1, j - y1, pixel);
    }
  }

  return(copy);
}

void surface_matrice(SDL_Surface *surface,int h, int w, int matrice [h * w])
{
  //Variables
  Uint32 pixel;
  Uint8 r, g, b;

  for(int i = 0;  i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r == 0 && g == 0 && b == 0)
      {
        matrice[i * w +j] = 1;
      }

      else
      {
        matrice[i * w + j] = 0;
      }
    }
  }
}

//Print in the terminal a character
void print_matrice( int h, int w, int T[h * w])
{
   int i, j ;
   for ( i = 0 ; i < h ; ++i )
   {
      for ( j = 0 ; j < w ; ++j )
      {
        printf( "%d", T[i * w + j] ) ;
      }
      printf( "\n" ) ;
   }
   printf( "\n" ) ;
}

void resize_char(int h, int w, int T[h * w], int matrice[28 * 28])
{
  int plhg = (28 - h) / 2;
  int plwg = (28 - w) / 2;

  for (int i = 0; i < plhg; i++)
  {
    for (int j = 0; j < 28; j++)
    {
      matrice[i * 28 + j] = 0;
    }
  }

  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < plwg; j++)
    {
      matrice[(i + plhg) * 28 + j] = 0;
    }
    for (int j = 0; j < w; j++)
    {
      matrice[(i + plhg) * 28 + j + plwg] = T[i * w + j];
    }
    for (int j = w + plwg; j < 28; j++)
    {
      matrice[(i + plhg) * 28 + j] = 0;
    }
  }

  for (int i = h + plhg; i < 28; i++)
  {
    for (int j = 0; j <= 28; j++)
    {
      matrice[i * 28 + j] = 0;
    }
  }
}

void convert_txt_to_array(int T[28 * 28], char *path)
{
  int caractereActuel = 0;
  FILE* txt = fopen(path, "r");
  int i = 0;
  if (txt != NULL)
  {
    while (i < 28 *28)
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
