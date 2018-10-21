#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../Tools/Image_Tools.h"
#include "../Tools/display.h"


void findBloc(SDL_Surface *surface);
void findBloc_H(SDL_Surface *surface);
void findBloc_V(SDL_Surface *surface);
void findLine(SDL_Surface *surface);
void lineCut(SDL_Surface *img);
void charcut(SDL_Surface *surface);
void isolateChar(SDL_Surface *surface);
int is_blank(SDL_Surface *surface, int x1, int x2, int y1, int y2);
int is_space(SDL_Surface *surface, int x1, int x2, int y1, int y2, int average);
int space_average(SDL_Surface *surface, int y1);
void VH2(SDL_Surface *surface, SDL_Surface *surface1, SDL_Surface *surface2);

//Calculate the average of the number of pixels colored by
//the RLSA algorithm in a line of pixels
int average_clear_H(SDL_Surface *surface, int line)
{
  //Variables
  int w = surface -> w;
  Uint8 r, g, b;
  int WhitePixels = 0;
  int ColorPixels = 0;

  for (int j = 0; j < w; j++)
  {
    Uint32 pixel = getpixel(surface, j, line);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r != 255 || g != 255 || b != 255)
    {
      ColorPixels += 1;
    }

    if(r == 255 && g == 255 && b == 255)
    {
      WhitePixels += 1;
    }
  }

  if(ColorPixels / 2 != 0)
  {
      return WhitePixels / (ColorPixels / 2);
  }

  return 0;
}

//Calculate the average of the number of pixels colored by
//the RLSA algorithm in a column of pixels
int average_clear_V(SDL_Surface *surface, int column)
{
  //Variables
  int h = surface -> h;
  Uint8 r, g, b;
  int WhitePixels = 0;
  int ColorPixels = 0;

  for (int j = 0; j < h; j++)
  {
    Uint32 pixel = getpixel(surface, column, j);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r != 255 || g != 255 || b != 255)
    {
      ColorPixels += 1;
    }

    if(r == 255 && g == 255 && b == 255)
    {
      WhitePixels += 1;
    }
  }

  if(ColorPixels / 2 != 0)
  {
      return WhitePixels / (ColorPixels / 2);
  }

  return 0;
}

//Calculate the average of the number of black pixel in a line
//of pixels between 2 white pixels
int average_findBloc_H(SDL_Surface *surface, int line)
{
  //Variables
  int w = surface -> w;
  Uint8 r, g, b;
  int WhitePixels = 0;
  int BlackPixels = 0;

  for (int j = 0; j < w; j++)
  {
    Uint32 pixel = getpixel(surface, j, line);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r == 0 && g == 0 && b == 0)
    {
      BlackPixels += 1;
    }

    if(r == 255 && g == 255 && b == 255)
    {
      WhitePixels += 1;
    }
  }

  if(BlackPixels / 2 != 0)
  {
      return WhitePixels / (BlackPixels / 2);
  }

  return 0;
}

//Calculate the average of the number of black pixel in a column
//of pixels between 2 white pixels
int average_findBloc_V(SDL_Surface *surface, int column)
{
  //Variables
  int h = surface -> h;
  Uint8 r, g, b;
  int WhitePixels = 0;
  int BlackPixels = 0;

  for (int j = 0; j < h; j++)
  {
    Uint32 pixel = getpixel(surface, column, j);
    SDL_GetRGB(pixel, surface->format, &r, &g, &b);

    if(r == 0 && g == 0 && b == 0)
    {
      BlackPixels += 1;
    }

    if(r == 255 && g == 255 && b == 255)
    {
      WhitePixels += 1;
    }
  }

  if(BlackPixels / 2 != 0)
  {
      return WhitePixels / (BlackPixels / 2);
  }

  return 0;
}

