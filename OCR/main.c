#include "main.h"


void pause();
void displayPicture(SDL_Surface *surface);


int main(int argc, char *argv[])
{
    SDL_Surface *surface = NULL;
    //surface = SDL_LoadBMP("./Image_Test/lac_en_montagne.bmp");
    surface = IMG_Load("./Image_Test/test2.png");

    grayScale(surface);
    binaryColor(surface);

    findBloc(surface);

    displayPicture(surface);

    return EXIT_SUCCESS;

}

void displayPicture(SDL_Surface *surface){
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
