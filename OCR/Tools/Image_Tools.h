#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
static inline Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);

#endif
