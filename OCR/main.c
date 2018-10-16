#include "main.h"


void pause();
void displayPicture(SDL_Surface *surface);


int main()
{
    SDL_Surface *surface = NULL;
    //surface = SDL_LoadBMP("./Image_Test/lac_en_montagne.bmp");
    surface = IMG_Load("./Image_Test/algo.png");

    grayScale(surface);
    binaryColor(surface);

    findBloc_H(surface);
    findBloc_V(surface);

    clear_H(surface);
    clear_V(surface);

    lineCut(surface);
    charcut(surface);

    //isolateChar(surface);

    //SDL_Surface* test = copy_image(surface,23,18,42,100);
    

    displayPicture(surface);

    return EXIT_SUCCESS;

}

