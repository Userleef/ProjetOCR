#include "main.h"


void pause();
void displayPicture(SDL_Surface *surface);


int main()
{
    SDL_Surface* surface = IMG_Load("./Image_Test/fleur.jpg");

    grayScale(surface);
    binaryColor(surface);

    //findLine(surface);
    VH(surface);
    //lineCut(surface);
    //charcut(surface);

    display(surface);

    //isolateChar(surface);

    return EXIT_SUCCESS;

}

