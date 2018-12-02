#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../Tools/Image_Tools.h"
#include "../Tools/display.h"
#include "Treatment.h"

void lineCut(SDL_Surface *img);
void charcut(SDL_Surface *surface);
char * isolateChar(SDL_Surface *surface);
int is_blank(SDL_Surface *surface, int x1, int x2, int y1, int y2);
int is_space(SDL_Surface *surface, int x1, int x2, int y1, int y2, int average);
int space_average(SDL_Surface *surface, int y1);
int count_black(SDL_Surface *surface);

void lineCut(SDL_Surface *surface)
{
  //Variables
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
          if(i > 0){
            pixel = SDL_MapRGB(surface -> format, 255, 0, 0);
            put_pixel(surface, k, i - 1, pixel);
          }
          else
          {
            pixel = SDL_MapRGB(surface -> format, 255, 0, 0);
            put_pixel(surface, k, i , pixel);
          }
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

//Separate each character of each line
void charcut(SDL_Surface *surface)
{
  //Variables
  Uint32 pixel;
  Uint8 r, g , b;
  int lineTop;
  int lineBot;
  int haveBlack = -1;
  int isInchar = -1;

  for(int j = 0 ; j < surface -> h; j++)
  {
    pixel = getpixel(surface, 0, j);
    SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

    if( b == 255 && g == 0 && r == 0)
    {
      lineTop = j;
      j++;
      pixel = getpixel(surface, 0, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      while(j < surface -> h && (b != 255 || g != 0 || r != 0))
      {
        pixel = getpixel(surface, 0, j);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
        j++;
      }

      lineBot = j - 1;
      j--;

      if(lineTop != -1)
      {
        for(int i = 0 ; i < (surface -> w); i++)
        {
          haveBlack = -1;
          for(int h = lineTop ; h <= lineBot; h++)
          {
            pixel = getpixel(surface, i, h);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

            if( b == 0 && g == 0 && r == 0)
            {
              haveBlack = 0;
            }

            if( b == 0 && g == 0 && r == 0 && isInchar != 0)
            {
              haveBlack = 0;
              isInchar = 0;
              pixel = SDL_MapRGB(surface -> format, 0, 0, 255);

              for(int k = lineTop ; k < surface -> h && k <= lineBot; k++)
              {
                put_pixel(surface, i-1, k, pixel);
              }

              pixel = SDL_MapRGB(surface -> format, 0, 255, 0);
              put_pixel(surface, i-1, lineTop, pixel);
              put_pixel(surface, i-1, lineBot, pixel);
            }
          }

          if(haveBlack != 0 && isInchar == 0)
          {
            isInchar = -1;
            pixel = SDL_MapRGB(surface -> format, 0, 0, 255);

            for(int k = lineTop ;k < surface -> h &&  k <= lineBot; k++)
            {
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

//Identify each character of of a text
char * isolateChar(SDL_Surface *surface)
{
  //Variables
  Uint32 pixel;
  Uint8 r, g , b;
  int x1,x2,y1,y2;
  int save = 0;
  char *result = concat("", "");

  for(int i = 0; i < (surface -> h) ; i++)
  {
    save = y2;
    pixel = getpixel(surface, 0, i);
    SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

    if(b == 255 && g == 0 && r == 0)
    {
      int average = space_average(surface, i);

      for(int j = 0 ; j < (surface -> w); j++)
      {
        pixel = getpixel(surface, j, i);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

        if(r == 0 && g == 255 && b == 0)
        {
          x1 = j;
          y1 = i;
          j++;
          r = 2;

          while(j < surface -> w && (r != 0 || g != 255 || b != 0))
          {
            pixel = getpixel(surface, j, i);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
            j++;
          }

          if(j >= surface -> w)
          {
            break;
          }

          j--;
          int t = i ;
          t++;
          r = 2;

          while(t < surface -> h && (r != 0 || g != 255 || b != 0))
          {
            pixel = getpixel(surface, j, t);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
            t++;
          }

          x2 = j;
          y2 = t;
          j--;
          SDL_Surface* character = copy_image(surface,x1,x2,y1,y2);

          if(is_space(surface,x1,x2,y1,y2,average)){
            printf("SPACE\n");
            append(&result," ");
          }
          else
          {
            if(!is_blank(surface,x1,x2,y1,y2))
            {
              printf("---Char :\n");
              int matrice[(character -> h) * (character -> w)];
              character = resize(character, 28, 28);
              surface_matrice(character, character->h, character->w, matrice);
              //print_matrice(character -> h, character -> w, matrice);
              int T[28 * 28];
              resize_char(character -> h, character -> w, matrice, T);
              print_matrice(28, 28, T);
              
              if(count_black(character) <= 10)
              {
                append(&result,".");
                printf("---Point\n");
              }
              else
              {
                append(&result,"c");
              }

              //display(character);
              printf("----\n");

            }
          }

          //display(character);
        }
      }

      append(&result,"\n");

      printf("\\n\n");
    }

    if( y2 != save)
    {
        i = y2;
    }
  }

  return result;
}

int count_black(SDL_Surface *surface)
{
  //Variables
  Uint32 pixel;
  Uint8 r, g , b;
  int Black = 0;

  for(int i = 0;i < surface -> w; i++)
  {
    for(int j = 0;j < surface -> h; j++)
    {
      pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r == 0 && g == 0 && b == 0)
      {
        Black++;
      }
    }
  }

  return Black;
}

//Boolean that determine if a detected area is a not a character
int is_blank(SDL_Surface *surface, int x1, int x2, int y1, int y2)
{
  //Variables
  Uint32 pixel;
  Uint8 r, g , b;

  for(int i = x1;i < surface -> w && i < x2; i++)
  {
    for(int j = y1;j < surface -> h && j < y2; j++)
    {
      pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      if(r == 0 && g == 0 && b == 0)
      {
        return 0;
      }
    }
  }

  return 1;
}

//Bolean that determine if a blank area is a space
int is_space(SDL_Surface *surface, int x1, int x2, int y1, int y2, int average)
{
  if(x2 - x1 < average){
    return 0;
  }

  return is_blank(surface, x1, x2, y1, y2) == 1;
}

//Calculate an average for differantiate
int space_average(SDL_Surface *surface, int y1)
{
  //Variables
  Uint32 pixel;
  Uint8 r, g , b;
  r = 2;
  int y2 = y1 + 1;
  int x1,x2;
  int totalBlank = 0;
  int sum_blank_size = 0;

  while(y2 < surface -> h && (b != 255 || g != 0 || r != 0))
  {
      pixel = getpixel(surface, 0, y2);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      y2++;
  }

  for(int i = 0; i < surface -> w; i++)
  {
    pixel = getpixel(surface, i, y1);
    SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

    if(r == 0 && g == 255 && b == 0)
    {
      x1 = i;
      i++;
      r = 2;

      while(i < surface -> w && (r != 0 || g != 255 || b != 0))
      {
        pixel = getpixel(surface, i, y1);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
        i++;
      }

      if(i >= surface -> w)
      {
        break;
      }

      x2 = i;

      if(is_blank(surface,x1,x2,y1,y2) == 1)
      {
        totalBlank += 1;
        sum_blank_size += x2 - x1;
      }
    }
  }

  if(totalBlank != 0)
  {
    return sum_blank_size / totalBlank;
  }

  return 0;
}