//Delete the surplus of colored pixels by the RLSA algorithm
//between the paragraphs in each line of pixels
void clear_H(SDL_Surface *surface)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  int average;
  int blank;
  Uint8 r, g, b;

  for (int i = 0; i < h; i++)
  {
    average = average_clear_H(surface, i) *4;
    blank = -1;

    for (int j = 0; j < w; j++)
    {
      Uint32 pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface->format, &r, &g, &b);

      if(r != 255 || g != 255 || b != 255)
      {
        if(blank != -1)
        {
          blank++;
        }
      }
      else
      {
        if(blank <= average)
        {
          int k = j - 1;
          while(blank > 0)
          {
            Uint32 pixel = getpixel(surface, k, i);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
            if(r!= 0 || g != 0 || b != 0)
            {
              Uint32 pix = SDL_MapRGB(surface -> format, 255, 255, 255);
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

//Delete the surplus of colored pixels by the RLSA algorithm
//between the paragraphs in each column of pixels
void clear_V(SDL_Surface *surface)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  int average;
  int blank;
  Uint8 r, g, b;

  for (int i = 0; i < w; i++)
  {
    average = average_clear_V(surface, i) *4;
    blank = -1;

    for (int j = 0; j < h; j++)
    {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r != 255 || g != 255 || b != 255)
      {
        if(blank != -1)
        {
          blank++;
        }
      }
      else
      {
        if(blank <= average)
        {
          int k = j - 1;
          while(blank > 0)
          {
            Uint32 pixel = getpixel(surface, i, k);
            SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
            if(r!= 0 || g != 0 || b != 0)
            {
              Uint32 pix = SDL_MapRGB(surface -> format, 255, 255, 255);
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

//Color the spaces of whites pixels between 2 black pixels with a number of
//pixels inferior of the average in each line of pixels
void findBloc_H(SDL_Surface *surface)
{
  int w = surface -> w;
  int h = surface -> h;
  Uint8 r, g, b;
  int blank;
  int average;

  for (int i = 0; i < h; i++)
  {
    average = average_findBloc_H(surface, i) * 6;
    //average = 10;
    blank = -1;

    for (int j = 0; j < w; j++)
    {
      Uint32 pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r == 255 && g == 255 && b == 255)
      {
        if(blank != -1)
        {
          blank++;
        }
      }
      else
      {
        if(blank <= average)
        {
          int k = j - 1;
          while(blank > 0)
          {
            Uint32 pix = SDL_MapRGB(surface -> format, 150, 200, 255);
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

//Color the spaces of whites pixels between 2 black pixels with a number of
//pixels inferior of the average in each column of pixels
void findBloc_V(SDL_Surface *surface)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  int average;
  int blank;
  Uint8 r, g, b;

  for (int i = 0; i < w; i++)
  {
    average = average_findBloc_V(surface, i) * 10;
    //average = 4;
    blank = -1;

    for (int j = 0; j < h; j++)
    {
      Uint32 pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r == 255 && g == 255 && b == 255)
      {
        if(blank != -1)
        {
          blank++;
        }
      }
      else
      {
        if(blank <= average)
        {
          int k = j - 1;

          while(blank > 0)
          {
            Uint32 pix = SDL_MapRGB(surface -> format, 150, 200, 255);
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

//First RLSA algorithm
void VH(SDL_Surface *surface)
{
  //Variables
  SDL_Surface* surface1 = copy_image(surface, 0, surface -> w, 0, surface -> h);
  SDL_Surface* surface2 = copy_image(surface, 0, surface -> w, 0, surface -> h);
  findBloc_H(surface1);
  findBloc_V(surface2);
  Uint8 r1, g1, b1, r2, g2, b2;

  for (int i = 0; i < surface -> w; i++)
  {
    for (int j = 0; j < surface -> h; j++)
    {
      Uint32 pixel1 = getpixel(surface1, i, j);
      SDL_GetRGB(pixel1, surface -> format, &r1, &g1, &b1);
      Uint32 pixel2 = getpixel(surface2, i, j);
      SDL_GetRGB(pixel2, surface -> format, &r2, &g2, &b2);

      if(r1 == 0 && r1 == r2)
      {
        Uint32 pix = SDL_MapRGB(surface -> format, 0, 0, 0);
        put_pixel(surface, i, j , pix);
      }
    }
  }
}

//Second RLSA algorithm
void findBloc(SDL_Surface *surface)
{
  findBloc_H(surface);
  findBloc_V(surface);
  clear_H(surface);
  clear_V(surface);
}

//Identify each line totaly white
int findNextBlankLine(SDL_Surface *surface, int begin)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  Uint8 r, g, b;
  Uint32 pixel;
  int HaveBlack = 0;

  for (int i = begin; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      if(r == 0)
      {
        HaveBlack = 1;
        break;
      }
    }
    if(HaveBlack == 0)
    {
      return i;
    }

    HaveBlack = 0;
    }

  return begin;
}

//Identify the coordinates of the first black pixel of a line of text
void findBeginLine(SDL_Surface *surface, int x_begin,
                  int y_begin, int *x_Min, int *y_Min)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  Uint8 r, g, b;
  Uint32 pixel;
  int found = 0;

  for (int i = y_begin; i < h && found == 0; i++)
  {
    for (int j = x_begin; j < w && found == 0; j++)
    {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if (r == 0)
      {
        found = 1;
        *y_Min = i;
      }
    }
  }

  int y_end = findNextBlankLine(surface, *y_Min);
  found = 0;

  for (int i = x_begin; i < w && found == 0; i++)
  {
    for (int j = y_begin; j < y_end && found == 0; j++)
    {
      pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
      if (r == 0)
      {
        found = 1;
        *x_Min = i;
      }
    }
  }
}

//Identify the coordinates of the last black pixel of a line of text
void findEndLine(SDL_Surface *surface, int x_begin,
                int y_begin, int *x_Max, int *y_Min)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  Uint8 r, g, b;
  Uint32 pixel;
  int found = 0;

  for (int i = y_begin; i < h && found == 0; i++)
  {
    for (int j = x_begin; j < w && found == 0; j++)
    {
      pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if (r == 0)
      {
        found = 1;
        *y_Min = i;
      }
    }
  }

  int y_end = findNextBlankLine(surface, *y_Min);
  found = 0;

  for (int i = w - 1; i > 0 && found == 0; i--)
  {
    for (int j = y_begin; j < y_end && found == 0; j++)
    {
      pixel = getpixel(surface, i, j);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if (r == 0)
      {
        found = 1;
        *x_Max = i;
      }
    }
  }

}

//Color each line of text
void colorLine(SDL_Surface *surface, int x_Min, int y, int x_Max)
{
  //Variables
  Uint8 r, g , b;

  for (int i = x_Min; i <= x_Max; i++)
  {
    Uint32 pixel = getpixel(surface, i, y);
    SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

    if(r == 255)
    {
      Uint32 pix = SDL_MapRGB(surface -> format, 255,150, 150);
      put_pixel(surface, i, y , pix);
    }
  }
}

//First function that identify each line of text
void findLine(SDL_Surface *surface)
{
  //Variables
  int w = surface -> w;
  int h = surface -> h;
  int x_Min;
  int y_Min;
  int x_Max;
  Uint8 r, g, b;
  int HaveBlack = 0;

  findBeginLine(surface,0,0,&x_Min, &y_Min);
  findEndLine(surface,0,0,&x_Max, &y_Min);

  for (int i = y_Min; i < h; i++)
  {
    for (int j = x_Min; j < w; j++)
    {
      Uint32 pixel = getpixel(surface, j, i);
      SDL_GetRGB(pixel, surface -> format, &r, &g, &b);

      if(r == 0)
      {
        HaveBlack = 1;
        break;
      }
    }

    if(HaveBlack == 1)
    {
      colorLine(surface,x_Min,i,x_Max);
    }

    else
    {
      findBeginLine(surface,0,i,&x_Min, &y_Min);
      findEndLine(surface,0,i,&x_Max, &y_Min);
    }

    HaveBlack = 0;
  }
}

//Second function that identify each line of text
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
void isolateChar(SDL_Surface *surface)
{
  //Variables
  Uint32 pixel;
  Uint8 r, g , b;
  int x1,x2,y1,y2;
  int save = 0;

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
          }
          else
          {
            if(!is_blank(surface,x1,x2,y1,y2))
            {
              printf("---Char :\n");
              int matrice[character -> h][character -> w];
              surface_matrice(character,character -> h, character -> w, matrice);
              print_matrice(character -> h, character -> w, matrice);
              printf("----\n");
            }
          }

          display(character);
        }
      }

      printf("\\n\n");
    }

    if( y2 != save)
    {
        i = y2;
    }
  }
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
