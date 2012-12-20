#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#define MAX_CITIES 255

/// TODO: Update this shit to the new paradigm

typedef struct City {
    char name[80];
    int x, y; // location
    int size; // population size
    int faction_id; // id of the controlling faction
    short budget_money;
    short budget_production; // budget is 0-20 in each
    short budget_research; // it is a priority
    short budget_infrastructure; // value/(sum-of-values) is how much you get
    short budget_population;  // based on city stuff
    float accumulated_production;
    int production_order; // probably the same values as IMG_
    float accumulated_food; 

} City;

#endif // CITY_H_INCLUDED
