#include "header.h"
#include "globals.h"

int save_game (GameState * gameState) {
    FILE *fp; 
    // structure dump
    fp=fopen("save//game.sav","wb");
    if (fp!=0) {
        fwrite((char*)gameState,sizeof(GameState),1,fp);
        fclose(fp);
    } else {
        fprintf(stderr,"File not open. Could not save.");
        return 1; // error!
    }
    //move(22,0); printw("Game saved. Press any key to continue.");
    //getch();
    return 0;
}

int load_game(GameState * gameState) {
    FILE *fp; 
    // load structure
    fp=fopen("save//game.sav","rb");
    if (fp!=0) {
        fread((char*)gameState,sizeof(GameState),1,fp);
        fclose(fp);
    } else {
        fprintf(stderr,"File not open. Could not load.");
        return 1; // error!
    }
    //clear_screen();
    //move(10,COLS/2-1-5); printw("GAME LOADED");
    //move(11,COLS/2-1-12); printw("Welcome back, commander.");
    //getch();
    return 0; 
}

int save_load_interface(int which) { // use the CHOICE_ defines
    int outcome=1;
    char temp[80];
    
    if (which == CHOICE_SAVE) {
        outcome = save_game (&gs);
        if (outcome == 1) sprintf(temp,"Saving FAILED."); else sprintf(temp,"Saving successful!");
    } else if (which == CHOICE_LOAD) {
        outcome = load_game (&gs);
        if (outcome == 1) sprintf(temp,"Loading FAILED."); else sprintf(temp,"Loading successful!");
    } else {
        // what the shit?
    }
    
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
                        if (outcome == 0)
                            return CODE_MAIN_GAME_INTERFACE;
                        else
                            if (which == CHOICE_SAVE) return CODE_MAIN_GAME_INTERFACE;
                            else if (which == CHOICE_LOAD) return CODE_MAIN_MENU;
                            else { /* what the shit man */  }
                    }
                }
            } // end switch
        } // end of message processing
        
        print_full_picture(BITMAPS[IMG_FULL_SAVELOAD]);
        if (which == CHOICE_SAVE) put_text_at(-1,300,"SAVING...");
        else if (which == CHOICE_LOAD) put_text_at(-1,300,"LOADING...");
        
        put_text_at(-1,400,temp);
        
        put_text_at(-1,500,"Press ENTER to continue.");
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    
    
    return 0;
}


