#include "main.h"

int main()
{
    SDL_Surface* surface = IMG_Load("./Image_Test/fleur.jpg");

    grayScale(surface);
    binaryColor(surface);

    //findLine(surface);
    VH(surface);
    //findBloc(surface);
    //lineCut(surface);
    //charcut(surface);

    display(surface);

    //isolateChar(surface);

    return 0;
}
