#include "header.h"
#include "globals.h"

SDL_Surface* load_bitmap(const char * path) {
    SDL_Surface * temp;
    temp = IMG_Load(path);
    if (!temp) {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
        return NULL;
    } else {
        return temp;
    }
}

Mix_Chunk* load_sound(const char * path) {
    Mix_Chunk * temp;
    temp = Mix_LoadWAV(path);
    if (!temp) {
        printf("Unable to load wave file: %s\n", Mix_GetError());
        return NULL;
    } else {
        return temp;
    }
}

bool load_media() {
    // prevent undefined shit with media
    for (int i=0;i<255;i++) {
        BITMAPS[i] = NULL;
        SOUNDS[i] = NULL;
    }
    
    FONT_GEORGIA = TTF_OpenFont("georgia.ttf", 16);
    if (FONT_GEORGIA == NULL){
        printf("Unable to load font: %s %s \n", "georgia.ttf", TTF_GetError());
        // Handle the error here.
    }
    // load images
    // FORMAT AS FOLLOWS
    // BITMAPS[$enum_from_header] = load_bitmap("path.png");
    BITMAPS[IMG_FULL_BLANK] = load_bitmap("data//img//blank.png");
    BITMAPS[IMG_TILE_GRASSLAND] = load_bitmap("data//img//tiles0001.png");
    BITMAPS[IMG_TILE_FOREST] = load_bitmap("data//img//tiles0002.png");
    BITMAPS[IMG_TILE_HILLS] = load_bitmap("data//img//tiles0003.png");
    BITMAPS[IMG_TILE_MOUNTAIN] = load_bitmap("data//img//tiles0004.png");
    BITMAPS[IMG_TILE_DESERT] = load_bitmap("data//img//tiles0005.png");
    BITMAPS[IMG_TILE_JUNGLE] = load_bitmap("data//img//tiles0006.png");
    BITMAPS[IMG_TILE_SWAMP] = load_bitmap("data//img//tiles0007.png");
    BITMAPS[IMG_TILE_TUNDRA] = load_bitmap("data//img//tiles0008.png");
    BITMAPS[IMG_TILE_WATER] = load_bitmap("data//img//tiles0009.png");
    BITMAPS[IMG_TILE_ARCTIC] = load_bitmap("data//img//tiles0010.png");
    BITMAPS[IMG_STATIC_CITY] = load_bitmap("data//img//city.png");
    BITMAPS[IMG_UNIT_INFANTRY] = load_bitmap("data//img//units0001.png");
    BITMAPS[IMG_UNIT_CAVALRY] = load_bitmap("data//img//units0002.png");
    BITMAPS[IMG_UNIT_ARMOUR] = load_bitmap("data//img//units0003.png");
    BITMAPS[IMG_UNIT_ARTILLERY] = load_bitmap("data//img//units0004.png");
    BITMAPS[IMG_UNIT_WORKERS] = load_bitmap("data//img//units0005.png");
    BITMAPS[IMG_UNIT_BATTLESHIP] = load_bitmap("data//img//units0006.png");
    BITMAPS[IMG_UNIT_SUBMARINE] = load_bitmap("data//img//units0007.png");
    BITMAPS[IMG_UNIT_SEATRANSPORT] = load_bitmap("data//img//units0008.png");
    BITMAPS[IMG_UNIT_FIGHTER] = load_bitmap("data//img//units0009.png");
    BITMAPS[IMG_UNIT_BOMBER] = load_bitmap("data//img//units0010.png");
    BITMAPS[IMG_UNIT_MISSILE] = load_bitmap("data//img//units0011.png");
    BITMAPS[IMG_UNIT_AIRTRANSPORT] = load_bitmap("data//img//units0012.png");
    
    //load sounds
    // FORMAT AS FOLLOWS
    // SOUNDS[$enum_from_header] = load_sound("path.ogg");


    return true;
}


