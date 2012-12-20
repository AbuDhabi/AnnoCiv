#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

typedef struct GameMap {
    // see the Tile definition
    Tile tiles[MAX_GAME_MAP_X][MAX_GAME_MAP_Y]; 
    // 1 for a river, otherwise no river
    int rivers[MAX_GAME_MAP_X][MAX_GAME_MAP_Y];
    // 1 for a road, otherwise no road
    int roads[MAX_GAME_MAP_X][MAX_GAME_MAP_Y];
} GameMap;

#endif // GAMEMAP_H_INCLUDED
