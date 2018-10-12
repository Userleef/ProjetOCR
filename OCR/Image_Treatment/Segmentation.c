#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../Tools/Image_Tools.h"

void colorLine(SDL_Surface * surface, int x, int y,int x_Max);
void findBeginLine
(SDL_Surface * surface, int x_begin, int y_begin, int* px_Min, int* py_Min);
int findNextBlankLine(SDL_Surface * surface, int begin);
void findEndLine
(SDL_Surface * surface, int x_begin, int y_begin, int *x_Max, int *y_Min);
void findBloc_H(SDL_Surface * surface);
void findBloc(SDL_Surface * surface);
void clear_H(SDL_Surface * surface);
void clear_V(SDL_Surface * surface);

int averagePixelBlocLine(SDL_Surface * surface, int line){
  int w = surface -> w;
  int h = surface -> h;

  Uint8 r, g, b;

  int WhitePixels = 0;
  int ColorPixels = 0;

  for (int j = 0; j < w; j++)
  {
    Uint32 pixel = getpixel(surface, j, line);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r != 255 || g != 255 || b != 255){
      ColorPixels += 1;
    }
    if(r == 255 && g == 255 && b == 255){
      WhitePixels += 1;
    }

  }

  if(ColorPixels / 2 != 0){
      return WhitePixels / (ColorPixels / 2);
  }

  return 0;
}

int averagePixelBlocColumn(SDL_Surface * surface, int column){
  int w = surface -> w;
  int h = surface -> h;

  Uint8 r, g, b;

  int WhitePixels = 0;
  int ColorPixels = 0;

  for (int j = 0; j < h; j++)
  {
    Uint32 pixel = getpixel(surface, column, j);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r != 255 || g != 255 || b != 255){
      ColorPixels += 1;
    }
    if(r == 255 && g == 255 && b == 255){
      WhitePixels += 1;
    }

  }

  if(ColorPixels / 2 != 0){
      return WhitePixels / (ColorPixels / 2);
  }

  return 0;
}

int averagePixelLine(SDL_Surface * surface, int line){
  int w = surface -> w;
  int h = surface -> h;

  Uint8 r, g, b;

  int WhitePixels = 0;
  int BlackPixels = 0;

  for (int j = 0; j < w; j++)
  {
    Uint32 pixel = getpixel(surface, j, line);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r == 0 && g == 0 && b == 0){
      BlackPixels += 1;
    }
    if(r == 255 && g == 255 && b == 255){
      WhitePixels += 1;
    }

  }

  if(BlackPixels / 2 != 0){
      return WhitePixels / (BlackPixels / 2);
  }

  return 0;
}

int averagePixelColumn(SDL_Surface * surface, int column){
  int w = surface -> w;
  int h = surface -> h;

  Uint8 r, g, b;

  int WhitePixels = 0;
  int BlackPixels = 0;

  for (int j = 0; j < h; j++)
  {
    Uint32 pixel = getpixel(surface, column, j);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r == 0 && g == 0 && b == 0){
      BlackPixels += 1;
    }
    if(r == 255 && g == 255 && b == 255){
      WhitePixels += 1;
    }

  }

  if(BlackPixels / 2 != 0){
      return WhitePixels / (BlackPixels / 2);
  }

  return 0;

    

}

void clear_H(SDL_Surface * surface){
  int w = surface -> w;
  int h = surface -> h;

  int average;
  int blank;

  Uint8 r, g, b;

  for (int i = 0; i < h; i++)
  {
    average = averagePixelBlocLine(surface, i) * 8;
    blank = -1;

    for (int j = 0; j < w; j++)
    {
      Uint32 pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);

      if(r != 255 || g != 255 || b != 255){
        if(blank != -1){
          blank++;
        }
      }else{
        
        if(blank <= average){
          int k = j - 1;
          while(blank > 0){
            Uint32 pixel = getpixel(surface, k, i);
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            if(r!= 0 || g != 0 || b != 0){
              Uint32 pix = SDL_MapRGB(surface->format, 255, 255, 255);
              put_pixel(surface, k, i , pix);
            }
            blank--;
            k--;
          }
        }

        blank = 0;

      }
    }
  }
}

void clear_V(SDL_Surface * surface){
  int w = surface -> w;
  int h = surface -> h;

  int average;
  int blank;

  Uint8 r, g, b;

  for (int i = 0; i < w; i++)
  {
    average = averagePixelBlocColumn(surface, i) * 1.8;
    blank = -1;

    for (int j = 0; j < h; j++)
    {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);

      if(r != 255 || g != 255 || b != 255){
        if(blank != -1){
          blank++;
        }
      }else{
        
        if(blank <= average){
          int k = j - 1;
          while(blank > 0){
            Uint32 pixel = getpixel(surface, i, k);
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            if(r!= 0 || g != 0 || b != 0){
              Uint32 pix = SDL_MapRGB(surface->format, 255, 255, 255);
              put_pixel(surface, i, k , pix);
            }
            blank--;
            k--;
          }
        }

        blank = 0;

      }
    }
  }
}

void findBloc_H(SDL_Surface * surface){
  int w = surface -> w;
  int h = surface -> h;

  int average;
  int blank;

  Uint8 r, g, b;

  for (int i = 0; i < h; i++)
  {
    average = averagePixelLine(surface, i)*8;
    blank = -1;

    for (int j = 0; j < w; j++)
    {
      Uint32 pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);

      if(r == 255 && g == 255 && b == 255){
        if(blank != -1){
          blank++;
        }
      }else{
        
        if(blank <= average){
          int k = j - 1;
          while(blank > 0){
            Uint32 pix = SDL_MapRGB(surface->format, 0, 0, 255);
            put_pixel(surface, k, i , pix);
            blank--;
            k--;
          }
        }

        blank = 0;

      }
    }
  }
}

