#include "header.h"
#include "globals.h"

#define BUDGET_MONEY 1
#define BUDGET_RESEARCH 2
#define BUDGET_PRODUCTION 3
#define BUDGET_INFRASTRUCTURE 4
#define BUDGET_POPULATION 5

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

float appraise_city_value(int city_id) {
    // to do: forbid settling edges or deal with it
    // this is mostly a crude hack
    int x, y;
    x = gs.cities[city_id].x-1;
    y = gs.cities[city_id].y-1;
    float value; 
    float food=0, prod=0, comm=0;
    for (int i=0;i<3;i++) {
        for (int j=0;j<3;j++) {
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_ARCTIC) { food += 0; prod += 0; comm += 0.0; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_TUNDRA) { food += 1; prod += 0.5; comm += 0.5; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_GRASSLAND) { food += 2; prod += 0.5; comm += 0.5; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_FOREST) { food += 1; prod += 1; comm += 0.0; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_SWAMP) { food += 1; prod += 1; comm += 0.0; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_DESERT) { food += 0; prod += 1; comm += 0.5; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_HILLS) { food += 1; prod += 2; comm += 0.0; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_MOUNTAIN) { food += 0; prod += 4; comm += 0.0; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_JUNGLE) { food += 1; prod += 0.5; comm += 0.0; }
            if (gs.gm.tiles[x+i][y+j] == IMG_TILE_WATER) { food += 1; prod += 0; comm += 1; }
            prod += 0.5 * gs.gm.roads[x+i][y+j]; // add half road development to production
            comm += gs.gm.roads[x+i][y+j]; // add full road dev to commerce
            prod += 0.5 * gs.gm.rivers[x+i][y+j]; // half river to production
            comm += gs.gm.rivers[x+i][y+j]; // full river to commerce
            food += gs.gm.rivers[x+i][y+j]; // full river to food
            
        }
    }
    
    value = (food/2.0 + prod + 2.0*comm);
    if (gs.cities[city_id].size < 9) value = value * gs.cities[city_id].size / 9.0;
    
    
    return value;
}
