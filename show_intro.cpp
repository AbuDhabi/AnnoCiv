#include "header.h"
#include "globals.h"

int show_intro() {
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
                    done = true;
                    break;
                }
            } // end switch
        } // end of message processing
        
        
        print_full_picture(BITMAPS[IMG_FULL_INTRO]);
        
        put_text_at(-1,-1,"ANNOCIV");
        put_text_at(-1,400,"BEST GAME IN THE WORLD");
        
        SDL_Flip(MAIN_SCREEN);
        SDL_Delay(100);
    }
    
    return 0;
}
