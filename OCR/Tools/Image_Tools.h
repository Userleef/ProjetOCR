#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img,int x1, int x2, int y1, int y2);
void displayPicture(SDL_Surface *surface);
int surface_matrice(SDL_Surface *surface, int h, int w, int matrice [h][w]);
void print_matrice( int h, int w, int T[h][w]);

#endif
