#include "header.h"
#include "globals.h"

int do_turn() {
    // interate sides, checking if they're AI-controlled and active
    // doing all their stuff
    for (int i=0;i<MAX_FACTIONS;i++) {
        if (gs.factions[i].type == FACTION_TYPE_AI && gs.factions[i].status == FACTION_STATUS_ACTIVE)
            do_ai(i);
    }
    
    int lastunit = get_last_unit_id();
    // hack to restore move
    for (int i=0;i<=lastunit;i++) {
        gs.units[i].curmove = gs.units[i].maxmove;
    }
    
    /// TODO: city resolution turns
    
    for (int i=0;i<MAX_CITIES;i++) {
        if (gs.cities[i].size > 0) {
            resolve_city_turn(i);
        }
    }
    
    // resolve faction stuff
    faction_upkeep();
    for (int i=0;i<MAX_FACTIONS;i++) {
        faction_research(i);
    }
    
    
    return 0;
}
