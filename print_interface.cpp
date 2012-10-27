#include "header.h"
#include "globals.h"

int print_interface() {
    // sidebar
    boxRGBA(MAIN_SCREEN,10*64,0,MAXX,7*64,240,0,0,255);
    // botbar
    boxRGBA(MAIN_SCREEN,0,7*64,MAXX,MAXY,0,0,240,255);
    // debugging
    char temp[80];
    if (gs.selected_type == SELECTED_CITY && gs.selected_thing >= 0) {
        sprintf(temp,"%s (%d,%d)",gs.cities[gs.selected_thing].name,gs.cities[gs.selected_thing].x,gs.cities[gs.selected_thing].y);
        put_text_at(0+5,7*64+5,temp);
    }
    if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
        sprintf(temp,"Unit %d (%d,%d)",gs.units[gs.selected_thing].type,gs.units[gs.selected_thing].x,gs.units[gs.selected_thing].y);
        put_text_at(10*64+5,0+5,temp);
    }

    return 0;
}
