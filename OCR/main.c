#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void pause();
void grayScale(SDL_Surface *surface);

int main(int argc, char *argv[])
{
    SDL_Surface *surface = NULL;
    surface = SDL_LoadBMP("lac_en_montagne.bmp");
    Uint8 r, g, b;
    Uint32 pixel = getpixel(surface, 10, 10);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);
    printf("r: %hhu, g : %hhu, b : %hhu\n", r, g, b);

    grayScale(surface);

  // DISPLAY PICTURE
    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;
    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(surface -> w, surface -> h, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
    imageDeFond = surface;
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    pause();
    SDL_FreeSurface(imageDeFond);
    SDL_Quit();
    return EXIT_SUCCESS;

}

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
{
 Uint8 *p = pixelref(surface, x, y);
 return p[0] << 16 | p[1] << 8 | p[2];
}

static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
 int bpp = surf -> format -> BytesPerPixel;
 return (Uint8*)surf -> pixels + y * surf -> pitch + x * bpp;
}

void pause()
{
    int continuer = 1;
    SDL_Event event;
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
   Uint8 *p = pixelref(surface, x, y);

   p[2] = (pixel >> 16) & 0xff;
   p[1] = (pixel >> 8) & 0xff;
   p[0] = pixel & 0xff;
}

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
