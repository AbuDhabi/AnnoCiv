#include "header.h"
#include "globals.h"

int print_interface() {
    // sidebar
    boxRGBA(MAIN_SCREEN,10*64,0,MAXX,7*64,120,0,0,255);
    // botbar
    boxRGBA(MAIN_SCREEN,0,7*64,MAXX,MAXY,0,0,120,255);
    // debugging
    char temp[80];
    sprintf(temp,"%d  %d",gs.cities[9].x,gs.cities[9].y);
    put_text_at(0,7*64,temp);

    return 0;
}
