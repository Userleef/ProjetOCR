#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img,int x1, int x2, int y1, int y2);
void pause();
void displayPicture(SDL_Surface *surface);


Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
 int bpp = surf -> format -> BytesPerPixel;
 return (Uint8*)surf -> pixels + y * surf -> pitch + x * bpp;
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

SDL_Surface* copy_image(SDL_Surface *img,int x1, int x2, int y1, int y2)
{
  Uint32 pixel;
  SDL_Surface* copy;
  x2++;

  copy = SDL_CreateRGBSurface(SDL_HWSURFACE,
                              x2 - x1,
                              y2 - y1,
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

void surface_matrice(SDL_Surface *surface,int h, int w, int matrice [h][w]){
  Uint32 pixel;
  Uint8 r, g, b;

  for(int i = 0;  i < h; i++)
  {
    for(int j = 0; j < w; j++)
    {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);

      if(r == 0 && g == 0 && b == 0){
        matrice[i][j] = 1;
      }else{
        matrice[i][j] = 0;
      }
    }
  }
}

void print_matrice( int h, int w, int T[h][w])
{ 
   int i, j ; 
   for ( i = 0 ; i < h ; ++i ) 
   { 
      for ( j = 0 ; j < w ; ++j ){
        printf( "%5d", T[i][j] ) ;
      }
      printf("\n");
   } 
   printf( "\n" ) ; 
} 