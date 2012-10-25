#include "header.h"
#include "globals.h"

int main_menu() {
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
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        return CODE_EXIT_GAME;
                    }
                    if (event.key.keysym.sym == SDLK_3) {
                        return CODE_EXIT_GAME;
                    }
                    if (event.key.keysym.sym == SDLK_1) {
                        return CODE_START_NEW_GAME;
                    }
                    if (event.key.keysym.sym == SDLK_2) {
                        return CODE_LOAD_GAME;
                    }

                }
            } // end switch
        } // end of message processing
        
        
        print_full_picture(BITMAPS[IMG_FULL_MENU]);
        
        put_text_at(-1,200,"MAIN MENU");
        put_text_at(-1,300,"1 - START GAME");
        put_text_at(-1,320,"2 - LOAD GAME");
        put_text_at(-1,340,"3 - EXIT");
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    
    return 0;
}
