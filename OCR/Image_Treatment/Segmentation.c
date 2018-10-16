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

void lineCut(SDL_Surface *img);
void charcut(SDL_Surface *surface);
void isolateChar(SDL_Surface * surface);

int averagePixelBlocLine(SDL_Surface * surface, int line){
  int w = surface -> w;

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
    average = averagePixelLine(surface, i)*4;
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
            Uint32 pix = SDL_MapRGB(surface->format, 180, 200, 255);
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
            Uint32 pix = SDL_MapRGB(surface->format, 180, 200, 255);

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


/* Cut the lines of the image */
void lineCut(SDL_Surface *surface)
{
    /* Variables */
    Uint32 pixel;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    int isBlank = 1;
    int firstCut = 1;

    for(int i = 0; i < (surface -> h) ; i++)
    {
      isBlank = 1 ;
      for(int j = 0 ; j < (surface -> w); j++)
      {
        pixel = getpixel(surface, j, i);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
        //Check if there is a black character in this line
        if(!r && !g && !b)
        {
          isBlank = 0;
          break;
        }
      }
      //For the first cut we cut the pixel line
      //before the line with a black character
      if(!isBlank && firstCut)
      {
          for(int k = 0; k < (surface -> w); k++)
          {
            pixel = SDL_MapRGB(surface -> format, 255, 0, 0);
            put_pixel(surface, k, i - 1, pixel);
          }
          firstCut = 0;
      }
      //For the second cut we cut the first white line
      if(isBlank && !firstCut)
      {
        for(int k = 0; k < (surface -> w); k++)
        {
          pixel = SDL_MapRGB(surface -> format, 255, 0, 0);
          put_pixel(surface, k, i, pixel);
        }
        firstCut = 1;
      }
    }
}

void charcut(SDL_Surface *surface){
  /* Variables */
  Uint32 pixel;
  Uint8 r, g , b;

  int lineTop;
  int lineBot;

  int haveBlack = -1;
  int isInchar = -1;

  for(int j = 0 ; j < surface -> h; j++)
  {
    pixel = getpixel(surface, 0, j);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if( b == 255 && g == 0 && r == 0){
      lineTop = j;
      j++;
      pixel = getpixel(surface, 0, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      while(b != 255 || g != 0 || r != 0)
      {
        pixel = getpixel(surface, 0, j);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
        j++;
      }

      lineBot = j - 1;
      j--;

      if(lineTop != -1){
        for(int i = 0 ; i < (surface -> w); i++){
          haveBlack = -1;
          for(int h = lineTop ; h <= lineBot; h++){
            pixel = getpixel(surface, i, h);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

            if( b == 0 && g == 0 && r == 0){
              haveBlack = 0;
            }

            if( b == 0 && g == 0 && r == 0 && isInchar != 0){
              haveBlack = 0;
              isInchar = 0;

              pixel = SDL_MapRGB(surface -> format, 0, 0, 255);
              for(int k = lineTop ; k <= lineBot; k++){
                put_pixel(surface, i-1, k, pixel);
              }

              pixel = SDL_MapRGB(surface -> format, 0, 255, 0);
              put_pixel(surface, i-1, lineTop, pixel);
              put_pixel(surface, i-1, lineBot, pixel);
            }
          }

          if(haveBlack != 0 && isInchar == 0){
            isInchar = -1;

            pixel = SDL_MapRGB(surface -> format, 0, 0, 255);
            for(int k = lineTop ; k <= lineBot; k++){
                put_pixel(surface, i, k, pixel);
            }

            pixel = SDL_MapRGB(surface -> format, 0, 255, 0);
            put_pixel(surface, i, lineTop, pixel);
            put_pixel(surface, i, lineBot, pixel);
          }

        }

    }

    }

  }

}


void isolateChar(SDL_Surface * surface){

  Uint32 pixel;
  Uint8 r, g , b;
  int x1,x2,y1,y2;
  int save = 0;

  for(int i = 0; i < (surface -> h) ; i++)
    {
      save = y2;
      for(int j = 0 ; j < (surface -> w); j++)
      {
        pixel = getpixel(surface, j, i);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

        printf("%d,%d,%d\n",r,g,b);

        if(r == 0 && g == 255 && b == 0){
          printf("---0---\n");
          x1 = j;
          y1 = i;

          j++;
          pixel = getpixel(surface, j, i);
          SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

          while(r != 0 || g != 255 || b != 0){
            pixel = getpixel(surface, j, i);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
            j++;
          }
          j--;


          printf("---1---\n");

          int t = i ;
          t++;
          pixel = getpixel(surface, j, t);
          SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

          while(r != 0 || g != 255 || b != 0){
            pixel = getpixel(surface, j, t);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
            t++;
          }

          x2 = j;
          y2 = t;

          printf("---2---\n");

          printf("coords : %d,%d--%d,%d\n",x1,y1,x2,y2);
          printf("---3---\n");

          SDL_Surface* character = copy_image(surface,x1,x2,y1,y2);
          printf("---4---\n");

          displayPicture(character);
        }
      }

      if( y2 != save){
          i = y2;
      }
    }
}
