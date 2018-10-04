#include "main.h"


void pause();


int main(int argc, char *argv[])
{
    SDL_Surface *surface = NULL;
    surface = SDL_LoadBMP("./Image_Test/lac_en_montagne.bmp");
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
