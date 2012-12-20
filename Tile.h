#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

#define TILE_FLAGS_IRRIGATION 1
#define TILE_FLAGS_FARMS 2
#define TILE_FLAGS_ROAD 4
#define TILE_FLAGS_RAILROAD 8
#define TILE_FLAGS_MINE 16
#define TILE_FLAGS_FORTRESS 32
#define TILE_FLAGS_AIRBASE 64
#define TILE_FLAGS_FERTILE 128
#define TILE_FLAGS_RESOURCEFUL 256
#define TILE_FLAGS_RICH 512
#define TILE_FLAGS_POLLUTED 1024

typedef struct Tile {
    int tile_id; // same as bitmap ID
    float defense_bonus; // as a multiplier, so 1.5 is a 50% increase
    int food; // food
    int prod; // production
    int comm; // commerce
    int move_cost; // how many units of move it costs to move onto the spot
    unsigned int flags; // tile flags for improvements and natural resources
} Tile;

#endif // TILE_H_INCLUDED
