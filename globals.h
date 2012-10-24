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

#endif // GLOBALS_H_INCLUDED
