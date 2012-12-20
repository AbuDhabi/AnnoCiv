#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

// extern statements for global variables go here
// no initializations!
extern bool DEBUG;
extern int MAXX;
extern int MAXY;
extern SDL_Surface* BITMAPS[255];
extern Mix_Chunk* SOUNDS[255];
extern TTF_Font* FONT_GEORGIA;
extern SDL_Surface* MAIN_SCREEN;
extern SDL_Color DEFAULT_COLOR;
// others
extern GameState gs; 
extern Unit PROTOTYPE_INFANTRY;
extern Unit PROTOTYPE_SETTLERS;
extern Tile TILE_ARCTIC;
extern Tile TILE_DESERT;
extern Tile TILE_FOREST;
extern Tile TILE_GRASSLAND;
extern Tile TILE_HILLS;
extern Tile TILE_JUNGLE;
extern Tile TILE_MOUNTAIN;
extern Tile TILE_SWAMP;
extern Tile TILE_TUNDRA;
extern Tile TILE_WATER;

#endif // GLOBALS_H_INCLUDED
