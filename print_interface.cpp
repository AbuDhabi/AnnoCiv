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
        // name location
        sprintf(temp,"%s (%d,%d)",gs.cities[gs.selected_thing].name,gs.cities[gs.selected_thing].x,gs.cities[gs.selected_thing].y);
        put_text_at(0+5,7*64+5,temp);
        sprintf(temp,"City Value: %4.2f",appraise_city_value(gs.selected_thing));
        put_text_at(200+5,7*64+5,temp);
        // budget
        sprintf(temp,"Money: %d",gs.cities[gs.selected_thing].budget_money);
        put_text_at(0+5,7*64+35,temp);
        sprintf(temp,"Production: %d",gs.cities[gs.selected_thing].budget_production);
        put_text_at(0+5,7*64+50,temp);
        sprintf(temp,"Population: %d",gs.cities[gs.selected_thing].budget_population);
        put_text_at(0+5,7*64+65,temp);
        sprintf(temp,"Infrastructure: %d",gs.cities[gs.selected_thing].budget_infrastructure);
        put_text_at(0+5,7*64+80,temp);
        sprintf(temp,"Research: %d",gs.cities[gs.selected_thing].budget_research);
        put_text_at(0+5,7*64+95,temp);
    }
    if (gs.selected_type == SELECTED_UNIT && gs.selected_thing >= 0) {
        // name and location 
        unit_type_to_text(gs.units[gs.selected_thing].type,temp);
        sprintf(temp,"%s (%d,%d)",temp,gs.units[gs.selected_thing].x,gs.units[gs.selected_thing].y);
        put_text_at(10*64+5,0+5,temp);
        // power movement
        sprintf(temp,"P %d, M %d/%d",gs.units[gs.selected_thing].power,gs.units[gs.selected_thing].curmove,gs.units[gs.selected_thing].maxmove);
        put_text_at(10*64+5,0+20,temp);
        // hit points
        sprintf(temp,"HP %d/%d",gs.units[gs.selected_thing].hp,gs.units[gs.selected_thing].maxhp);
        put_text_at(10*64+5,0+35,temp);
    }

    return 0;
}
