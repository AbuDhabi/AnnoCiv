#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

// image enums
#define IMG_FULL_BLANK 0
#define IMG_TILE_GRASSLAND 1
#define IMG_TILE_FOREST 2
#define IMG_TILE_HILLS 3
#define IMG_TILE_MOUNTAIN 4
#define IMG_TILE_DESERT 5
#define IMG_TILE_JUNGLE 6
#define IMG_TILE_SWAMP 7
#define IMG_TILE_TUNDRA 8
#define IMG_TILE_WATER 9
#define IMG_TILE_ARCTIC 10
#define IMG_STATIC_CITY 11

//sound enums


//misc enums


#ifdef __cplusplus
    #include <cstdlib>
    #include <stdlib.h>
#else
    #include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_gfxPrimitives.h>
#else
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>
#endif

#include <cstring>
#include <time.h>

// custom structs/classes go here
#include "Point.h"
#include "City.h"
#include "GameMap.h"
#include "GameState.h"


// function declarations go here
bool load_media();
bool clean_up();
int print_full_picture(SDL_Surface* image);
int print_image_at(int x,int y,SDL_Surface* image);
int print_map(int x,int y);

#endif // HEADER_H_INCLUDED
