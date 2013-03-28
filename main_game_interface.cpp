#include "header.h"
#include "globals.h"

int count_units() {
    int counter=0;
    for (int i=0;i<MAX_UNITS;i++) if (gs.units[i].active == UNIT_ACTIVE) counter++;
    return counter;
}

int count_cities() {
    int counter=0;
    for (int i=0;i<MAX_CITIES;i++) if (gs.cities[i].size > 0) counter++;
    return counter;
}

void sanitize_coords() {
    // sanitizing shown map coordinates
    // it shouldn't go off the map, or show beyond the map screen
    if (gs.curx < 0) gs.curx = 0;
    if (gs.cury < 0) gs.cury = 0;
    if (gs.curx > MAX_GAME_MAP_X-10) gs.curx = MAX_GAME_MAP_X-10;
    if (gs.cury > MAX_GAME_MAP_Y-7) gs.cury = MAX_GAME_MAP_Y-7;
    // sanitizing selected tile/unit/city rectangle cursor
    // it shouldn't be off the map
    if (gs.selx < 0) gs.selx = 0;
    if (gs.sely < 0) gs.sely = 0;
    if (gs.selx > MAX_GAME_MAP_X) gs.selx = MAX_GAME_MAP_X;
    if (gs.sely > MAX_GAME_MAP_Y) gs.sely = MAX_GAME_MAP_Y;
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
    if (gs.units[i].type == UNIT_TYPE_GROUND && gs.gm.tiles[gs.units[i].x][gs.units[i].y].tile_id == IMG_TILE_WATER) return false;
    // this is not a game about Vikings
    if (gs.units[i].type == UNIT_TYPE_SEA 
        && ((gs.gm.tiles[gs.units[i].x][gs.units[i].y].tile_id != IMG_TILE_WATER) 
            || any_friendly_city_there(gs.units[i].faction_id,gs.units[i].x,gs.units[i].y) )) return false;
    return true;
}

void detect_and_do_combat(int unit_id) {
    int atk_faction = gs.units[unit_id].faction_id;
    int atkx = gs.units[unit_id].x;
    int atky = gs.units[unit_id].y;
    for (int i=0;i<MAX_UNITS;i++) {
        // for combat, two units of differing allegiances must exist on the same space
        // and that the units must have positive hp
        if (gs.units[i].faction_id != atk_faction && gs.units[i].x == atkx && gs.units[i].y == atky &&
            gs.units[i].hp > 0) {
            unit_combat(unit_id,i,gs.gm.tiles[atkx][atky]);
        }
    }
    
}

