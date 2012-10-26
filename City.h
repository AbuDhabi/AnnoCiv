#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#define MAX_CITIES 255

typedef struct City {
    char name[80];
    int x, y; // location
    int size; // population size
    int faction_id; //
} City;

#endif // CITY_H_INCLUDED
