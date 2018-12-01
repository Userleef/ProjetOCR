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
void VH2(SDL_Surface *surface, SDL_Surface *surface1, SDL_Surface *surface2);
int neighbor(SDL_Surface *surface, int x, int y);
void discover_line(SDL_Surface *surface);

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
            Uint32 pix = SDL_MapRGB(surface -> format, 0, 0, 0);
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
            Uint32 pix = SDL_MapRGB(surface -> format, 0, 0, 0);
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

      if(r1 == 0 && r2 == 255)
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

int neighbor(SDL_Surface *surface, int x, int y)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int neigh = 0;

  for (int i = x - 1; i < x + 2; i++)
  {
    if(i >= 0 && i < surface -> w)
    {
      for (int j = y - 1; j < y + 2; j++)
      {
        if(j >= 0 && (i != x || j != y) && j < surface -> h)
        {
          pixel = getpixel(surface, i, j);
          SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
          if(r == 0 && g == 0 && g == 0)
          {
            neigh++;
          }
        }
      }
    }
  }
  return neigh;
}

void neigh(SDL_Surface *surface, int x, int y, int *xmin, int *xmax, int *ymin, int *ymax)
{
  Uint32 pixel;
  Uint8 r, g, b;
  if(x < *xmin)
  {
    *xmin = x;
  }
  if(x > *xmax)
  {
    *xmax = x;
  }
  if(y < *ymin)
  {
    *ymin = y;
  }
  if(y > *ymax)
  {
    *ymax = y;
  }
  pixel = SDL_MapRGB(surface -> format, 128, 128, 128);
  put_pixel(surface, x, y, pixel);
  for (int i = x - 1; i < x + 2; i++)
  {
    if(i >= 0 && i < surface -> w)
    {
      for (int j = y - 1; j < y + 2; j++)
      {
        if(j >= 0 && (i != x || j != y) && j < surface -> h)
        {
          pixel = getpixel(surface, i, j);
          SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
          if(r == 0 && g == 0 && g == 0)
          {
            neigh(surface, i, j, xmin, xmax, ymin, ymax);
          }
        }
      }
    }
  }
}

void discover_line(SDL_Surface *surface)
{
  Uint32 pixel;
  Uint8 r, g, b;
  int x = 0;
  int y = 0;

  while (y < surface->h && x < surface->w)
  {
    int p = 1;
    for (int j = 0; j < surface -> h && p; j++) {
      for (int i = 0; i < surface -> w && p; i++) {
        pixel = getpixel(surface, i, j);
        SDL_GetRGB(pixel, surface -> format, &r, &g, &b);
        if(r == 0 && g == 0 && g == 0)
        {
          x = i;
          y = j;
          p = 0;
        }
      }
    }
    int xmin = x;
    int xmax = x;
    int ymin = y;
    int ymax = y;
    if (!p)
    {
      neigh(surface, x, y, &xmin, &xmax, &ymin, &ymax);
      printf("%dxmin = , %dymin = , %dxmax = , %dymax\n",xmin , ymin, xmax, ymax);

      SDL_Surface* img = copy_image(surface, xmin, xmax, ymin, ymax);
      display(img);
    }
    y = ymax + 1;
    x = xmin;
    p = 1;
  }
}
