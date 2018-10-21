#ifndef SEGMENTATION_H
#define SEGMENTATION_H

void findBloc(SDL_Surface * surface);
void findBloc_V(SDL_Surface * surface);
void findBloc_H(SDL_Surface * surface);
void findLine(SDL_Surface * surface);
void lineCut(SDL_Surface *img);
void charcut(SDL_Surface *surface);
void isolateChar(SDL_Surface * surface);
void VH(SDL_Surface * surface);

#endif
