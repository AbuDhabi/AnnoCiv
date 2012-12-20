#include "header.h"
#include "globals.h"

/// TODO: Make better colours, because they are too similar to one another.
/// BUG: Memory leak! In the normal running somewhere, no input required.
/// TODO: convert all sprintf into snprintf (this can't really be done too automatically)

// global variables go here, with initializations perhaps
// the all important debugging flag
bool DEBUG = true;
// game window dimensions
int MAXX = 800;
int MAXY = 600;
SDL_Surface* BITMAPS[255]; //255 is more than I'll need
Mix_Chunk* SOUNDS[255];
TTF_Font* FONT_GEORGIA;
SDL_Surface* MAIN_SCREEN;
SDL_Color DEFAULT_COLOR = {0x00,0x00,0x00,0xFF}; // black opaque
// more global variables, remember to extern them
GameState gs; 
// these are available to all at start, but are guesstimates at this point
// type, x, y, maxhp, hp, power, maxmove, curmove, faction, flags 1, flags 2, cost, upkeep
Unit PROTOTYPE_INFANTRY = {UNIT_TYPE_GROUND,-1,-1,10,10,1,2,2,-1,0,0,10,0};
Unit PROTOTYPE_SETTLERS = {UNIT_TYPE_GROUND,-1,-1,10,10,1,2,2,-1,UNIT_FLAG1_SETTLER,0,10,0};
// tile prototypes are defined here
// id,defense bonus, food, prod, comm, move cost
Tile TILE_ARCTIC = {IMG_TILE_ARCTIC,1.0,0,0,0,1};
Tile TILE_DESERT = {IMG_TILE_DESERT,1.0,0,1,0,1};
Tile TILE_FOREST = {IMG_TILE_FOREST,1.5,1,2,0,2};
Tile TILE_GRASSLAND = {IMG_TILE_GRASSLAND,1.0,2,1,0,1};
Tile TILE_HILLS = {IMG_TILE_HILLS,2.0,1,0,0,2};
Tile TILE_JUNGLE = {IMG_TILE_JUNGLE,1.5,1,0,0,2};
Tile TILE_MOUNTAIN = {IMG_TILE_MOUNTAIN,3.0,0,2,0,3};
Tile TILE_SWAMP = {IMG_TILE_SWAMP,1.5,1,0,0,2};
Tile TILE_TUNDRA = {IMG_TILE_TUNDRA,1.0,1,0,0,1};
Tile TILE_WATER = {IMG_TILE_WATER,1.0,1,0,2,1};


int main ( int argc, char** argv )
{
    srand((unsigned)time(0)); // IT'S RANDOM TIME
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO&SDL_INIT_AUDIO&SDL_INIT_TIMER ) < 0 )
    {
        fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }
    // initialize SDL sound
    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
        // audio is something we can skip, really; non-essential
        //exit(1);
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Unable to initialize TTF: %s\n", TTF_GetError());
        exit(1);
    }
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        // handle error
    }
    // make sure SDL cleans up before exit
    atexit(SDL_Quit);
    atexit(TTF_Quit);
    atexit(IMG_Quit);

    // create a new window
    MAIN_SCREEN = SDL_SetVideoMode(MAXX, MAXY, 16,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !MAIN_SCREEN )
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        return 1;
    }
    SDL_WM_SetCaption("AnnoCiv","AnnoCiv");
    
    
    // LOAD MEDIA
    if (!load_media()) {
        // errors! could not load media for whatever reason
        exit(0); 
    };
    
    // GAME CODE HERE
    
    show_intro();
    
    int state = main_menu();
    while (state != CODE_EXIT_GAME) {
        if (state == CODE_MAIN_MENU) state = main_menu();
        if (state == CODE_MAIN_GAME_INTERFACE) state = main_game_interface();
        if (state == CODE_LOAD_GAME) state = save_load_interface(CHOICE_LOAD);
        if (state == CODE_START_NEW_GAME) state = new_game_setup();
        if (state == CODE_SAVE_GAME) state = save_load_interface(CHOICE_SAVE);
    }

    //while (true) {
    
    //print_full_picture(BITMAPS[IMG_TILE_FOREST]);
    
    //for (int i=0;i<100;i++) {
    //    for (int j=0;j<100;j++) {
    //        gs.gm.tiles[i][j]=rand()%10+1;
    //        gs.gm.rivers[i][j]=rand()%2-rand()%3+1;
    //        gs.gm.roads[i][j]=rand()%2-rand()%3+1;
    //        //print_image_at(i*64,j*64,BITMAPS[gs.gm.tiles[i][j]]);
    //    }
    //}
    //gs.gm.tiles[1][1] = IMG_TILE_WATER;
    //gs.gm.rivers[2][1] = 1;
    //gs.gm.tiles[0][99] = IMG_UNIT_ARMOUR;

    
    
    //int lineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
    //int lineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    //lineRGBA(MAIN_SCREEN,20,20,50,50,50,50,50,255);
    
    //SDL_Flip(MAIN_SCREEN);
    //SDL_Delay(3000);
    
    //}

    // END GAME CODE

    clean_up();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
