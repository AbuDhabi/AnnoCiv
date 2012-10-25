#include "header.h"
#include "globals.h"

int do_game_setup_stuff(int args) {
    for (int i=0;i<MAX_CITIES;i++) {
        sprintf(gs.cities[i].name,"Butts");
        gs.cities[i].x = -1;
        gs.cities[i].y = -1;
        gs.cities[i].size = 0;
    }
    
    sprintf(gs.cities[0].name,"Buttsville");
    gs.cities[0].x = 1;
    gs.cities[0].y = 5;
    gs.cities[0].size = 56;
    
    generate_map(0,0);
    
    return 0;
}

int new_game_setup() {

    
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
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        do_game_setup_stuff(0);
                        return CODE_MAIN_GAME_INTERFACE;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return CODE_MAIN_MENU;
                    }
                }
            } // end switch
        } // end of message processing
        
        print_full_picture(BITMAPS[IMG_FULL_NEWGAMESETUP]);
        put_text_at(-1,-1,"PRETEND SETUP IS HAPPENING");
        
        put_text_at(-1,400,"Press ESC or ENTER.");
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    
    return 0;
}
