#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED


typedef struct GameMap {
    int tiles[MAX_GAME_MAP_X][MAX_GAME_MAP_Y]; // these are the same numbers as in the graphics
    int rivers[MAX_GAME_MAP_X][MAX_GAME_MAP_Y];
    int roads[MAX_GAME_MAP_X][MAX_GAME_MAP_Y];
} GameMap;

#endif // GAMEMAP_H_INCLUDED