void findBloc_V(SDL_Surface * surface){
  int w = surface -> w;
  int h = surface -> h;

  int average;
  int blank;

  Uint8 r, g, b;

  for (int i = 0; i < w; i++)
  {
    average = averagePixelColumn(surface, i) * 4;
    blank = -1;
    

    for (int j = 0; j < h; j++)
    {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);


      if(r == 255 && g == 255 && b == 255){
        if(blank != -1){
          blank++;
        }
      }else{
        
        if(blank <= average){
          int k = j - 1;
          while(blank > 0){
            Uint32 pix = SDL_MapRGB(surface->format, 0, 0, 255);

            put_pixel(surface, i, k , pix);
            blank--;
            k--;
          }
        }

        blank = 0;

      }
    }
  }
}

void findLine(SDL_Surface * surface){
  int w = surface -> w;
  int h = surface -> h;

  int x_Min;
  int y_Min;
  int x_Max;

  findBeginLine(surface,0,0,&x_Min, &y_Min);
  findEndLine(surface,0,0,&x_Max, &y_Min);

  Uint8 r, g, b;

  int HaveBlack = 0;

  for (int i = y_Min; i < h; i++)
  {
    for (int j = x_Min; j < w; j++)
    {

      Uint32 pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);

      if(r == 0){
        HaveBlack = 1;
        break;
      }
    }
    if(HaveBlack == 1){
      colorLine(surface,x_Min,i,x_Max);
    }
    else{
      findBeginLine(surface,0,i,&x_Min, &y_Min);
      findEndLine(surface,0,i,&x_Max, &y_Min);
          // printf("x_Min : %d\n",x_Min);
           // printf("y_Min : %d\n",y_Min);
          // printf("x_Max : %d\n",x_Max);
    }
    HaveBlack = 0;
  }
}

/*
void findChar(SDL_Surface * surface){
  int w = surface -> w;
  int h = surface -> h;

  int x_Min;
  int y_Min;
  int x_Max;

  Uint8 r, g, b;

  int HaveBlack = 0;

  findBeginLine(surface,0,0,&x_Min, &y_Min);
  findEndLine(surface,0,0,&x_Max, &y_Min);

  for(int i = x_Min; i < x_Max; i++){
      for(int j = y_Min; j < y_)
  }
}*/

void findBeginLine
(SDL_Surface * surface, int x_begin, int y_begin, int *x_Min, int *y_Min){

    int w = surface -> w;
    int h = surface -> h;

    Uint8 r, g, b;
    Uint32 pixel;

    int found = 0;
    for (int i = y_begin; i < h && found == 0; i++) {
      for (int j = x_begin; j < w && found == 0; j++) {
        pixel = getpixel(surface, j, i);
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);
        if (r == 0){
          found = 1;
          *y_Min = i;
        }
      }
    }

    int y_end = findNextBlankLine(surface, *y_Min);
    // printf("y_end : %d\n",y_end);

    found = 0;
    for (int i = x_begin; i < w && found == 0; i++) {
      for (int j = y_begin; j < y_end && found == 0; j++) {
        pixel = getpixel(surface, i, j);
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);
        if (r == 0){
          found = 1;
          *x_Min = i;
        }
      }
    }

}

void findEndLine
(SDL_Surface * surface, int x_begin, int y_begin, int *x_Max, int *y_Min){

    int w = surface -> w;
    int h = surface -> h;

    Uint8 r, g, b;
    Uint32 pixel;

    int found = 0;
    for (int i = y_begin; i < h && found == 0; i++) {
      for (int j = x_begin; j < w && found == 0; j++) {
        pixel = getpixel(surface, j, i);
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);
        if (r == 0){
          found = 1;
          *y_Min = i;
        }
      }
    }

    int y_end = findNextBlankLine(surface, *y_Min);
    // printf("y_end : %d\n",y_end);

    found = 0;
    for (int i = w - 1; i > 0 && found == 0; i--) {
      for (int j = y_begin; j < y_end && found == 0; j++) {
        pixel = getpixel(surface, i, j);
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);
        if (r == 0){
          found = 1;
          *x_Max = i;
        }
      }
    }

}

int findNextBlankLine(SDL_Surface *surface, int begin){
  // printf("begin : %d\n",begin);
  int w = surface -> w;
  int h = surface -> h;

  Uint8 r, g, b;
  Uint32 pixel;

  int HaveBlack = 0;

  for (int i = begin; i < h; i++) {
    for (int j = 0; j < w; j++) {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);
      if(r == 0){
        HaveBlack = 1;
        break;
      }
    }
    if(HaveBlack == 0){
      return i;
    }
    HaveBlack = 0;
    }
  return begin;
}


void colorLine(SDL_Surface * surface, int x_Min, int y,int x_Max){

    Uint8 r, g , b;

    for (int i = x_Min; i <= x_Max; i++) {
      Uint32 pixel = getpixel(surface, i, y);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);
      if(r == 255){
        Uint32 pix = SDL_MapRGB(surface->format, 255, 0, 0);
        put_pixel(surface, i, y , pix);
      }
    }
}
