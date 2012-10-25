#include "header.h"
#include "globals.h"

int main_game_interface() {
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
                    if (event.key.keysym.sym == SDLK_s) {
                        return CODE_SAVE_GAME;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return CODE_MAIN_MENU;
                    }
                }
            } // end switch
        } // end of message processing
        
        print_map(lolx,loly);
        print_interface();
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    
    return 0;
}
