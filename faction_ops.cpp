#include "header.h"
#include "globals.h"

// handle research per turn
int faction_research(int faction) {
    // not sure how to handle this yet
    /// TODO: Figure this shit out
    /// BUG: Tech levels won't increase
    // sum up commerce in all cities beloging to the faction
    int sum = 0;
    int counter = 0;
    for (int i=0;i<MAX_CITIES;i++) {
        if (gs.cities[i].faction_id == faction && gs.cities[i].size > 0) {
            sum += get_city_comm(i);
            counter++;
        }
    }
    // divide sum by amount of cities, averaging it
    float result = (float)sum/(float)counter;
    // assign evenly to research progresses
    gs.factions[faction].research.AgrEne_progress += result/5.0;
    gs.factions[faction].research.ComTra_progress += result/5.0;
    gs.factions[faction].research.InfCom_progress += result/5.0;
    gs.factions[faction].research.ProEng_progress += result/5.0;
    gs.factions[faction].research.SocGov_progress += result/5.0;
    // check if research is completed, if so, upgrade and subtract from progress
    if (gs.factions[faction].research.AgrEne_progress >= 100) {
        gs.factions[faction].research.AgrEne++;
        gs.factions[faction].research.AgrEne_progress -= 100;
    }
    if (gs.factions[faction].research.ComTra_progress >= 100) {
        gs.factions[faction].research.ComTra++;
        gs.factions[faction].research.ComTra_progress -= 100;
    }
    if (gs.factions[faction].research.InfCom_progress >= 100) {
        gs.factions[faction].research.InfCom++;
        gs.factions[faction].research.InfCom_progress -= 100;
    }
    if (gs.factions[faction].research.ProEng_progress >= 100) {
        gs.factions[faction].research.ProEng++;
        gs.factions[faction].research.ProEng_progress -= 100;
    }
    if (gs.factions[faction].research.SocGov_progress >= 100) {
        gs.factions[faction].research.SocGov++;
        gs.factions[faction].research.SocGov_progress -= 100;
    }
    return 0;
}

int faction_upkeep () {
    // unit upkeep
    /// TODO: Standardize when units get counted
    for (int i=0;i<MAX_UNITS;i++) {
        if (gs.units[i].active == UNIT_ACTIVE) {
            gs.factions[gs.units[i].faction_id].money -= gs.units[i].upkeep;
        }
    }

    return 0;
}
