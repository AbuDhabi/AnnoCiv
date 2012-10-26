#include "header.h"
#include "globals.h"

int do_game_setup_stuff(int args) {
    for (int i=0;i<MAX_CITIES;i++) {
        sprintf(gs.cities[i].name,"Butts");
        gs.cities[i].x = -1;
        gs.cities[i].y = -1;
        gs.cities[i].size = 0;
    }
    
    gs.selected_unit = -1;
    gs.selected_city = -1;
    
    //sprintf(gs.cities[0].name,"Buttsville");
    //gs.cities[0].x = 1;
    //gs.cities[0].y = 5;
    //gs.cities[0].size = 56;
    
    generate_map(0,0);
    
    SDL_Color color;
    
    int rx, ry;
    for (int i=0;i<MAX_FACTIONS;i++) {
        gs.factions[i].type = FACTION_TYPE_AI;
        sprintf(gs.factions[i].name,"Random AI %d",i);
        gs.factions[i].type = FACTION_TYPE_AI;
        color.b = rand()%256; color.g = rand()%256; color.r = rand()%256;
        gs.factions[i].color = color;
        do {
            rx = rand()%MAX_GAME_MAP_X;
            ry = rand()%MAX_GAME_MAP_Y;
        } while (gs.gm.tiles[rx][ry] == IMG_TILE_WATER);
        sprintf(gs.cities[i].name,"City %d",i);
        gs.cities[i].x = rx;
        gs.cities[i].y = ry;
        gs.cities[i].size = 1;
        gs.cities[i].faction_id = i;
        gs.gm.roads[rx][ry] = 1;
        gs.units[i] = PROTOTYPE_WORKERS;
        gs.units[i].faction_id = i;
        gs.units[i].x = rx;
        gs.units[i].y = ry;
    }
    
    gs.factions[0].type = FACTION_TYPE_PLAYER;
    sprintf(gs.factions[0].name,"Mr Human");
    
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
