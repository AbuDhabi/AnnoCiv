#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED

#define MAX_UNITS 65535

typedef struct Unit {
    int type; // same as unit image designations
    int x;
    int y;
    int faction_id; // id of the spawning faction
} Unit;

#endif // UNIT_H_INCLUDED
