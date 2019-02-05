#ifndef IMAGE_TOOLS_H
#define IMAGE_TOOLS_H

Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y);
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
SDL_Surface* copy_image(SDL_Surface *img,int x1, int x2, int y1, int y2);
void displayPicture(SDL_Surface *surface);
int surface_matrice(SDL_Surface *surface, int h, int w, int matrice [h * w]);
void print_matrice( int h, int w, int T[h * w]);
void resize_char(int h, int w, int T[h * w], float matrice[28 * 28]);
char *concat(char *str1,char *str2);
void append(char **str1, char *str2);
void print_string(char *s);
char* concat2(const char *s1, const char *s2);

#endif
