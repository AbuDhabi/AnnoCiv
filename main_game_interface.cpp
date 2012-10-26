#include "header.h"
#include "globals.h"

int main_game_interface() {
    int lolx=0, loly=0;
    //int city=-1;
    
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
                    if (event.key.keysym.sym == SDLK_c) {
                        // find the next extant city
                        // sanity check for now, redo later
                        int counter=0;
                        for (int i=0;i<MAX_CITIES;i++) if (gs.cities[i].size > 0) counter++;
                        if (counter == 0) break;
                        do {
                            gs.selected_city++;
                            if (gs.selected_city >= MAX_CITIES) gs.selected_city = 0;
                            lolx = gs.cities[gs.selected_city].x;
                            loly = gs.cities[gs.selected_city].y;
                        } while (gs.cities[gs.selected_city].size < 1);
                        lolx -= 5; loly -= 3;
                        if (lolx <= 0) lolx = 0;
                        if (loly <= 0) loly = 0;
                        if (lolx > MAX_GAME_MAP_X-10) lolx = MAX_GAME_MAP_X-10;
                        if (loly > MAX_GAME_MAP_Y-7) loly = MAX_GAME_MAP_Y-7;
                        print_map(lolx,loly);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_u) {
                        // find the next extant unit
                        // sanity check for now, redo later
                        int counter=0;
                        for (int i=0;i<MAX_UNITS;i++) if (gs.units[i].hp > 0) counter++;
                        if (counter == 0) break;
                        do {
                            gs.selected_unit++;
                            if (gs.selected_unit >= MAX_CITIES) gs.selected_unit = 0;
                            lolx = gs.units[gs.selected_unit].x;
                            loly = gs.units[gs.selected_unit].y;
                        } while (gs.units[gs.selected_unit].hp < 1);
                        lolx -= 5; loly -= 3;
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
