#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

// extern statements for global variables go here
// no initializations!
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
extern Unit PROTOTYPE_CAVALRY;
extern Unit PROTOTYPE_ARMOUR;
extern Unit PROTOTYPE_ARTILLERY;
extern Unit PROTOTYPE_BATTLESHIP;
extern Unit PROTOTYPE_SUBMARINE;
extern Unit PROTOTYPE_SEATRANSPORT;
extern Unit PROTOTYPE_FIGHTER;
extern Unit PROTOTYPE_BOMBER;
extern Unit PROTOTYPE_AIRTRANSPORT;
extern Unit PROTOTYPE_MISSILE;
extern Unit PROTOTYPE_WORKERS;

#endif // GLOBALS_H_INCLUDED
