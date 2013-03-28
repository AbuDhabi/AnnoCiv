#include "header.h"
#include "globals.h"

#define BUDGET_MONEY 1
#define BUDGET_RESEARCH 2
#define BUDGET_PRODUCTION 3
#define BUDGET_INFRASTRUCTURE 4
#define BUDGET_POPULATION 5

/// TODO: Improve city growth scheme
/// TODO: Make a unit production scheme
/// TODO: Make a research scheme
/// TODO: Make a treasury scheme
/// TODO: Make an infrastructure scheme
/// TODO: Make a city turn resolution that isn't a placeholder

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
                food += get_tile_food(x+i,y+j);
                prod += get_tile_prod(x+i,y+j);
                comm += get_tile_comm(x+i,y+j);
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
    sprintf(gs.cities[cityfree].name,"Your Mom #%d",cityfree);
    
    return 0;
}

// resolves city turn, with all things relevant handled
// growth, resources, contributions, constructions, etc
// ONE city only
int resolve_city_turn(int city_id) {
    // this is mostly a placeholder so far
    city_growth(city_id);
    city_production(city_id);
    
    return 0;
}

// returns number of food units
int get_city_food(int city_id) {
    int x, y;
    x = gs.cities[city_id].x-1;
    y = gs.cities[city_id].y-1;
    int food=0;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (x+i >= 0 && y+j >=0 && x+i < MAX_GAME_MAP_X && y+j < MAX_GAME_MAP_Y) { 
                food += get_tile_food(x+i,y+j);
            }
        }
    }
    return food;
}

// checks whether the city should grow or diminish
int city_growth(int city_id) {
    // a sanity check - dead cities need not apply
    if (gs.cities[city_id].size < 1) return 0;
    
    // does the city have enough food?
    if (get_city_food(city_id) > gs.cities[city_id].size) {
        // for now, let it grow as long as it has more food than required
        gs.cities[city_id].growth_counter++;
        if (gs.cities[city_id].growth_counter > 10) {
            gs.cities[city_id].growth_counter = 0; // reset counter
            gs.cities[city_id].size++; // grow city!
        }
        return 1; // growth
    } else if (get_city_food(city_id) == gs.cities[city_id].size) {
        return 0; // stagnant
    } else { // not enough food
        gs.cities[city_id].growth_counter--; // decrement growth counter
        // too much starvation! people starve to death, bad player
        if (gs.cities[city_id].growth_counter < 0) {
            gs.cities[city_id].growth_counter = 0; // reset this
            gs.cities[city_id].size--; // decrement city
        }
        return -1; // ungrowth!
    }
}

// handles city production
int city_production(int city_id) {
    // check if the city is to produce anything
    if (gs.cities[city_id].production_type != CITY_NO_PRODUCTION && gs.cities[city_id].production_order != CITY_NO_PRODUCTION) {
        // spawn a unit with designated type and flags
        int type = gs.cities[city_id].production_type;
        int flags = gs.cities[city_id].production_order;
        int x = gs.cities[city_id].x;
        int y = gs.cities[city_id].y;
        int faction = gs.cities[city_id].faction_id;
        Unit unit = mould_unit(type, flags);
        spawn_unit(unit,x,y,faction);
    }
    
    return 0;
}

