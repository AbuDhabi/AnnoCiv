#include "header.h"
#include "globals.h"

#define BUDGET_MONEY 1
#define BUDGET_RESEARCH 2
#define BUDGET_PRODUCTION 3
#define BUDGET_INFRASTRUCTURE 4
#define BUDGET_POPULATION 5

/// TODO: Make a city growth scheme
/// TODO: Make a unit production scheme
/// TODO: Make a research scheme
/// TODO: Make a treasury scheme
/// TODO: Make an infrastructure scheme

int change_budget(int city_id, int branch, int new_amount) {
    //int counter; int accumulated;
    int value_to_set;
    if (new_amount < 0) value_to_set = 0;
    if (new_amount > 20) value_to_set = 20;
    switch(branch) {
        case BUDGET_MONEY:
            gs.cities[city_id].budget_money = value_to_set;
            break;
        case BUDGET_RESEARCH:
            gs.cities[city_id].budget_research = value_to_set;
            break;
        case BUDGET_PRODUCTION:
            gs.cities[city_id].budget_production = value_to_set;
            break;
        case BUDGET_INFRASTRUCTURE:
            gs.cities[city_id].budget_infrastructure = value_to_set;
            break;
        case BUDGET_POPULATION:
            gs.cities[city_id].budget_population = value_to_set;
            break;
        default:
            break;
        
    }
    return 0;
}

/// TODO: improve this somehow

float appraise_city_value(int city_id) {
    // to do: forbid settling edges or deal with it
    // this is mostly a less crude hack
    int x, y;
    x = gs.cities[city_id].x-1;
    y = gs.cities[city_id].y-1;
    float value; 
    float food=0, prod=0, comm=0;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (x+i >= 0 && y+j >=0 && x+i < MAX_GAME_MAP_X && y+j < MAX_GAME_MAP_Y) { 
                food = get_tile_food(x+i,y+j);
                prod = get_tile_prod(x+i,y+j);
                comm = get_tile_comm(x+i,y+j);
            }
            
        }
    }
    
    value = (food + prod + comm);
    if (gs.cities[city_id].size < 9) value = value * gs.cities[city_id].size / 9.0;
    
    
    return value;
}

int build_new_city(int x, int y, int faction) {
    // find an empty city slot
    int cityfree = -1;
    for (int i=0;i<MAX_CITIES;i++) 
        if (gs.cities[i].size == 0) cityfree = i;
    if (cityfree == -1) return 1; // no free cities, mon
    gs.cities[cityfree].size = 1;
    gs.cities[cityfree].faction_id = faction;
    gs.cities[cityfree].x = x;
    gs.cities[cityfree].y = y;
    /// TODO: Improve naming
    /// Implement that language system
    sprintf(gs.cities[cityfree].name,"Your Mom #%d",cityfree);
    
    return 0;
}

int resolve_city_turn(int city_id) {
    
    
    return 0;
}