int main_game_interface() {
    //int lolx=0, loly=0;
    //int city=-1;
    // sanity checks, do take care to see that they are always used whenever unit count changes
    int unitcount, citycount;
    int oldx, oldy;
    
    bool done = false;
    while (!done) {
        unitcount = count_units();
        citycount = count_cities();
        
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
                    if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_KP4) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            gs.units[gs.selected_thing].x--; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                            }
                        } else {
                            gs.curx--; 
                            gs.selx--;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_KP6) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            gs.units[gs.selected_thing].x++; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                            }
                        } else {
                            gs.curx++; 
                            gs.selx++;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_KP8) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].y--; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.cury--; 
                            gs.sely--;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_KP2) {
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].y++; 
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.cury++; 
                            gs.sely++;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_KP7) { // up-left
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].x--; 
                            gs.units[gs.selected_thing].y--;
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.curx--; 
                            gs.cury--;
                            gs.selx--;
                            gs.sely--;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_KP9) { // up-right
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].x++; 
                            gs.units[gs.selected_thing].y--;
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.curx++; 
                            gs.cury--;
                            gs.selx++;
                            gs.sely--;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_KP1) { // down-left
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].x--; 
                            gs.units[gs.selected_thing].y++;
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.curx--; 
                            gs.cury++;
                            gs.selx--;
                            gs.sely++;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_KP3) { // down-right
                        if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
                            oldx = gs.units[gs.selected_thing].x;
                            oldy = gs.units[gs.selected_thing].y;
                            gs.units[gs.selected_thing].x++; 
                            gs.units[gs.selected_thing].y++;
                            if (!sanitize_unit_coords(gs.selected_thing) && gs.units[gs.selected_thing].curmove > 0 && is_unit_allowed_there(gs.selected_thing)) { 
                                gs.units[gs.selected_thing].curmove--;
                                gs.curx = gs.units[gs.selected_thing].x-5;
                                gs.cury = gs.units[gs.selected_thing].y-3;
                                gs.selx = gs.units[gs.selected_thing].x;
                                gs.sely = gs.units[gs.selected_thing].y;
                                // combat here
                                detect_and_do_combat(gs.selected_thing);
                            } else {
                                gs.units[gs.selected_thing].x = oldx; 
                                gs.units[gs.selected_thing].y = oldy; 
                            }
                        } else {
                            gs.curx++; 
                            gs.cury++;
                            gs.selx++;
                            gs.sely++;
                        }
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    /// BUG: The city with 12 pop isn't getting cursor focus
                    if (event.key.keysym.sym == SDLK_c) { // cycle city
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
                            gs.selx = gs.units[gs.selected_thing].x;
                            gs.sely = gs.units[gs.selected_thing].y;
                        } while (gs.cities[gs.selected_thing].size < 1);
                        gs.curx -= 5; gs.cury -= 3;
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_u) { // cycle unit
                        // find the next extant unit
                        // sanity check for now, redo later
                        if (gs.selected_type == SELECTED_CITY || gs.selected_type == -1 || gs.selected_thing == -1) { 
                            gs.selected_type = SELECTED_UNIT;
                            gs.selected_thing = -1;
                        }
                        if (unitcount == 0) break; // no active units, go away
                        // finds the closest active unit and centers on it
                        do {
                            gs.selected_thing++;
                            if (gs.selected_thing >= MAX_UNITS) gs.selected_thing = 0;
                            gs.curx = gs.units[gs.selected_thing].x;
                            gs.cury = gs.units[gs.selected_thing].y;
                            gs.selx = gs.units[gs.selected_thing].x;
                            gs.sely = gs.units[gs.selected_thing].y;
                        } while (gs.units[gs.selected_thing].active == UNIT_INACTIVE);
                        gs.curx -= 5; gs.cury -= 3;
                        sanitize_coords();
                        print_map(gs.curx,gs.cury);
                        break;
                    }
                    // Build city command!
                    if (event.key.keysym.sym == SDLK_b) {
                        // make sure a unit is actually selected and can build
                        if (gs.selected_type != SELECTED_UNIT) break; // no unit selected
                        if (gs.selected_thing == -1) break; // nothing selected
                        if ((gs.units[gs.selected_thing].flags&UNIT_FLAG_SETTLER) == 0) break; // unit can't build
                        /// TODO: Checks for if there is a city too close
                        gs.units[gs.selected_thing].hp = 0; // kill the unit
                        // build the city
                        build_new_city(gs.units[gs.selected_thing].x,gs.units[gs.selected_thing].y,gs.units[gs.selected_thing].faction_id);
                        break;
                    }
                    if (event.key.keysym.sym == SDLK_p) { // production
                        if (gs.selected_type != SELECTED_CITY) break; // no city selected
                        if (gs.selected_thing == -1) break; // nothing selected
                        
                        // placeholder code until I can think of something better
                        // toggles production of random unit
                        if (gs.cities[gs.selected_thing].production_order == CITY_NO_PRODUCTION) {
                            gs.cities[gs.selected_thing].production_order = rand()%65536; // fix this later, should be a parameter or something
                            gs.cities[gs.selected_thing].production_type = rand()%3+1; // random type
                        } else {
                            gs.cities[gs.selected_thing].production_order = CITY_NO_PRODUCTION;
                        }
                        
                        
                    }
                    if (event.key.keysym.sym == SDLK_s) { // save
                        return CODE_SAVE_GAME;
                    } 
                    if (event.key.keysym.sym == SDLK_ESCAPE) { // quit
                        return CODE_MAIN_MENU;
                    }
                    if (event.key.keysym.sym == SDLK_BACKSPACE) { // turn
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
