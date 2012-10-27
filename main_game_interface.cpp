#include "header.h"
#include "globals.h"

int count_units() {
    int counter=0;
    for (int i=0;i<MAX_UNITS;i++) if (gs.units[i].hp > 0) counter++;
    return counter;
}

int count_cities() {
    int counter=0;
    for (int i=0;i<MAX_CITIES;i++) if (gs.cities[i].size > 0) counter++;
    return counter;
}

void sanitize_coords() {
    if (gs.curx < 0) gs.curx = 0;
    if (gs.cury < 0) gs.cury = 0;
    if (gs.curx > MAX_GAME_MAP_X-10) gs.curx = MAX_GAME_MAP_X-10;
    if (gs.cury > MAX_GAME_MAP_Y-7) gs.cury = MAX_GAME_MAP_Y-7;
}
bool sanitize_unit_coords(int i) { // true if modified anything, false if not
    int counter=0;
    if (gs.units[i].x < 0) { gs.units[i].x = 0; counter++; }
    if (gs.units[i].y < 0) { gs.units[i].y = 0; counter++; }
    if (gs.units[i].x >= MAX_GAME_MAP_X) { gs.units[i].x = MAX_GAME_MAP_X-1; counter++; }
    if (gs.units[i].y >= MAX_GAME_MAP_Y) { gs.units[i].y = MAX_GAME_MAP_Y-1; counter++; }
    if (counter > 0) return true; else return false;
}

bool any_friendly_city_there(int faction, int x, int y) {
    for (int i=0;i<MAX_CITIES;i++) {
        if (gs.cities[i].x == x && gs.cities[i].y == y && gs.cities[i].faction_id == faction) return true;
    }
    return false;
}

bool is_unit_allowed_there(int i) { 
    // Jesus could walk on water, but infantry probably can't.
    if (gs.units[i].move_type == MOVE_TYPE_GROUND && gs.gm.tiles[gs.units[i].x][gs.units[i].y] == IMG_TILE_WATER) return false;
    // this is not a game about Vikings
    if (gs.units[i].move_type == MOVE_TYPE_SEA 
        && ((gs.gm.tiles[gs.units[i].x][gs.units[i].y] != IMG_TILE_WATER) 
            || any_friendly_city_there(gs.units[i].faction_id,gs.units[i].x,gs.units[i].y) )) return false;
    return true;
}

int main_game_interface() {
    //int lolx=0, loly=0;
    //int city=-1;
    // sanity checks, do take care to see that they are always used whenever unit count changes
    int unitcount, citycount;
    unitcount = count_units();
    citycount = count_cities();
    int oldx, oldy;
    
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
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            gs.units[gs.selected_thing].x--; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                            }
                        } else {
                            gs.curx--; 
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            gs.units[gs.selected_thing].x++; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                            }
                        } else {
                            gs.curx++; 
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_UP) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].y--; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                            } else {
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.cury--; 
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].y++; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                            } else {
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.cury++; 
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_c) {
                        // find the next extant city
                        // sanity check for now, redo later
                        if (gs.selected_type == SELECTED_UNIT || gs.selected_type == -1 || gs.selected_thing == -1) { 
                            gs.selected_type = SELECTED_CITY;
                            gs.selected_thing = -1;
                        }
                        if (citycount == 0) break;
                        do {
                            gs.selected_thing++;
                            if (gs.selected_thing >= MAX_CITIES) gs.selected_thing = 0;
                            gs.curx = gs.cities[gs.selected_thing].x;
                            gs.cury = gs.cities[gs.selected_thing].y;
                        } while (gs.cities[gs.selected_thing].size < 1);
                        gs.curx -= 5; gs.cury -= 3;
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_u) {
                        // find the next extant unit
                        // sanity check for now, redo later
                        if (gs.selected_type == SELECTED_CITY || gs.selected_type == -1 || gs.selected_thing == -1) { 
                            gs.selected_type = SELECTED_UNIT;
                            gs.selected_thing = -1;
                        }
                        if (unitcount == 0) break;
                        do {
                            gs.selected_thing++;
                            if (gs.selected_thing >= MAX_UNITS) gs.selected_thing = 0;
                            gs.curx = gs.units[gs.selected_thing].x;
                            gs.cury = gs.units[gs.selected_thing].y;
                        } while (gs.units[gs.selected_thing].hp < 1);
                        gs.curx -= 5; gs.cury -= 3;
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_s) {
                        return CODE_SAVE_GAME;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return CODE_MAIN_MENU;
                    }
                    if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        // end turn hack
                        do_turn();
                        break;
                    }
                }
            } // end switch
        } // end of message processing
        
        print_map(gs.curx,gs.cury);
        print_interface();
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    
    return 0;
}
