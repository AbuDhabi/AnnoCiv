#include "header.h"
#include "globals.h"

// global variables go here, with initializations perhaps
int MAXX = 800;
int MAXY = 600;
SDL_Surface* BITMAPS[255]; //255 is more than I'll need
Mix_Chunk* SOUNDS[255];
TTF_Font* FONT_GEORGIA;
SDL_Surface* MAIN_SCREEN;
SDL_Color DEFAULT_COLOR = {0x00,0x00,0x00,0xFF}; // black opaque
// more global variables, remember to extern them
GameState gs; 

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

    //while (true) {
    
    print_full_picture(BITMAPS[IMG_TILE_FOREST]);
    
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
    
    for (int i=0;i<MAX_CITIES;i++) {
        sprintf(gs.cities[i].name,"");
        gs.cities[i].x = -1;
        gs.cities[i].y = -1;
        gs.cities[i].size = 0;
    }
    
    sprintf(gs.cities[0].name,"Buttsville");
    gs.cities[0].x = 1;
    gs.cities[0].y = 5;
    gs.cities[0].size = 4;
    
    generate_map(0,0);
    
    print_map(0,0);
    
    
    //int lineColor(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color);
    //int lineRGBA(SDL_Surface * dst, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    //lineRGBA(MAIN_SCREEN,20,20,50,50,50,50,50,255);
    
    //SDL_Flip(MAIN_SCREEN);
    //SDL_Delay(3000);
    
    int lolx=0, loly=0;
    
    bool done = false;
    while (!done) {
        
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    if (event.key.keysym.sym == SDLK_LEFT) {
                        lolx--; 
                        if (lolx <= 0) lolx = 0;
                        if (loly <= 0) loly = 0;
                        if (lolx > MAX_GAME_MAP_X-10) lolx = MAX_GAME_MAP_X-10;
                        if (loly > MAX_GAME_MAP_Y-7) loly = MAX_GAME_MAP_Y-7;
                        print_map(lolx,loly);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        lolx++;
                        if (lolx <= 0) lolx = 0;
                        if (loly <= 0) loly = 0;
                        if (lolx > MAX_GAME_MAP_X-10) lolx = MAX_GAME_MAP_X-10;
                        if (loly > MAX_GAME_MAP_Y-7) loly = MAX_GAME_MAP_Y-7;
                        print_map(lolx,loly);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_UP) {
                        loly--;
                        if (lolx <= 0) lolx = 0;
                        if (loly <= 0) loly = 0;
                        if (lolx > MAX_GAME_MAP_X-10) lolx = MAX_GAME_MAP_X-10;
                        if (loly > MAX_GAME_MAP_Y-7) loly = MAX_GAME_MAP_Y-7;
                        print_map(lolx,loly);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        loly++;
                        if (lolx <= 0) lolx = 0;
                        if (loly <= 0) loly = 0;
                        if (lolx > MAX_GAME_MAP_X-10) lolx = MAX_GAME_MAP_X-10;
                        if (loly > MAX_GAME_MAP_Y-7) loly = MAX_GAME_MAP_Y-7;
                        print_map(lolx,loly);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        // exit if ESCAPE PRESSED
                        done = true;
                        break;
                    }
                }
            } // end switch
        } // end of message processing
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    //}

    // END GAME CODE

    clean_up();

    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
