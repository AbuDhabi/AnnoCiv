#include "header.h"
#include "globals.h"

int print_interface() {
    // sidebar
    boxRGBA(MAIN_SCREEN,10*64,0,MAXX,7*64,120,0,0,255);
    // botbar
    boxRGBA(MAIN_SCREEN,0,7*64,MAXX,MAXY,0,0,120,255);

    return 0;
}
