#include "header.h"
#include "globals.h"

int get_tile_food(int x, int y) {
    int food;
    
    food = gs.gm.tiles[x][y].food; // base food income
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_FERTILE) food += 2; // if fertile, +2
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_FARMS) food++; // if farms +2
    else if (gs.gm.tiles[x][y].flags&TILE_FLAGS_IRRIGATION) food++; // if irrigated, +1
    if (gs.gm.rivers[x][y] == 1) food++; // if river, +1
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_POLLUTED) food--; // if polluted, -1
    
    return food;
}

int get_tile_prod(int x, int y) {
    int prod;
    
    prod = gs.gm.tiles[x][y].prod; // base food income
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_RESOURCEFUL) prod += 2; // if resourceful, +2
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_MINE) prod++; // if mine, +1
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_RAILROAD) prod++; // if railroad, +1
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_POLLUTED) prod++; // if polluted, -1
    
    return prod;
}

int get_tile_comm(int x, int y) {
    int comm;
    
    comm = gs.gm.tiles[x][y].comm; // base comm income
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_RICH) comm += 2; // if rich, +2
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_RAILROAD) comm++; // if railroad, +2
    else if (gs.gm.tiles[x][y].flags&TILE_FLAGS_ROAD) comm++; // if road, +1
    if (gs.gm.rivers[x][y] == 1) comm++; // if river, +1
    if (gs.gm.tiles[x][y].flags&TILE_FLAGS_POLLUTED) comm--; // if polluted, -1
    
    return comm;
}
