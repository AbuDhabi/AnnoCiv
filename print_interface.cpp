#include "header.h"
#include "globals.h"

int print_interface() {
    // sidebar
    boxRGBA(MAIN_SCREEN,10*64,0,MAXX,7*64,240,0,0,255);
    // botbar
    boxRGBA(MAIN_SCREEN,0,7*64,MAXX,MAXY,0,0,240,255);
    // corner bar
    boxRGBA(MAIN_SCREEN,10*64,7*64,MAXX,MAXY,0,240,0,255);
    // information printing
    char temp[80];
    
    // monies and other faction stuff
    /// TODO: Having a faction selected
    sprintf(temp,"Reserve: %d",gs.factions[gs.player_faction].money);
    put_text_at(10*64+5,7*64+5,temp);
    sprintf(temp,"AgrEne: %d/%1.2f",gs.factions[gs.player_faction].research.AgrEne,gs.factions[gs.player_faction].research.AgrEne_progress);
    put_text_at(10*64+5,7*64+20,temp);
    sprintf(temp,"ComTra: %d/%1.2f",gs.factions[gs.player_faction].research.ComTra,gs.factions[gs.player_faction].research.ComTra_progress);
    put_text_at(10*64+5,7*64+35,temp);
    sprintf(temp,"InfCom: %d/%1.2f",gs.factions[gs.player_faction].research.InfCom,gs.factions[gs.player_faction].research.InfCom_progress);
    put_text_at(10*64+5,7*64+50,temp);
    sprintf(temp,"ProEng: %d/%1.2f",gs.factions[gs.player_faction].research.ProEng,gs.factions[gs.player_faction].research.ProEng_progress);
    put_text_at(10*64+5,7*64+65,temp);
    sprintf(temp,"SocGov: %d/%1.2f",gs.factions[gs.player_faction].research.SocGov,gs.factions[gs.player_faction].research.SocGov_progress);
    put_text_at(10*64+5,7*64+80,temp);
    
    
    
    if (gs.selected_type == SELECTED_CITY && gs.selected_thing >= 0) {
        // name location
        sprintf(temp,"%s (%d,%d)",gs.cities[gs.selected_thing].name,gs.cities[gs.selected_thing].x,gs.cities[gs.selected_thing].y);
        put_text_at(0+5,7*64+5,temp);
        sprintf(temp,"City Value: %4.2f",appraise_city_value(gs.selected_thing));
        put_text_at(200+5,7*64+5,temp);
        sprintf(temp,"Production: %d-%d", gs.cities[gs.selected_thing].production_type,gs.cities[gs.selected_thing].production_order);
        put_text_at(200+5,7*64+20,temp);
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
    
    // debug stuff
    if (DEBUG) {
        sprintf (temp,"selx %d, sely %d", gs.selx, gs.sely);
        put_text_at(0,0,temp);
        sprintf (temp,"curx %d, cury %d", gs.curx, gs.cury);
        put_text_at(0,10,temp);
        sprintf (temp,"selected thing %d, selected type %d", gs.selected_thing, gs.selected_type);
        put_text_at(0,20,temp);
        sprintf (temp,"last unit ID: %d", get_last_unit_id());
        put_text_at(0,30,temp);
        sprintf (temp,"tile flags under cursor: %d", gs.gm.tiles[gs.selx][gs.sely].flags);
        put_text_at(0,40,temp);
    }

    return 0;
}

